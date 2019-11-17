// MIT License
// 
// Copyright (c) 2018-2019, neverfelly <neverfelly@gmail.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include "model.h"

namespace min::engine {

void Model::LoadModel(const std::string &path) {
  Assimp::Importer importer;
  const auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    std::cout << "ERROR::ASSIMP" << importer.GetErrorString() << std::endl;
    return;
  }
  dir_ = path.substr(0, path.find_last_of('/'));
  ProcessNode(scene->mRootNode, scene);
}
void Model::ProcessNode(aiNode *node, const aiScene *scene) {
  for (uint i = 0; i < node->mNumMeshes; i++) {
    auto mesh = scene->mMeshes[node->mMeshes[i]];
    meshes_.emplace_back(ProcessMesh(mesh, scene));
  }
  for (uint i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i], scene);
  }
}
Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<Vertex> vertices;
  std::vector<uint> indices;
  std::vector<Texture> textures;
  // Walk through each of the mesh's vertices
  for (uint i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    Vector3f vector;
    // Positions
    vector.x() = mesh->mVertices[i].x;
    vector.y() = mesh->mVertices[i].y;
    vector.z() = mesh->mVertices[i].z;
    vertex.position = vector;
    // Normals
    vector.x() = mesh->mNormals[i].x;
    vector.y() = mesh->mNormals[i].y;
    vector.z() = mesh->mNormals[i].z;
    // Texture coordinates
    if (mesh->mTextureCoords[0]) {
      // Exists
      Vector2f vec;
      vec.x() = mesh->mTextureCoords[0][i].x;
      vec.y() = mesh->mTextureCoords[0][i].y;
      vertex.tex_coords = vec;
    } else {
      vertex.tex_coords = Vector2f(0.0f, 0.0f);
    }
    //// Tangent
    //vector.x() = mesh->mTangents[i].x;
    //vector.y() = mesh->mTangents[i].y;
    //vector.z() = mesh->mTangents[i].z;
    //vertex.tangent = vector;
    //// Bitangent
    //vector.x() = mesh->mBitangents[i].x;
    //vector.y() = mesh->mBitangents[i].y;
    //vector.z() = mesh->mBitangents[i].z;
    //vertex.bitangent = vector;
    vertices.emplace_back(vertex);
  }
  // Walk through each of the mesh's face
  for (uint i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (uint j = 0; j < face.mNumIndices; j++) {
      indices.emplace_back(face.mIndices[j]);
    }
  }
  auto material = scene->mMaterials[mesh->mMaterialIndex];
  // Diffuse maps
  std::vector<Texture> diffuse_maps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
  textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());
  // Specular maps
  std::vector<Texture> specular_maps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
  textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
  // Normal maps
  std::vector<Texture> normal_maps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
  textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());
  // Height maps
  std::vector<Texture> height_maps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
  textures.insert(textures.end(), height_maps.begin(), height_maps.end());

  return Mesh(vertices, indices, textures);
}
std::vector<Texture> Model::LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string name) {
  std::vector<Texture> textures;
  for (uint i = 0; i < material->GetTextureCount(type); i++) {
    aiString str;
    material->GetTexture(type, i, &str);
    // Check if texture was loaded
    bool skip = false;
    for (uint j = 0; j < textures_loaded_.size(); j++) {
      if (std::strcmp(textures_loaded_[j].path.data(), str.C_Str())==0) {
        textures.emplace_back(textures_loaded_[j]);
        skip = true;
        break;
      }
    }
    if (!skip) {
      Texture texture;
      texture.type = name;
      texture.path = this->dir_ + str.C_Str();
      textures.emplace_back(texture);
      textures_loaded_.emplace_back(texture);
    }
  }
  return textures;
}

}
