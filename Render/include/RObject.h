#pragma once
#include<iostream>
#include"Object.h"
#include"Transform.h"
#include"ComponentManager.h"
namespace RR {
	class Component;
	/// <summary>
	/// ��Ⱦ���������
	/// </summary>
	class RObject :public Object {
	private:
		static int count;
		std::shared_ptr<Transform> transform;
		std::unordered_map<std::string, Component*> components;
	public:
		int Renderqueue;
		RObject();
		RObject(const RObject& ro);
		//������
		Component* AddComponent(const std::string& name);
		Component* GetComponent(const std::string& name);
		void MoveTo(const glm::vec3& pos);
		void ScaleTo(const glm::vec3& scale);
		//���������Start
		void Start() override;
		//���������Update
		void Update() override;
		void component_dis() override;
		virtual void ToString()override;
		~RObject();
	};
}