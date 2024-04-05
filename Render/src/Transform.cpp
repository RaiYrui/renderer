#include "Transform.h"
namespace RR {
	Transform::Transform() {
		this->pos = glm::mat4(1.0f);
		this->localPosition = glm::vec3();
		this->localRotation = glm::vec3();
		this->localScale = glm::vec3(1.0f);
		this->translation_mat = glm::mat4(1.0f);
		this->rotation_mat = glm::mat4(1.0f);
		this->scale_mat = glm::mat4(1.0f);
		this->up = glm::vec3(0, 1, 0);
		this->eu_angle = glm::vec3();
		this->model = std::make_shared<Uniform>(Mat4, glm::mat4(1.0f));
		Mesh::global_uniform["model"] = this->model;
	}
	glm::vec3 Transform::Position() {
		return this->localPosition;
	}
	glm::mat4 Transform::Pos_mat() {
		return this->pos;
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
		this->localScale = scale;
	}

	void Transform::Start() {
		std::cout << "Transform start" << std::endl;
	}
	void Transform::Update() {
		this->translation_mat = glm::translate(glm::mat4(1.0f), this->localPosition);
		this->rotation_mat = glm::mat4_cast(this->localRotation);
		this->scale_mat = glm::scale(glm::mat4(1.0f), this->localScale);
		this->pos = this->translation_mat  * this->rotation_mat* this->scale_mat*glm::mat4(1.0f);
		this->model->data.Mat4 = this->pos;
		Mesh::global_uniform["model"]->data.Mat4 = this->pos;
	}
	void Transform::Destroy() {

	}
	void Transform::Inspector_dis() {
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
			
			ImGui::Separator();
			ImGui::Text("Position");
			ImGui::DragFloat("Position x", &this->localPosition.x, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
			ImGui::DragFloat("Position y", &this->localPosition.y, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
			ImGui::DragFloat("Position z", &this->localPosition.z, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
			ImGui::Separator();
			ImGui::Text("Rotation");
			this->eu_angle =  glm::eulerAngles(this->localRotation);
			ImGui::DragFloat("Angle x", &this->eu_angle.x, 0.005f, -FLT_MAX, FLT_MAX, "%.3f");
			ImGui::DragFloat("Angle y", &this->eu_angle.y, 0.005f, -FLT_MAX, FLT_MAX, "%.3f");
			ImGui::DragFloat("Angle z", &this->eu_angle.z, 0.005f, -FLT_MAX, FLT_MAX, "%.3f");
			this->localRotation = glm::quat(this->eu_angle);
			ImGui::Separator();
			ImGui::Text("Scale");
			ImGui::DragFloat("Scale x", &this->localScale.x, 0.1f, 0.0f, FLT_MAX, "%.2f");
			ImGui::DragFloat("Scale y", &this->localScale.y, 0.1f, 0.0f, FLT_MAX, "%.2f");
			ImGui::DragFloat("Scale z", &this->localScale.z, 0.1f, 0.0f, FLT_MAX, "%.2f");

			
		}
	}
	glm::vec3 Transform::Foward() {
		return glm::normalize(this->localRotation * glm::vec4(glm::vec3(0, 0, 1), 0.0f));
	}
	Transform::~Transform() {

	}
}