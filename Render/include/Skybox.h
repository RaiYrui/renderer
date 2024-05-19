#pragma once
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include"Object.h"
#include"Resources.h"
#include"Shader.h"
#include"Material.h"
#include<glm/gtc/matrix_transform.hpp>
namespace RR {
	class Skybox : public Object {
	private:
		GLuint cubemap;
		std::shared_ptr<Texture> tex;
		//»º³å
		GLuint capFBO, capRBO;
		GLuint vao,vbo;
		glm::mat4 projection;
		glm::mat4 view[6];
		std::shared_ptr<Shader> sky_shader;
		void Uploadbuffer();
	public:
		static glm::mat4 v, p;
		static glm::vec3 lightdir;
		Skybox();
		//½«hdräÖÈ¾Îªcubemap
		void Rendercube();
		//äÖÈ¾Ìì¿ÕºÐ
		void Render();
		void component_dis() override;
	};
}