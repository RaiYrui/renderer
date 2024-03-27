#pragma once
#include <iostream>
#include<memory>
namespace RR {
	/// <summary>
	/// 物体基类
	/// </summary>
	class Object {
	private:
	public:
		std::string name;
		virtual void ToString();
		//添加组件时调用
		virtual void Start();
		//每一帧调用
		virtual void Update();
		virtual void component_dis() = 0;
		virtual ~Object() = 0;
	};
}