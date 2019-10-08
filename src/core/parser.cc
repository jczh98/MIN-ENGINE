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
}

MIN_NAMESPACE_END

