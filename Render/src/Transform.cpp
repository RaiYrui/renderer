#include "Transform.h"
Transform::Transform() {
	this->pos = glm::mat4(1.0f);
	this->localPosition = glm::vec3();
	this->localRotation = glm::vec3();
	this->localScale = glm::vec3();
	this->up = glm::vec3(0, 1, 0);
}
glm::vec3 Transform::Position() {
	return this->localPosition;
}
glm::vec3 Transform::Up() {
	return this->up;
}
void Transform::Translate(const glm::vec3& position) {
	this->pos = glm::translate(this->pos, position);
	this->localPosition.x = pos[3][0];
	this->localPosition.y = pos[3][1];
	this->localPosition.z = pos[3][2];

}
void Transform::Rotate(const glm::vec3& axis, float angle) {
	this->pos = glm::rotate(this->pos, glm::radians(angle), axis);
	//赋值给旋转的变量，用旋转矩阵
}
void Transform::Scale(const glm::vec3& scale) {
	this->pos = glm::scale(this->pos, scale);
	this->localScale.x *= scale.x;
	this->localScale.y *= scale.y;
	this->localScale.z *= scale.z;
}

void Transform::Start() {
	std::cout << "Transform start"<<std::endl;
}
void Transform::Update() {

}
void Transform::Destroy() {

}