#pragma once
#include"Transform.h"
namespace RR {
	class Light : public Object {
	private:
		std::shared_ptr<Transform> transform;
		glm::vec4 color;
		float intensity;
	public:
		void Moveto(const glm::vec3& position);
		glm::vec3 Getpos();
		glm::vec4 GetColor();
		float Getintensity();
		void Start() override;
		void Update() override;
		Light();
	};
}