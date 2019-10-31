/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/engine/renderer/shader.h>
#include <min/engine/renderer/opengl/gl_shader.h>

namespace min::engine {

std::shared_ptr<Shader> Shader::Create(const std::string &vert_path, const std::string &frag_path) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None: MIN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(vert_path, frag_path);
  }
  MIN_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}
std::shared_ptr<Shader> Shader::Create(const std::string &name, const std::string &vertex, const std::string &frag) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::None: MIN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertex, frag);
  }
}
void ShaderLibrary::Add(const std::string &name, const std::shared_ptr<Shader> &shader) {
  MIN_CORE_ASSERT(!Exists(name), "Shader already exists!");
  shaders_[name] = shader;
}
void ShaderLibrary::Add(const std::shared_ptr<Shader> &shader) {
  auto& name = shader->GetName();
  Add(name, shader);
}
std::shared_ptr<Shader> ShaderLibrary::Load(const std::string &vert_path, const std::string &frag_path) {
  auto shader = Shader::Create(vert_path, frag_path);
  Add(shader);
  return shader;
}
std::shared_ptr<Shader> ShaderLibrary::Load(const std::string &name, const std::string &vert_path, const std::string &frag_path) {
  auto shader = Shader::Create(vert_path, frag_path);
  Add(name, shader);
  return shader;
}
std::shared_ptr<Shader> ShaderLibrary::Get(const std::string &name) {
  MIN_CORE_ASSERT(Exists(name), "Shader not found!");
  return shaders_[name];
}
bool ShaderLibrary::Exists(const std::string &name) const {
  return shaders_.find(name) != shaders_.end();
}

}
