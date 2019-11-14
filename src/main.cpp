#include "application.h"
#include "gl_shader.h"
#include "gl_vertex_array.h"
#include "controller.h"
#include "gl_texture.h"

using namespace min::engine;

class SandBoxLayer : public Layer {
 public:
  SandBoxLayer() {
    controller_ = std::make_unique<Controller>(1280.0f/720.0f);
  }
  void OnAttach() override {
    light_shader_ = std::make_shared<GLShader>("assets/shaders/colors.vs.glsl", "assets/shaders/colors.fs.glsl");
    lamp_shader_ = std::make_shared<GLShader>("assets/shaders/lamp.vs.glsl", "assets/shaders/lamp.fs.glsl");
    texture_ = std::make_shared<GLTexture>("assets/textures/container2.png");
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    lamp_ = std::make_shared<GLVertexArray>();
    light_ = std::make_shared<GLVertexArray>();
    quad_ = std::make_shared<GLVertexBuffer>(vertices, sizeof(vertices));
    BufferLayout layout = {
        { ShaderDataType::Float3, "aPos"},
        { ShaderDataType::Float3, "aNormal"},
        { ShaderDataType::Float2, "aTexCoords"}
    };
    quad_->SetLayout(layout);
    light_->AddVertexBuffer(quad_);
    lamp_->AddVertexBuffer(quad_);
    light_shader_->Use();
    light_shader_->UploadUniformInt("material.diffuse", 0);
  }
  void OnDetach() override {
    light_->Unbind();
    lamp_->Unbind();
    quad_->Unbind();
  }
  void OnUpdate(TimeStep ts) override {
    controller_->OnUpdate(ts);
    Renderer::SetClearColor({0.1, 0.1, 0.1, 1});
    Renderer::Clear();
    light_shader_->Use();
    light_shader_->UploadUniformFloat3("material.specular", {0.5f, 0.5f, 0.5f});
    light_shader_->UploadUniformFloat("material.shininess", 64.0f);
    light_shader_->UploadUniformFloat3("light.ambient", {0.2f, 0.2f, 0.2f});
    light_shader_->UploadUniformFloat3("light.diffuse", {0.5f, 0.5f, 0.5f});
    light_shader_->UploadUniformFloat3("light.specular", {1.0f, 1.0f, 1.0f});
    // view/projection transformations
    Matrix4f projection = controller_->camera.GetProjectionMatrix();
    Matrix4f view = controller_->camera.GetViewMatrix();
    light_shader_->UploadUniformMat4("projection", projection);
    light_shader_->UploadUniformMat4("view", view);
    Vector3f light_pos = Vector3f(1.2f, 1.0f, 2.0f);
    light_shader_->UploadUniformFloat3("light.position", light_pos);
    light_shader_->UploadUniformFloat3("view_pos", controller_->camera.position());
    // world transformation
    Matrix4f model = Matrix4f::Identity();
    light_shader_->UploadUniformMat4("model", model);
    // Bind diffuse map
    texture_->Bind();
    // render the cube
    light_->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // also draw the lamp object
    lamp_shader_->Use();
    lamp_shader_->UploadUniformMat4("projection", projection);
    lamp_shader_->UploadUniformMat4("view", view);
    model = Matrix4f::Identity();
    Eigen::Affine3f t = Eigen::Affine3f::Identity();
    t.translate(light_pos);
    t.scale(0.2f);
    model = t.matrix();
    lamp_shader_->UploadUniformMat4("model", model);

    lamp_->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
  void OnImGuiRender() override {
  }
  void OnEvent(Event &event) override {
    controller_->OnEvent(event);
  }
 private:
  std::unique_ptr<Controller> controller_;
  std::shared_ptr<GLShader> light_shader_, lamp_shader_;
  std::shared_ptr<GLVertexArray> light_, lamp_;
  std::shared_ptr<GLVertexBuffer> quad_;
  std::shared_ptr<GLTexture> texture_;
};
class SandBox : public Application {
 public:
  SandBox() {
    PushLayer(std::make_shared<SandBoxLayer>());
  }
};
int main() {
  auto app = std::make_unique<SandBox>();
  app->Run();
  return 0;
}