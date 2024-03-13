#pragma once
#include "Transform.h"
#include "Mesh.h"
#include"Control.h"
namespace RR {
	enum CamType {
		Perspective = 0,
		Orthogonal
	};
	/// <summary>
	/// œ‡ª˙¿‡
	/// </summary>
	class Camera : public  Object {
	private:
		glm::mat4 view;
		glm::mat4 projecton;
		std::shared_ptr<Transform> transform;
		float fov, nearp, farp;
		int width, height;
	public:
		std::shared_ptr<Control> control;
		int index;
		CamType type;
		Camera();
		void Changetype(const CamType& type);
		void Setpers(const float& fov, const int& width, const int& height, const float& nearp, const float& farp);
		void Setorth(const int& width, const int& height, const float& nearp, const float& farp);
		void MoveTo(const glm::vec3& pos);
		glm::mat4 Getview();
		glm::mat4 Getprojection();
		void Start() override;
		void Update()override;
	};
}