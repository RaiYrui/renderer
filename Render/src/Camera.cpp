#include "Camera.h"
namespace RR {
	Camera::Camera() {
		this->transform = std::make_shared<Transform>();
		this->transform->Translate(glm::vec3(5.0f, 3.0f, -22.0f));
		this->transform->Rotate(glm::vec3(0, 1, 0), -20);
		this->Setpers(45.0f, 1200, 900, 0.1f, 1000.0f);
		this->view = std::make_shared<Uniform>(Mat4, glm::lookAt(this->transform->Position(), this->front, glm::vec3(0, 1, 0)));
		this->projecton = std::make_shared<Uniform>(Mat4, glm::mat4(1.0f));
		this->Changetype(Perspective);
		this->campos = std::make_shared<Uniform>(Vec3, glm::vec3());
		Mesh::global_uniform["view"] = this->view;
		Mesh::global_uniform["projection"] = this->projecton;
		Mesh::global_uniform["Campos"] = this->campos;
		this->front = glm::vec3(0,0,1);
		this->yaw = 90.0f;
		this->pitch = 0.0f;
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
			this->projecton->data.Mat4 = glm::perspective(glm::radians(this->fov), (float)this->width / this->height, this->nearp, this->farp);
		}
		else {
			this->projecton->data.Mat4 = glm::ortho(-(this->width / 2.0f), (this->width / 2.0f), -(this->height / 2.0f), (this->height / 2.0f));
		}
	}
	glm::mat4 Camera::Getprojection() {
		return this->projecton->data.Mat4;
	}
	glm::mat4 Camera::Getview() {
		return this->view->data.Mat4;
	}
	void Camera::Start() {

	}
	void Camera::Input(const double& x,const double& y) {
		yaw += x;
		pitch += y;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		this->front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		this->front.y = sin(glm::radians(pitch));
		this->front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		this->front = glm::normalize(front);
	}
	void Camera::Update() {
		this->control->Input();
		this->view->data.Mat4 = glm::lookAt(this->transform->Position(),this->transform->Position()+this->front, glm::vec3(0, 1, 0));
		this->campos->data.Vec3 = this->transform->Position();
		Skybox::v = this->view->data.Mat4;
		Skybox::p = this->projecton->data.Mat4;
		//Mesh::global_uniform["Campos"] = this->campos;
		//Mesh::global_uniform["view"] = this->view;
		//Mesh::global_uniform["projection"] = this->projecton;
	}
	void Camera::MoveTo(const glm::vec3& pos) {
		this->transform->Translate(pos);
	}
	void Camera::Rotate(const glm::vec3& axis, const float& angle) {
		this->transform->Rotate(axis, angle);
	}
	glm::vec3 Camera::Forward() {
		return this->front;
	}
	glm::vec3 Camera::Right() {
		return glm::normalize(glm::cross(this->front, this->transform->Up()));
	}
	glm::vec3 Camera::Up() {
		return this->transform->Up();
	}
	void Camera::component_dis() {

	}
}