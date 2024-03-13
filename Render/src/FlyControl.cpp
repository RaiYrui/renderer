#include"FlyControl.h"
namespace RR {
	
	FlyControl::FlyControl(std::shared_ptr<Camera> cam) {
		this->camera = cam;
		 Func Fly_keyboard =  [&](int key) {
			if (key == GLFW_KEY_W) {
				this->camera->MoveTo(glm::vec3(0, 0, 1));
				std::cout << "fuck";
			}
			else if (key == GLFW_KEY_A) {
				this->camera->MoveTo(glm::vec3(-1, 0, 0));
			}
			else if (key == GLFW_KEY_D) {
				this->camera->MoveTo(glm::vec3(1, 0, 0));
			}
			else if (key == GLFW_KEY_S) {
				this->camera->MoveTo(glm::vec3(0, 0, -1));
			}
		};
		EventList["Keyboard"].emplace_back(Fly_keyboard);
	}
	FlyControl::FlyControl() {
	}
}