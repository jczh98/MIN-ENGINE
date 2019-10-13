/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#include <min/opengl/model.h>

MIN_NAMESPACE_BEGIN

uint gl::TextureFromFile(const char *path, const std::string &directory, bool gamma) {
  std::string filename = std::string(path);
  filename = directory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents==1)
      format = GL_RED;
    else if (nrComponents==3)
      format = GL_RGB;
    else if (nrComponents==4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

void gl::Model::LoadModel(const std::string &path) {
  Assimp::Importer importer;
  const auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    std::cout << "ERROR::ASSIMP" << importer.GetErrorString() << std::endl;
    return;
  }
  dir_ = path.substr(0, path.find_last_of('/'));
  ProcessNode(scene->mRootNode, scene);
}

void gl::Model::ProcessNode(aiNode *node, const aiScene *scene) {
  for (uint i = 0; i < node->mNumMeshes; i++) {
    auto mesh = scene->mMeshes[node->mMeshes[i]];
    meshes_.emplace_back(ProcessMesh(mesh, scene));
  }
  for (uint i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i], scene);
  }
}
gl::Mesh gl::Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<Vertex> vertices;
  std::vector<uint> indices;
  std::vector<Texture> textures;
  // Walk through each of the mesh's vertices
  for (uint i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    Vector3 vector;
    // Positions
    vector.x() = mesh->mVertices[i].x;
    vector.y() = mesh->mVertices[i].y;
    vector.z() = mesh->mVertices[i].z;
    vertex.pos = vector;
    // Normals
    vector.x() = mesh->mNormals[i].x;
    vector.y() = mesh->mNormals[i].y;
    vector.z() = mesh->mNormals[i].z;
    // Texture coordinates
    if (mesh->mTextureCoords[0]) {
      // Exists
      Vector2 vec;
      vec.x() = mesh->mTextureCoords[0][i].x;
      vec.y() = mesh->mTextureCoords[0][i].y;
      vertex.text_coords = vec;
    } else {
      vertex.text_coords = Vector2(0.0f, 0.0f);
    }
    // Tangent
    vector.x() = mesh->mTangents[i].x;
    vector.y() = mesh->mTangents[i].y;
    vector.z() = mesh->mTangents[i].z;
    vertex.tangent = vector;
    // Bitangent
    vector.x() = mesh->mBitangents[i].x;
    vector.y() = mesh->mBitangents[i].y;
    vector.z() = mesh->mBitangents[i].z;
    vertex.bitangent = vector;
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

std::vector<gl::Texture> gl::Model::LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string name) {
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
      texture.id = TextureFromFile(str.C_Str(), this->dir_);
      texture.type = name;
      texture.path = str.C_Str();
      textures.emplace_back(texture);
      textures_loaded_.emplace_back(texture);
    }
  }
  return textures;
}

MIN_NAMESPACE_END