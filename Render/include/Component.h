#pragma once
#include<iostream>
#include<IMGUI/imgui_impl_glfw.h>
#include<IMGUI/imgui_impl_opengl3.h>
namespace RR {
    class RObject;
	/// <summary>
	/// ×é¼þÀà
	/// </summary>
	class Component {
	private:
	public:
		std::string name;
		std::shared_ptr<RObject> entity;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Destroy() = 0;
		virtual void Inspector_dis()=0;
		virtual ~Component()= 0;
	};
}