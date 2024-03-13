#pragma once
#define GLFW_INCLUDE_NONE
#include<iostream>
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<IMGUI/imgui_impl_glfw.h>
#include<IMGUI/imgui_impl_opengl3.h>
namespace RR {
	/// <summary>
	/// ´°¿ÚÀà
	/// </summary>
	class Window {
	private:
		static Window* window;
		Window();
	public:
		static Window* getInstance();
		bool Init();
		int width, height;
		static GLFWwindow* glfw_window;
		void Close();
	};
}