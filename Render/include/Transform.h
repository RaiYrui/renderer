#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/quaternion.hpp>
#include"Component.h"
namespace RR {
	/// <summary>
	/// Transform类描述物体的变换信息
	/// </summary>
	class Transform : public Component {
	private:
		glm::vec3 localPosition;
		glm::quat localRotation;
		glm::vec3 localScale;
		glm::mat4 pos;
		glm::mat4 translation_mat;
		glm::mat4 rotation_mat;
		glm::mat4 scale_mat;
		glm::vec3 up;
	public:
		void Start()override;
		void Update()override;
		void Destroy()override;
		void Inspector_dis()override;
		Transform();
		void Translate(const glm::vec3& position);
		void Rotate(const glm::vec3& axis,const float& angle);
		void Scale(const glm::vec3& scale);
		glm::vec3 Position();
		glm::vec3 Up();
		glm::vec3 Foward();
		~Transform();
	};
}