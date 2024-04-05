#pragma once
#include"Render.h"
#include"Skybox.h"
namespace RR {
	/// <summary>
	/// 渲染管线
	/// </summary>
	class RenderPipeline {
	private:
		std::unique_ptr<Render> render;
		std::shared_ptr<Material> mat;
		std::shared_ptr<Skybox> skybox;
	public:
		//需要配置定制化的材质
		RenderPipeline();
		void Init(std::vector<RObject*>& entitylist);
		void Start(std::vector<RObject*>& entitylist);
	};
}