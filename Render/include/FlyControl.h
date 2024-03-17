#pragma once
#include "Control.h"
#include"Camera.h"
namespace RR {
	class FlyControl : public Control {
	private:
		void KeyBoard_upadate();
		void Cursor_update();
		double c_xpos, c_ypos;
		double xlast, ylast;
		bool pressed;
	public:
		std::shared_ptr<Camera>camera;
		FlyControl(std::shared_ptr<Camera> cam);
		FlyControl();
		void Input()override;
	};
}