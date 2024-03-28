#pragma once
#include"World.h"
namespace RR {
	/// <summary>
	/// ��������
	/// </summary>
	enum Utype {
		U_Entity = 0,
		U_Light,
		U_Camera
	};

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
		//��ʾ��������
		Utype utype;
		//��ʾ����
		int dis_index;
		std::vector<RObject*> El;
		std::vector<std::shared_ptr<Light>> lights;
	public:
		UWidget(std::shared_ptr<World>world = nullptr);
		void Init();
		void updategui();
	};
}