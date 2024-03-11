#pragma once
#include"Object.h"
/// <summary>
/// �����
/// </summary>
class Component {
private:
public:
	std::string name;
	std::shared_ptr<Object> entity;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;
};