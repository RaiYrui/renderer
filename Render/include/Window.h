#pragma once
#define GLFW_INCLUDE_NONE
#include<iostream>
#include<GLFW/glfw3.h>
#include<glad/glad.h>
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
	GLFWwindow* glfw_window;
	void Close();
};