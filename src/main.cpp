#include "application.h"

using namespace min::engine;

class SandBoxLayer : public Layer {
 public:
  SandBoxLayer() {}
  void OnAttach() override {
  }
  void OnDetach() override {
  }
  void OnUpdate(TimeStep ts) override {
  }
  void OnImGuiRender() override {
  }
  void OnEvent(Event &event) override {
  }
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