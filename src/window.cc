// MIT License
// 
// Copyright (c) 2018-2019, neverfelly <neverfelly@gmail.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "window.h"


namespace min::engine {

static uint GLFWWindow_count = 0;

static void GLFWErrorCallback(int error, const char* description)
{
  log::Log("GLFW Error ({0}): {1}", error, description);
}

Window::Window(const WindowProps &props) {
  Init(props);
}
Window::~Window() {
  Shutdown();
}
void Window::OnUpdate() {
  glfwPollEvents();
  context_->SwapBuffers();
}
void Window::SetVSync(bool enabled) {
  glfwSwapInterval((int) enabled);
  data_.vsync = enabled;
}
bool Window::IsVSync() const {
  return data_.vsync;
}
void Window::Init(const WindowProps &props) {
  data_.title = props.title;
  data_.width = props.width;
  data_.height = props.height;
  log::Log("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

  if (GLFWWindow_count == 0) {
    int success = glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    if (success == GLFW_FALSE) {
      log::Log("Could not initialize GLFW!");
      return;
    }
    glfwSetErrorCallback(GLFWErrorCallback);
  }

  window_ = glfwCreateWindow(data_.width, data_.height, data_.title.c_str(), nullptr, nullptr);
  ++GLFWWindow_count;

  context_ = std::make_unique<GLContext>(window_);
  context_->Init();
  glfwSetWindowUserPointer(window_, &data_);
  SetVSync(true);

  // Set GLFW callbacks
  glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
    data.width = width;
    data.height = height;

    WindowResizeEvent event(width, height);
    data.event_callback_fn(event);
  });

  glfwSetWindowCloseCallback(window_, [](GLFWwindow* window)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    data.event_callback_fn(event);
  });

  glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    switch (action)
    {
      case GLFW_PRESS:
      {
        KeyPressedEvent event(key, 0);
        data.event_callback_fn(event);
        break;
      }
      case GLFW_RELEASE:
      {
        KeyReleasedEvent event(key);
        data.event_callback_fn(event);
        break;
      }
      case GLFW_REPEAT:
      {
        KeyPressedEvent event(key, 1);
        data.event_callback_fn(event);
        break;
      }
    }
  });

  glfwSetCharCallback(window_, [](GLFWwindow* window, unsigned int keycode)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    KeyTypedEvent event(keycode);
    data.event_callback_fn(event);
  });

  glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    switch (action)
    {
      case GLFW_PRESS:
      {
        MouseButtonPressedEvent event(button);
        data.event_callback_fn(event);
        break;
      }
      case GLFW_RELEASE:
      {
        MouseButtonReleasedEvent event(button);
        data.event_callback_fn(event);
        break;
      }
    }
  });

  glfwSetScrollCallback(window_, [](GLFWwindow* window, double xOffset, double yOffset)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    MouseScrolledEvent event((float)xOffset, (float)yOffset);
    data.event_callback_fn(event);
  });

  glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xPos, double yPos)
  {
    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    MouseMovedEvent event((float)xPos, (float)yPos);
    data.event_callback_fn(event);
  });
}
void Window::Shutdown() {
  glfwDestroyWindow(window_);
  --GLFWWindow_count;
  if (GLFWWindow_count) {
    glfwTerminate();
  }
}
std::unique_ptr<Window> Window::Create(const WindowProps &props) {
  return std::make_unique<Window>(props);
}
}