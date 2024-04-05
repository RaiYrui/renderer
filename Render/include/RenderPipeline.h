#pragma once
#include"Render.h"
#include"Skybox.h"
namespace RR {
	/// <summary>
	/// ��Ⱦ����
	/// </summary>
	class RenderPipeline {
	private:
		std::unique_ptr<Render> render;
		std::shared_ptr<Material> mat;
		std::shared_ptr<Skybox> skybox;
	public:
		//��Ҫ���ö��ƻ��Ĳ���
		RenderPipeline();
		void Init(std::vector<RObject*>& entitylist);
		void Start(std::vector<RObject*>& entitylist);
	};
}