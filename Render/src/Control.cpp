#include"Control.h"
namespace RR {
	std::unordered_map<std::string, std::vector<Func>>EventList;
	void Cursor_action(GLFWwindow* window, double xpos, double ypos) {

	}
	void Keyboard_action(GLFWwindow* window, int key, int scancode, int action, int mods) {
		for (Func f : EventList["Keyboard"]) {
			f(key);
		}
	}
	Window* Control::window = nullptr;
	Control::Control() {
		//glfwSetKeyCallback(Window::glfw_window, Keyboard_action);
		this->selected = false;
		this->window = Window::getInstance();
	}
	void Control::ToString() {
		std::cout << "Control" << std::endl;
	}
	void Control::Input() {
		glfwGetCursorPos(Window::glfw_window, &c_xpos, &c_ypos);
		if (glfwGetMouseButton(Window::glfw_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			if (c_xpos > this->window->H_width && c_xpos < this->window->H_width + this->window->gl_width
				&&c_ypos<this->window->gl_height) {
				this->selected = true;
			}
			else {
				this->selected = false;
			}
		}
	}
}