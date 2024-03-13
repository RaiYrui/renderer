#include "Application.h"
namespace RR {
	Application* Application::app = nullptr;
	Window* Application::window = nullptr;
	Application::Application() {
		window = Window::getInstance();
	}
	Application* Application::getInstance() {
		if (app == nullptr)
			app = new Application();
		return app;
	}
	bool Application::Init() {
		if (window->Init()) {
			this->world = std::make_shared<World>();
			this->world->Init();
			return true;
		}
		return false;
	}
	void Application::Start() {
		while (!glfwWindowShouldClose(window->glfw_window))
		{
			glClearColor(0.8f, 0.2f, 0.3f, 1.0f);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->world->Startp();
			glfwSwapBuffers(window->glfw_window);
			glfwPollEvents();
		}
		Stop();
	}
	void Application::Stop() {
		window->Close();
		delete window;
		window = nullptr;
	}
}