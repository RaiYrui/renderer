#include"Light.h"
namespace RR {
	int Light::id = 0;
	Light::Light() {
		this->color = glm::vec4(1.0f);
		this->intensity = 10.0f;
		this->transform = std::make_shared<Transform>();
		this->id++;
		std::string c;
		int num = this->id;
		while (num > 0) {
			int n = num % 10;
			c += (n + '0');
			num /= 10;
		}
		this->name = "Light" + c;
	}
	void Light::Moveto(const glm::vec3& position) {
		this->transform->Translate(position);
	}
	void Light::Start() {
		this->Moveto(glm::vec3(0, 5, 0));
	}
	void Light::Update() {

	}
	glm::vec3 Light::Getpos() {
		return this->transform->Position();
	}
	glm::vec4 Light::GetColor() {
		return this->color;
	}
	float Light::Getintensity() {
		return this->intensity;
	}
	void Light::component_dis() {
		this->transform->Inspector_dis();

	}
}