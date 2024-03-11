#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"Component.h"
/// <summary>
/// Transform类描述物体的变换信息
/// </summary>
class Transform: public Component{
private:
	glm::vec3 localPosition;
	glm::vec3 localRotation;
	glm::vec3 localScale;
	glm::mat4 pos;
	glm::vec3 up;
public:
	void Start()override;
	void Update()override;
	void Destroy()override;
	Transform();
	void Translate(const glm::vec3& position);
	void Rotate(const glm::vec3& axis, float angle);
	void Scale(const glm::vec3& scale);
	glm::vec3 Position();
	glm::vec3 Up();
};