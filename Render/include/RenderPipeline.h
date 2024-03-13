#pragma once
#include"Render.h"
namespace RR {
	/// <summary>
	/// ��Ⱦ����
	/// </summary>
	class RenderPipeline {
	private:
		std::unique_ptr<Render> render;
		std::shared_ptr<Material> mat;
	public:
		//��Ҫ���ö��ƻ��Ĳ���
		RenderPipeline();
		void Init(std::vector<RObject*>& entitylist);
		void Start(std::vector<RObject*>& entitylist);
	};
}