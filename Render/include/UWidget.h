#pragma once
#include"World.h"
namespace RR {
	/// <summary>
	/// UI����
	/// </summary>
	class UWidget {
	private:
		std::shared_ptr<World> world;
		//����
		bool demo;
		static Window* window;
		//�������
		void Inspector();
		//�㼶���
		void Hierarchy();
		//��Դ���
		void Resources();
		//������
		const ImGuiViewport* main_viewport;
		//��������
		ImGuiWindowFlags window_flags;
	public:
		UWidget(std::shared_ptr<World>world = nullptr);
		void Init();
		void updategui();
	};
}