#include "application.h"
#include "controller.h"

using namespace min::engine;

class SandBoxLayer : public Layer {
 public:
  SandBoxLayer() {
    controller_ = std::make_unique<Controller>(1280.0f/720.0f);
  }
  void OnAttach() override {
  }
  void OnDetach() override {
  }
  void OnUpdate(TimeStep ts) override {
    controller_->OnUpdate(ts);
    Renderer::SetClearColor({0.1, 0.1, 0.1, 1});
    Renderer::Clear();
  }
  void OnImGuiRender() override {
  }
  void OnEvent(Event &event) override {
    controller_->OnEvent(event);
  }
 private:
  std::unique_ptr<Controller> controller_;
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