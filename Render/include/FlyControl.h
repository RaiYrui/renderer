#pragma once
#include "Control.h"
#include"Camera.h"
namespace RR {
	class FlyControl : public Control {
	private:

	public:
		std::shared_ptr<Camera>camera;
		FlyControl(std::shared_ptr<Camera> cam);
		FlyControl();
	};
}