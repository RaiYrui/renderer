#pragma once
#include<glad/glad.h>
#include"World.h"
#include"Window.h"
#include"RenderPipeline.h"
#include"UWidget.h"
namespace RR {
	/// <summary>
	/// ‰÷»æ∆˜∆Ù∂Ø¿‡
	/// </summary>
	class Application {
	private:
		static Window* window;
		static Application* app;
		std::shared_ptr<World> world;
		std::shared_ptr<UWidget> widget;
		Application();
	public:
		static Application* getInstance();
		bool Init();
		void Start();
		void Stop();
	};
}