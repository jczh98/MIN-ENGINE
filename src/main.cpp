#include "application.h"
#include "controller.h"
#include "gl_shader.h"

using namespace min::engine;

class SandBoxLayer : public Layer {
 public:
  SandBoxLayer() {
    controller_ = std::make_unique<Controller>(1280.0f/720.0f);
  }
  void OnAttach() override {
    light_shader_ = std::make_shared<GLShader>("assets/shaders/colors.vs.glsl", "assets/shaders/colors.fs.glsl");
    lamp_shader_ = std::make_shared<GLShader>("assets/shaders/lamp.vs.glsl", "assets/shaders/lamp.fs.glsl");
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
  }
  void OnDetach() override {
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
  }
  void OnUpdate(TimeStep ts) override {
    controller_->OnUpdate(ts);
    Renderer::SetClearColor({0.1, 0.1, 0.1, 1});
    Renderer::Clear();
    light_shader_->Use();
    light_shader_->UploadUniformFloat3("objectColor", {1.0f, 0.5f, 0.31f});
    light_shader_->UploadUniformFloat3("lightColor", {1.0f, 1.0f, 1.0f});
    // view/projection transformations
    using namespace nf;
    auto& window = Application::Get().GetWindow();
    Matrix4f  projection = math::Perspective(math::radians(controller_->zoom_level), window.GetWidth() / window.GetHeight(), 0.1f, 100.0f);
    Matrix4f view = controller_->camera.view;
    light_shader_->UploadUniformMat4("projection", projection);
    light_shader_->UploadUniformMat4("view", view);

    // world transformation
    Matrix4f model = Matrix4f::Identity();
    light_shader_->UploadUniformMat4("model", model);
    // render the cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // also draw the lamp object
    lamp_shader_->Use();
    lamp_shader_->UploadUniformMat4("projection", projection);
    lamp_shader_->UploadUniformMat4("view", view);
    model = Matrix4f::Identity();
    Vector3f light_pos = Vector3f(1.2f, 1.0f, 2.0f);
    Eigen::Affine3f t = Eigen::Affine3f::Identity();
    t.translate(Vector3f(1.2f, 1.0f, 2.0f));
    t.scale(0.2f);
    model = t.matrix();
    lamp_shader_->UploadUniformMat4("model", model);

    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
  void OnImGuiRender() override {
  }
  void OnEvent(Event &event) override {
    controller_->OnEvent(event);
  }
  unsigned int VBO, cubeVAO, lightVAO;
 private:
  std::unique_ptr<Controller> controller_;
  std::shared_ptr<GLShader> light_shader_, lamp_shader_;
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