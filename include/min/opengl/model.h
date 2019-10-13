/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>
#include "mesh.h"

MIN_NAMESPACE_BEGIN
namespace gl {

extern unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model {
 public:
  Model(const std::string &path, bool gamma = false) : gamma_correction_(gamma) {
    LoadModel(path);
  }
  void Draw(Shader shader) {
    for (uint i = 0; i < meshes_.size(); i++) {
      meshes_[i].Draw(shader);
    }
  }
 private:
  void LoadModel(const std::string &path);

  void ProcessNode(aiNode *node, const aiScene *scene);

  Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

  std::vector<Texture> LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string name);

  std::vector<Texture> textures_loaded_;
  std::vector<Mesh> meshes_;
  std::string dir_;
  bool gamma_correction_;
};

}
MIN_NAMESPACE_END