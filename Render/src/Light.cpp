#include"Light.h"
namespace RR {
	Light::Light() {
		this->color = glm::vec4(1.0f);
		this->intensity = 10.0f;
		this->transform = std::make_shared<Transform>();
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
}