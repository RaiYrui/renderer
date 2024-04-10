#pragma once
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<Shader.h>
namespace RR {
	class Postprocessor {
	private:
	public:
		virtual GLuint process(const GLuint& src) = 0;
	};
}