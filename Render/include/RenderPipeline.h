#pragma once
#include"Render.h"
#include"Skybox.h"
#include"hdr.h"
#include"bloom.h"
#include"Window.h"
namespace RR {
	/// <summary>
	/// ��Ⱦ����
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
	public:
		//��Ҫ���ö��ƻ��Ĳ���
		RenderPipeline();
		void Init(std::vector<RObject*>& entitylist);
		void Start(std::vector<RObject*>& entitylist);
	};
}