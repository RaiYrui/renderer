#pragma once
#include"World.h"
namespace RR {
	/// <summary>
	/// 物体类型
	/// </summary>
	enum Utype {
		U_Entity = 0,
		U_Light,
		U_Camera
	};

	/// <summary>
	/// UI交互
	/// </summary>
	class UWidget {
	private:
		std::shared_ptr<World> world;
		//测试
		bool demo;
		static Window* window;
		//检视面板
		void Inspector();
		//层级面板
		void Hierarchy();
		//资源面板
		void Resources();
		//主窗口
		const ImGuiViewport* main_viewport;
		//窗口属性
		ImGuiWindowFlags window_flags;
		//显示物体类型
		Utype utype;
		//显示索引
		int dis_index;
		std::vector<RObject*> El;
		std::vector<std::shared_ptr<Light>> lights;
	public:
		UWidget(std::shared_ptr<World>world = nullptr);
		void Init();
		void updategui();
	};
}