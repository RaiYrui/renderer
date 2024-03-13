#pragma once
#include"Render.h"
namespace RR {
	/// <summary>
	/// 渲染管线
	/// </summary>
	class RenderPipeline {
	private:
		std::unique_ptr<Render> render;
		std::shared_ptr<Material> mat;
	public:
		//需要配置定制化的材质
		RenderPipeline();
		void Init(std::vector<RObject*>& entitylist);
		void Start(std::vector<RObject*>& entitylist);
	};
}