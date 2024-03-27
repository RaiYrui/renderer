#pragma once
#define GLFW_INCLUDE_NONE
#include<iostream>
#include<GLFW/glfw3.h>
#include<vector>
#include<unordered_map>
#include<functional>
#include "Object.h"
#include"Window.h"
namespace RR {
	typedef std::function<void(int)> Func;
	extern std::unordered_map<std::string, std::vector<Func>>EventList;
	void Keyboard_action(GLFWwindow* window, int key, int scancode, int action, int mods);
	void Cursor_action(GLFWwindow* window, double xpos, double ypos);
	/// <summary>
	/// ¿ØÖÆ»ùÀà
	/// </summary>
	class Control {
	private:
		double c_xpos, c_ypos;
	public:
		static Window* window;
		bool selected;
		virtual void ToString();
		virtual void Input();
		Control();
	};
}