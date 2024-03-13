#pragma once
#include<vector>
#include<glm/glm.hpp>
namespace RR {
	/// <summary>
	/// Õ¯∏Ò–≈œ¢¥Ê¥¢
	/// </summary>
	class MeshItem {
	public:
		std::vector<glm::vec3> vertex;
		std::vector<glm::vec2> uv;
		std::vector<glm::vec3> normal;
		MeshItem() {};
		MeshItem(std::vector<glm::vec3>& v, std::vector<glm::vec2>& u, std::vector<glm::vec3>& n) :vertex(v), uv(u), normal(n) {}
	};
}