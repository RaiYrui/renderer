#include "Camera.h"
namespace RR {
	Camera::Camera() {
		this->transform = std::make_shared<Transform>();
		this->transform->Translate(glm::vec3(5.0f, 1.0f, -15.0f));
		this->transform->Rotate(glm::vec3(0, 1, 0), -20);
		this->Setpers(45.0f, 1200, 900, 0.1f, 100.0f);
		this->view = glm::lookAt(this->transform->Position(), this->transform->Position() + this->transform->Foward(), this->transform->Up());
		this->Changetype(Perspective);
		this->projecton = this->Getprojection();
	}
	void Camera::Setpers(const float& fov, const int& width, const int& height, const float& nearp, const float& farp) {
		this->fov = fov;
		this->width = width;
		this->height = height;
		this->nearp = nearp;
		this->farp = farp;
	}
	void Camera::Setorth(const int& width, const int& height, const float& nearp, const float& farp) {
		this->width = width;
		this->height = height;
		this->nearp = nearp;
		this->farp = farp;
	}
	void Camera::Changetype(const CamType& type) {
		this->type = type;
		if (this->type == Perspective) {
			this->projecton = glm::perspective(glm::radians(this->fov), (float)this->width / this->height, this->nearp, this->farp);
		}
		else {
			this->projecton = glm::ortho(-(this->width / 2.0f), (this->width / 2.0f), -(this->height / 2.0f), (this->height / 2.0f));
		}
	}
	glm::mat4 Camera::Getprojection() {
		return this->projecton;
	}
	glm::mat4 Camera::Getview() {
		return this->view;
	}
	void Camera::Start() {

	}
	void Camera::Update() {
		this->control->Input();
		this->view = glm::lookAt(this->transform->Position(), this->transform->Position() + this->transform->Foward(), this->transform->Up());
		this->projecton = this->Getprojection();
		Mesh::projection = this->projecton;
		Mesh::view = this->view;
		Mesh::campos = this->transform->Position();
	}
	void Camera::MoveTo(const glm::vec3& pos) {
		this->transform->Translate(pos);
	}
	void Camera::Rotate(const glm::vec3& axis, const float& angle) {
		this->transform->Rotate(axis, angle);
	}
	glm::vec3 Camera::Forward() {
		return this->transform->Foward();
	}
	glm::vec3 Camera::Right() {
		return glm::normalize(glm::cross(this->transform->Foward(), this->transform->Up()));
	}
	glm::vec3 Camera::Up() {
		return this->transform->Up();
	}
}