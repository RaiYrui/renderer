#pragma once
#include<IMGUI/imgui_impl_glfw.h>
#include<IMGUI/imgui_impl_opengl3.h>
#include"Object.h"
namespace RR {
	/// <summary>
	/// ×é¼þÀà
	/// </summary>
	class Component {
	private:
	public:
		std::string name;
		std::shared_ptr<Object> entity;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Destroy() = 0;
		virtual void Inspector_dis()=0;
		virtual ~Component()= 0;
	};
}