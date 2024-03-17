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
	Control::Control() {
		//glfwSetKeyCallback(Window::glfw_window, Keyboard_action);
	}
	void Control::ToString() {
		std::cout << "Control" << std::endl;
	}
	void Control::Input() {

	}
}