#pragma once
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<Shader.h>
#include "Window.h"
namespace RR {
	class Postprocessor {
	private:
	public:
		GLuint quadvao, quadvbo;
		Window* window;
		Postprocessor();
		virtual GLuint process(const GLuint& src) = 0;
	};
}