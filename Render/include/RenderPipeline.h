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
		unsigned int size;
		unsigned int luttex;
		unsigned int texture;
		unsigned int xdis;
		unsigned int ydis;
		unsigned int stagenum;
		//测试
		void testGenTextures();
	public:
		//需要配置定制化的材质
		RenderPipeline();
		void Init(std::vector<RObject*>& entitylist);
		void Start(std::vector<RObject*>& entitylist);
	};
}