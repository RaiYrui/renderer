#pragma once
#include<iostream>
#include"Object.h"
#include "Transform.h"
#include"Component.h"
#include"ComponentManager.h"
namespace RR {
	/// <summary>
	/// 渲染器物体基类
	/// </summary>
	class RObject :public Object {
	private:
		static int count;
		std::shared_ptr<Transform> transform;
		std::unordered_map<std::string, Component*> components;
	public:
		RObject();
		//添加组件
		Component* AddComponent(const std::string& name);
		Component* GetComponent(const std::string& name);
		void MoveTo(const glm::vec3& pos);
		//调用组件的Start
		void Start() override;
		//调用组件的Update
		void Update() override;
		void component_dis() override;
		virtual void ToString()override;
		~RObject();
	};
}