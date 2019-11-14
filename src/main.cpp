#include "application.h"
#include "gl_shader.h"
#include "gl_vertex_array.h"
#include "controller.h"
#include "gl_texture.h"

using namespace min::engine;

class SandBoxLayer : public Layer {
 public:
  SandBoxLayer() {
    controller_ = std::make_unique<Controller>(1280.0f / 720.0f);
  }
  void OnAttach() override {
    light_shader_ = std::make_shared<GLShader>("assets/shaders/point_light.vs.glsl", "assets/shaders/point_light.fs.glsl");
    lamp_shader_ = std::make_shared<GLShader>("assets/shaders/lamp.vs.glsl", "assets/shaders/lamp.fs.glsl");
    diffuse_map_ = std::make_shared<GLTexture>("assets/textures/container2.png");
    specular_map_ = std::make_shared<GLTexture>("assets/textures/container2_specular.png");
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };
    cube_position_ = {
        Vector3f(0.0f, 0.0f, 0.0f),
        Vector3f(2.0f, 5.0f, -15.0f),
        Vector3f(-1.5f, -2.2f, -2.5f),
        Vector3f(-3.8f, -2.0f, -12.3f),
        Vector3f(2.4f, -0.4f, -3.5f),
        Vector3f(-1.7f, 3.0f, -7.5f),
        Vector3f(1.3f, -2.0f, -2.5f),
        Vector3f(1.5f, 2.0f, -2.5f),
        Vector3f(1.5f, 0.2f, -1.5f),
        Vector3f(-1.3f, 1.0f, -1.5f)
    };
    lamp_ = std::make_shared<GLVertexArray>();
    light_ = std::make_shared<GLVertexArray>();
    quad_ = std::make_shared<GLVertexBuffer>(vertices, sizeof(vertices));
    BufferLayout layout = {
        {ShaderDataType::Float3, "aPos"},
        {ShaderDataType::Float3, "aNormal"},
        {ShaderDataType::Float2, "aTexCoords"}
    };
    quad_->SetLayout(layout);
    light_->AddVertexBuffer(quad_);
    lamp_->AddVertexBuffer(quad_);
    light_shader_->Use();
    light_shader_->UploadUniformInt("material.diffuse", 0);
    light_shader_->UploadUniformInt("material.specular", 1);
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

    Vector3f light_pos = Vector3f(1.2f, 1.0f, 2.0f);
    light_shader_->Use();
    light_shader_->UploadUniformFloat("material.shininess", 32.0f);
    light_shader_->UploadUniformFloat3("light.ambient", {0.2f, 0.2f, 0.2f});
    light_shader_->UploadUniformFloat3("light.diffuse", {0.5f, 0.5f, 0.5f});
    light_shader_->UploadUniformFloat3("light.specular", {1.0f, 1.0f, 1.0f});
    light_shader_->UploadUniformFloat3("light.position", light_pos);
    light_shader_->UploadUniformFloat("light.constant", 1.0f);
    light_shader_->UploadUniformFloat("light.linear", 0.09f);
    light_shader_->UploadUniformFloat("light.quadratic", 0.032f);
    Matrix4f projection = controller_->camera.GetProjectionMatrix();
    Matrix4f view = controller_->camera.GetViewMatrix();
    light_shader_->UploadUniformMat4("projection", projection);
    light_shader_->UploadUniformMat4("view", view);
    light_shader_->UploadUniformFloat3("view_pos", controller_->camera.position());
    Matrix4f model = Matrix4f::Identity();
    light_shader_->UploadUniformMat4("model", model);
    diffuse_map_->Bind(GL_TEXTURE0);
    specular_map_->Bind(GL_TEXTURE1);
    light_->Bind();
    for (uint i = 0; i < 10; i++) {
      Eigen::Affine3f t = Eigen::Affine3f::Identity();
      t.translate(cube_position_[i]);
      float angle = 20.0f * i;
      Eigen::AngleAxisf rotate(nf::math::radians(angle), Vector3f(1.0f, 0.3f, 0.5f));
      t.rotate(rotate);
      light_shader_->UploadUniformMat4("model", t.matrix());
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
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
  std::vector<Vector3f> cube_position_;
  std::unique_ptr<Controller> controller_;
  std::shared_ptr<GLShader> light_shader_, lamp_shader_;
  std::shared_ptr<GLVertexArray> light_, lamp_;
  std::shared_ptr<GLVertexBuffer> quad_;
  std::shared_ptr<GLTexture> diffuse_map_, specular_map_;
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