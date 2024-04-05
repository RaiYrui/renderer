#pragma once
#include "Transform.h"
#include "Mesh.h"
#include"Control.h"
#include"Skybox.h"
namespace RR {
	/// <summary>
	/// œ‡ª˙¿‡
	/// </summary>
	class Camera : public  Object {
	private:
		std::shared_ptr<Uniform> view;
		std::shared_ptr<Uniform> projecton;
		std::shared_ptr<Uniform> campos;
		std::shared_ptr<Transform> transform;
		float fov, nearp, farp;
		int width, height;
		GLfloat yaw, pitch;
		glm::vec3 front;
	public:
		std::shared_ptr<Control> control;
		int index;
		CamType type;
		Camera();
		void Changetype(const CamType& type);
		void Setpers(const float& fov, const int& width, const int& height, const float& nearp, const float& farp);
		void Setorth(const int& width, const int& height, const float& nearp, const float& farp);
		void MoveTo(const glm::vec3& pos);
		void Rotate(const glm::vec3& axis, const float& angle);
		void Input(const double& x,const double& y);
		glm::vec3 Forward();
		glm::vec3 Right();
		glm::vec3 Up();
		glm::mat4 Getview();
		glm::mat4 Getprojection();
		void Start() override;
		void Update()override;
		void component_dis()override;
	};
}