#pragma once
#include "Object.h"
#include"Transform.h"
#include"Mesh.h"
namespace RR {
	/// <summary>
	/// µÆ¹â
	/// </summary>
	class Light : public Object {
	private:
		std::shared_ptr<Transform> transform;
		glm::vec4 color;
		float intensity;
		static int tid;
		int id;
	public:
		//ÒÆ¶¯µÆ¹â
		void Moveto(const glm::vec3& position);
		glm::vec3 Getpos();
		glm::vec4 GetColor();
		float Getintensity();
		void Start() override;
		void Update() override;
		void component_dis() override;
		Light();
	};
}