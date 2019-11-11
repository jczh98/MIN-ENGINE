#include "application.h"

using namespace min::engine;

class SandBoxLayer : public Layer {
 public:
  SandBoxLayer() {}
  void OnAttach() override {
    Layer::OnAttach();
  }
  void OnDetach() override {
    Layer::OnDetach();
  }
  void OnUpdate(TimeStep ts) override {
    Layer::OnUpdate(ts);
  }
  void OnImGuiRender() override {
    Layer::OnImGuiRender();
  }
  void OnEvent(Event &event) override {
    Layer::OnEvent(event);
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