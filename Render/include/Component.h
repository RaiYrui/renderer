#pragma once
#include"Object.h"
namespace RR {
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
}