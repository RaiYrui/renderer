#include"FlyControl.h"
namespace RR {
	FlyControl::FlyControl(std::shared_ptr<Camera> cam) {
		this->camera = cam;
		this->c_xpos = 0;
		this->c_ypos = 0;
		this->pressed = false;
		this->xlast = 0;
		this->ylast = 0;
	}
	FlyControl::FlyControl() {
		this->camera = nullptr;
		this->c_xpos = 0;
		this->c_ypos = 0;
		this->pressed = false;
		this->xlast = 0;
		this->ylast = 0;
	}
	void FlyControl::Input() {
		Control::Input();
		this->KeyBoard_upadate();
		this->Cursor_update();
	}
	void FlyControl::KeyBoard_upadate() {
		if (this->selected) {
			if (glfwGetKey(Window::glfw_window, GLFW_KEY_W) == GLFW_PRESS) {
				this->camera->MoveTo(this->camera->Forward() * 0.1f);
			}
			if (glfwGetKey(Window::glfw_window, GLFW_KEY_A) == GLFW_PRESS) {
				this->camera->MoveTo(-this->camera->Right() * 0.1f);
			}
			if (glfwGetKey(Window::glfw_window, GLFW_KEY_D) == GLFW_PRESS) {
				this->camera->MoveTo(this->camera->Right() * 0.1f);
			}
			if (glfwGetKey(Window::glfw_window, GLFW_KEY_S) == GLFW_PRESS) {
				this->camera->MoveTo(-this->camera->Forward() * 0.1f);
			}
			if (glfwGetKey(Window::glfw_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
				this->camera->MoveTo(glm::vec3(0, 1, 0) * 0.1f);
			}
			if (glfwGetKey(Window::glfw_window, GLFW_KEY_C) == GLFW_PRESS) {
				this->camera->MoveTo(-glm::vec3(0, 1, 0) * 0.1f);
			}
		}
	}
	void FlyControl::Cursor_update() {
		glfwGetCursorPos(Window::glfw_window, &c_xpos, &c_ypos);
		if (this->selected) {
			if (glfwGetMouseButton(Window::glfw_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
				this->pressed = true;
			if (glfwGetMouseButton(Window::glfw_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
				this->pressed = false;
			if (this->pressed) {
				if (this->xlast < this->c_xpos)
					this->camera->Rotate(glm::vec3(0, 1, 0), -1.0f);
				else if (this->xlast > this->c_xpos)
					this->camera->Rotate(glm::vec3(0, 1, 0), 1.0f);
				if (this->ylast < this->c_ypos)
					this->camera->Rotate(glm::vec3(1, 0, 0), 1.0f);
				else if (this->ylast > this->c_ypos)
					this->camera->Rotate(glm::vec3(1, 0, 0), -1.0f);
			}
			this->xlast = c_xpos;
			this->ylast = c_ypos;
		}
	}
}