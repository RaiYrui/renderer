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
		virtual void Start();
		virtual void Update();
	};
}