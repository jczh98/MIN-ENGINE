/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_OBJECT_H_
#define MIN_INCLUDE_MIN_CORE_OBJECT_H_

#include <min/min.h>
#include "property_list.h"

MIN_NAMESPACE_BEGIN

class MinObject {
 public:
  enum ClassType {
    kScene = 0,
    kMesh,
    kBSDF,
    kCamera,
    kIntegrator,
    kSampler,
    kFilter,

    kClassTypeCount
  };

  virtual ~MinObject();

  virtual ClassType GetClassType() const = 0;

  virtual void AddChild(MinObject *child);

  virtual void SetParent(MinObject *parent);

  virtual void Activate();

  virtual std::string ToString() const = 0;

  static std::string TypeName(ClassType type) {
    switch (type) {
      case kScene: return "scene";
      case kMesh: return "mesh";
      case kBSDF: return "bsdf";
      case kCamera: return "camera";
      case kIntegrator: return "integrator";
      case kSampler: return "sampler";
      case kFilter: return "filter";
      default: return "unknown";
    }
  }
};

class MinObjectFactory {
 public:
  typedef std::function<MinObject *(const PropertyList &)> Constructor;

  static void RegisterClass(const std::string &name, const Constructor &constructor);

  static MinObject* CreateInstance(const std::string &name,
      const PropertyList &property_list) {
    if (!constructors_ || constructors_->find(name) == constructors_->end()) {
      throw std::runtime_error(fmt::format("A constructor for class \"%s\" could not be found!", name));
    }
    return (*constructors_)[name](property_list);
  }

 private:
  static std::map<std::string, Constructor> *constructors_;
};

#define MIN_REGISTER_CLASS(cls, name) \
  cls *cls ##_create(const PropertyList &list) { \
    return new cls(list); \
  } \
  static struct cls ##_{ \
    cls ##_() { \
      MinObjectFactory::RegisterClass(name, cls ##_create); \
    } \
  } cls ##__MIN_;

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_OBJECT_H_
