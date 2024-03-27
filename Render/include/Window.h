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
		int width, height;
		int gl_width, gl_height;
		int Ins_width, Ins_height;
		int R_width, R_height;
		int H_width, H_height;
		static Window* getInstance();
		bool Init();
		void Resize();
		static GLFWwindow* glfw_window;
		void Close();
	};
}