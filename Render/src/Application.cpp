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
			RenderPipeline::glw = this->window->gl_width;
			RenderPipeline::glh = this->window->gl_height;
			this->world = std::make_shared<World>();
			this->world->Init();
			return true;
		}
		return false;
	}
	void Application::Start() {
		this->widget = std::make_shared<UWidget>(this->world);
		this->widget->Init();
		//glViewport(this->window->H_width, this->window->height - this->window->gl_height, this->window->gl_width, this->window->gl_height);
		while (!glfwWindowShouldClose(window->glfw_window))
		{
			//glViewport(this->window->H_width, this->window->height - this->window->gl_height, this->window->gl_width, this->window->gl_height);
			glViewport(0, 0, this->window->width, this->window->height);
			RenderPipeline::glw = this->window->gl_width;
			RenderPipeline::glh = this->window->gl_height;
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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