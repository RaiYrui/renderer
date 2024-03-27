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
		this->widget = std::make_shared<UWidget>(this->world);
		this->widget->Init();
		glViewport(this->window->H_width, this->window->height - this->window->gl_height, this->window->gl_width, this->window->gl_height);
		while (!glfwWindowShouldClose(window->glfw_window))
		{
			glViewport(this->window->H_width, this->window->height - this->window->gl_height, this->window->gl_width, this->window->gl_height);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->world->Startp();
			this->widget->updategui();
			glfwSwapBuffers(window->glfw_window);
			glfwPollEvents();
			glfwGetWindowSize(this->window->glfw_window, &this->window->width, &this->window->height);
			this->window->Resize();
		}
		Stop();
	}
	void Application::Stop() {
		window->Close();
		delete window;
		window = nullptr;
	}
}