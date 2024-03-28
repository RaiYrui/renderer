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
		this->localPosition += position;
	}
	void Transform::Rotate(const glm::vec3& axis,const float& angle) {
		this->localRotation = glm::angleAxis(glm::radians(angle), axis) * this->localRotation;
	}
	void Transform::Scale(const glm::vec3& scale) {
		this->localScale.x *= scale.x;
		this->localScale.y *= scale.y;
		this->localScale.z *= scale.z;
	}

	void Transform::Start() {
		std::cout << "Transform start" << std::endl;
	}
	void Transform::Update() {
		this->translation_mat = glm::translate(glm::mat4(1.0f), this->localPosition);
		this->rotation_mat = glm::mat4_cast(this->localRotation);
		this->scale_mat = glm::scale(glm::mat4(1.0f), this->localScale);
		this->pos = this->translation_mat * this->rotation_mat * this->scale_mat * this->pos;
	}
	void Transform::Destroy() {

	}
	void Transform::Inspector_dis() {
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::DragFloat("Position x", &this->localPosition.x, 0.5f, -FLT_MAX, FLT_MAX, "%.3f");
			ImGui::DragFloat("Position y", &this->localPosition.y, 0.5f, -FLT_MAX, FLT_MAX, "%.3f");
			ImGui::DragFloat("Position z", &this->localPosition.z, 0.5f, -FLT_MAX, FLT_MAX, "%.3f");
		}
	}
	glm::vec3 Transform::Foward() {
		return glm::normalize(this->localRotation * glm::vec4(glm::vec3(0, 0, 1), 0.0f));
	}
	Transform::~Transform() {

	}
}