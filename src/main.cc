/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/min.h>
#include <boost/filesystem.hpp>
#include <min/core/object.h>
#include <min/io/resolver.h>
#include <min/core/parser.h>

namespace fs = boost::filesystem;

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Syntax: " << argv[0] << " <scene.xml>" << std::endl;
    return -1;
  }
  fs::path path(argv[1]);
  try {
    if (path.extension() == "xml") {
      min::GetFileResolver()->Append(path.parent_path());
      std::unique_ptr<min::MinObject> root(min::LoadFromXML(argv[1]));
    }
  } catch (const std::exception &e) {
    std::cerr << "Fatal error: " << e.what() << std::endl;
    return -1;
  }

  return 0;
}

