/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <set>
#include <fstream>
#include <min/core/parser.h>
#include <min/core/property_list.h>
#include <Eigen/Geometry>
#include <pugixml.hpp>

MIN_NAMESPACE_BEGIN

MinObject *LoadFromXML(const std::string &filename) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(filename.c_str());

  // Helper lambda function for map a position offset in bytes to a more readable line value
  auto offset = [&](ptrdiff_t pos) -> std::string {
    std::fstream is(filename);
    char buffer[1024];
    int line = 0, linestart = 0, offset = 0;
    while (is.good()) {
      is.read(buffer, sizeof(buffer));
      for (int i = 0; i < is.gcount(); i++) {
        if (buffer[i] == '\n') {
          if (offset + i >= pos) {
            return fmt::format("line %i, col %i", line + 1, pos - linestart);
          }
          line++;
          linestart = offset + i;
        }
      }
      offset += (int) is.gcount();
    }
    return "byte offset" + std::to_string(pos);
  };

  if (!result) {
    // IO error
    throw std::runtime_error(fmt::format("Error while parsing \"%s\": %s (at %s)", filename, result.description(), offset(result.offset)));
  }

  enum Tag {
    kScene = MinObject::kScene,
    kMesh = MinObject::kMesh,
    kBSDF = MinObject::kBSDF,
    kCamera = MinObject::kCamera,
    kIntegrator = MinObject::kIntegrator,
    kSampler = MinObject::kSampler,
    kFilter = MinObject::kFilter,

    kBoolean = MinObject::kClassTypeCount,
    kInteger,
    kFloat,
    kString,
    kVector,
    kColor,
    kTransform,
    kTranslate,
    kMatrix,
    kRotate,
    kScale,
    kLookAt,
    kInvalid
  };

  std::map<std::string, Tag> tags;
  tags["scene"]      = kScene;
  tags["mesh"]       = kMesh;
  tags["bsdf"]       = kBSDF;
  tags["camera"]     = kCamera;
  tags["integrator"] = kIntegrator;
  tags["sampler"]    = kSampler;
  tags["filter"]    = kFilter;

  auto check_attributes = [&](const pugi::xml_node &node, std::set<std::string> attrs) {
    for (auto attr : node.attributes()) {
      auto it = attrs.find(attr.name());
      if (it == attrs.end()) {
        throw std::runtime_error(fmt::format(R"(Error while parsing "%s": unexpected attribute "%s" in "%s" at %s)",
                                             filename, attr.name(), node.name(), offset(node.offset_debug())));
      }
      attrs.erase(it);
    }
    if (!attrs.empty()) {
      throw std::runtime_error(fmt::format(R"(Error while parsing "%s": missing attribute "%s" in "%s" at %s)",
                                           filename, *attrs.begin(), node.name(), offset(node.offset_debug())));
    }
  };

  Eigen::Affine3f transform;

  std::function<MinObject *(pugi::xml_node &, PropertyList &, int)> parse_tag = [&](
      pugi::xml_node &node, PropertyList &list, int parent_tag) -> MinObject* {
    // Skip over comments
    if (node.type() == pugi::node_comment || node.type() == pugi::node_declaration)
      return nullptr;

    if (node.type() != pugi::node_element)
      throw std::runtime_error(fmt::format("Error while parsing \"%s\": unexpected content at %s",
                                           filename, offset(node.offset_debug())));

    auto it = tags.find(node.name());
    if (it == tags.end())
      throw std::runtime_error(fmt::format(R"(Error while parsing "%s": unexpected tag "%s" at %s)",
                                           filename, node.name(), offset(node.offset_debug())));
    int tag = it->second;

    // Perform some safety checks to make sure that the XML tree really make sense
    bool has_parent = parent_tag != kInvalid;
    bool parent_is_object = has_parent && parent_tag < MinObject::kClassTypeCount;
    bool current_is_object = tag < MinObject::kClassTypeCount;
    bool parent_is_transform = parent_tag == kTransform;
    bool current_is_transform_op = tag == kTranslate || tag == kRotate ||
        tag == kScale || tag == kLookAt || tag == kMatrix;

    if (!has_parent && !current_is_object) {
      throw std::runtime_error(fmt::format(R"(Error while parsing "%s": root element "%s" must be a Nori object (at %s))",
                                           filename, node.name(), offset(node.offset_debug())));
    }
    if (parent_is_transform != current_is_transform_op) {
      throw std::runtime_error(fmt::format("Error while parsing \"%s\": transform nodes "
                                           "can only contain transform operations (at %s)",
                                           filename,  offset(node.offset_debug())));
    }
    if (has_parent && !parent_is_object && !(parent_is_transform && current_is_transform_op)) {
      throw std::runtime_error(fmt::format(R"(Error while parsing "%s": node "%s" requires a Nori object as parent (at %s))",
                                           filename, node.name(), offset(node.offset_debug())));
    }

    if (tag == kScene) {
      node.append_attribute("type") = "scene";
    } else if (tag == kTransform) {
      transform.setIdentity();
    }

    PropertyList property_list;
    std::vector<MinObject*> children;
    for (pugi::xml_node &ch : node.children()) {
      auto child = parse_tag(ch, property_list, tag);
      if (child)
        children.emplace_back(child);
    }
    MinObject *result = nullptr;
    try {
      if (current_is_object) {
        check_attributes(node, {"type"});

        result = MinObjectFactory::CreateInstance(node.attribute("type").value(), property_list);

        if (result->GetClassType() != (int) tag) {
          throw std::runtime_error(fmt::format("Unexpectedly constructed an object "
                                               "of type <%s> (expected type <%s>): %s",
                                               MinObject::ClassType(result->GetClassType()),
                                               MinObject::ClassType((MinObject::ClassType) tag),
                                               result->ToString()));
        }

        // Add all children
        for (auto ch : children) {
          result->AddChild(ch);
          ch->SetParent(result);
        }

        result->Activate();
      } else {
        // This is a property

      }
    }

  };
}

MIN_NAMESPACE_END

