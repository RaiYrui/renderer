#include "Transform.h"
namespace RR {
	Transform::Transform() {
		this->pos = glm::mat4(1.0f);
		this->localPosition = glm::vec3();
		this->localRotation = glm::vec3();
		this->localScale = glm::vec3();
		this->translation_mat = glm::mat4(1.0f);
		this->rotation_mat = glm::mat4(1.0f);
		this->scale_mat = glm::mat4(1.0f);
		this->up = glm::vec3(0, 1, 0);
	}
	glm::vec3 Transform::Position() {
		return this->localPosition;
	}
	glm::vec3 Transform::Up() {
		return glm::normalize(this->localRotation * glm::vec4(glm::vec3(0,1,0), 0.0f));
	}
	void Transform::Translate(const glm::vec3& position) {
		this->translation_mat = glm::translate(this->translation_mat, position);
		this->localPosition.x = this->translation_mat[3][0];
		this->localPosition.y = this->translation_mat[3][1];
		this->localPosition.z = this->translation_mat[3][2];

	}
	void Transform::Rotate(const glm::vec3& axis,const float& angle) {
		this->rotation_mat = glm::rotate(this->rotation_mat, glm::radians(angle), axis);
		//赋值给旋转的变量，用旋转矩阵
		this->localRotation = glm::quat_cast(this->rotation_mat);
	}
	void Transform::Scale(const glm::vec3& scale) {
		this->scale_mat = glm::scale(this->scale_mat, scale);
		this->localScale.x *= scale.x;
		this->localScale.y *= scale.y;
		this->localScale.z *= scale.z;
	}

	void Transform::Start() {
		std::cout << "Transform start" << std::endl;
	}
	void Transform::Update() {
		this->pos = this->translation_mat * this->rotation_mat * this->scale_mat * this->pos;
	}
	void Transform::Destroy() {

	}
	glm::vec3 Transform::Foward() {
		return glm::normalize(this->localRotation * glm::vec4(glm::vec3(0, 0, 1), 0.0f));
	}
}