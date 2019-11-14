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
    light_shader_ = std::make_shared<GLShader>("assets/shaders/multi_light.vs.glsl", "assets/shaders/multi_light.fs.glsl");
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
    point_light_positions_ = {
        Vector3f( 0.7f,  0.2f,  2.0f),
        Vector3f( 2.3f, -3.3f, -4.0f),
        Vector3f(-4.0f,  2.0f, -12.0f),
        Vector3f( 0.0f,  0.0f, -3.0f)
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

    light_shader_->Use();
    light_shader_->UploadUniformFloat3("viewPos", controller_->camera.position());
    light_shader_->UploadUniformFloat("material.shininess", 32.0f);
    Vector3f light_pos = Vector3f(1.2f, 1.0f, 2.0f);
    // Direction Light
    light_shader_->UploadUniformFloat3("dirLight.direction", {-0.2f, -1.0f, -0.3f});
    light_shader_->UploadUniformFloat3("dirLight.ambient", {0.05f, 0.05f, 0.05f});
    light_shader_->UploadUniformFloat3("dirLight.diffuse", {0.4f, 0.4f, 0.4f});
    light_shader_->UploadUniformFloat3("dirLight.specular", {0.5f, 0.5f, 0.5f});
    // SpotLight
    for (int i = 0; i < 4; i++) {
      std::string name = fmt::format("pointLights[{}].", i);
      light_shader_->UploadUniformFloat3(name+"position", point_light_positions_[i]);
      light_shader_->UploadUniformFloat3(name+"ambient", {0.05f, 0.05f, 0.05f});
      light_shader_->UploadUniformFloat3(name+"diffuse", {0.8f, 0.8f, 0.8f});
      light_shader_->UploadUniformFloat3(name+"specular", {1.0f, 1.0f, 1.0f});
      light_shader_->UploadUniformFloat(name+"constant", 1.0f);
      light_shader_->UploadUniformFloat(name+"linear", 0.09);
      light_shader_->UploadUniformFloat(name+"quadratic", 0.032);
    }
    // spotLight
    light_shader_->UploadUniformFloat3("spotLight.position", controller_->camera.position());
    light_shader_->UploadUniformFloat3("spotLight.direction", controller_->camera.direction());
    light_shader_->UploadUniformFloat3("spotLight.ambient", {0.0f, 0.0f, 0.0f});
    light_shader_->UploadUniformFloat3("spotLight.diffuse", {1.0f, 1.0f, 1.0f});
    light_shader_->UploadUniformFloat3("spotLight.specular", {1.0f, 1.0f, 1.0f});
    light_shader_->UploadUniformFloat("spotLight.constant", 1.0f);
    light_shader_->UploadUniformFloat("spotLight.linear", 0.09);
    light_shader_->UploadUniformFloat("spotLight.quadratic", 0.032);
    light_shader_->UploadUniformFloat("spotLight.cutOff", std::cos(nf::math::radians(12.5f)));
    light_shader_->UploadUniformFloat("spotLight.outerCutOff", std::cos(nf::math::radians(15.0f)));

    Matrix4f projection = controller_->camera.GetProjectionMatrix();
    Matrix4f view = controller_->camera.GetViewMatrix();
    light_shader_->UploadUniformMat4("projection", projection);
    light_shader_->UploadUniformMat4("view", view);
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
    lamp_->Bind();
    for (uint i = 0; i < 4; i++) {
      Eigen::Affine3f t = Eigen::Affine3f::Identity();
      t.translate(point_light_positions_[i]);
      t.scale(Vector3f(0.2f, 0.2f, 0.2f));
      lamp_shader_->UploadUniformMat4("model", t.matrix());
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
  }
  void OnImGuiRender() override {
  }
  void OnEvent(Event &event) override {
    controller_->OnEvent(event);
  }
 private:
  std::vector<Vector3f> cube_position_;
  std::vector<Vector3f> point_light_positions_;
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