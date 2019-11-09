#include "engine.h"

int main() {
  auto engine = std::make_shared<min::engine::Engine>();
  engine->Run();
  return 0;
}