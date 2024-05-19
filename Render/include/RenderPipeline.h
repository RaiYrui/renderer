#pragma once
#include"Render.h"
#include"Skybox.h"
#include"hdr.h"
#include"bloom.h"
#include"Window.h"
#include"ComputeShader.h"
namespace RR {
	/// <summary>
	/// 渲染管线
	/// </summary>
	class RenderPipeline {
	private:
		std::unique_ptr<Render> render;
		std::shared_ptr<Material> mat;
		std::shared_ptr<Skybox> skybox;
		GLuint quadvao, quadvbo;
		GLuint FBO, RBO;
		GLuint SRC,TRG;
		std::vector<std::shared_ptr<Postprocessor>> Ps;
		std::shared_ptr<Shader>cam;
		void setquad();
		void Renderquad();
		void Postprocess();
		Window* window;

		std::shared_ptr<ComputeShader> lut;
		std::shared_ptr<ComputeShader> computetest;
		std::shared_ptr<ComputeShader> ifft;
		unsigned int size;
		unsigned int luttex;
		unsigned int texture;
		unsigned int xdis;
		unsigned int ydis;
		unsigned int ddx;
		unsigned int ddz;
		unsigned int dyx;
		unsigned int dyz;
		unsigned int ddzx;
		unsigned int stagenum;
		bool pingpong;
		int stage;
		unsigned int b0, b1;
		//测试
		void testGenTextures();
		void IFFT(unsigned int tex);
		glm::vec2* wind;
	public:
		//需要配置定制化的材质
		RenderPipeline();
		void Init(std::vector<RObject*>& entitylist);
		void Start(std::vector<RObject*>& entitylist);
	};
}