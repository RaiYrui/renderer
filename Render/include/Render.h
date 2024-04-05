#pragma once
#include<vector>
#include"RObject.h"
namespace RR {
	/// <summary>
	/// ‰÷»æ µœ÷¿‡
	/// </summary>
	class Render {
	private:
		int drawsize;
	public:
		void render(std::vector<RObject*>& entitylist);
		Render();
	};
}