#pragma once
#include<iostream>
#include"Object.h"
#include "Transform.h"
#include"Component.h"
#include"ComponentManager.h"
/// <summary>
/// ��Ⱦ���������
/// </summary>
class RObject :public Object {
private:
	static int count;
	std::shared_ptr<Transform> transform;
	std::unordered_map<std::string,Component*> components;
public:
	RObject();
	//������
	Component* AddComponent(const std::string & name);
	Component* GetComponent(const std::string& name);
	//���������Start
	void Start() override;
	//���������Update
	void Update() override;
	virtual void ToString()override;
};