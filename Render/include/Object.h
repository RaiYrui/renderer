#pragma once
#include <iostream>
#include<memory>
namespace RR {
	/// <summary>
	/// �������
	/// </summary>
	class Object {
	private:
	public:
		std::string name;
		virtual void ToString();
		//������ʱ����
		virtual void Start();
		//ÿһ֡����
		virtual void Update();
		virtual void component_dis() = 0;
		virtual ~Object() = 0;
	};
}