#pragma once
#include"World.h"
namespace RR {
	class UWidget {
	private:
		std::shared_ptr<World> world;
		bool demo;
	public:
		UWidget(std::shared_ptr<World>world = nullptr);
		void Init();
		void updategui();
	};
}