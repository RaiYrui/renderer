#include"Light.h"
namespace RR {
	int Light::tid = 0;
	Light::Light() {
		this->color = glm::vec4(2.0f,2.0f,1.8f,1.0f);
		this->intensity = 5.0f;
		this->transform = std::make_shared<Transform>();
		this->id = this->tid;
		Mesh::global_uniform["Lightpos[" + std::to_string(this->id) + "]"] = std::make_shared<Uniform>(Vec3, glm::vec3());
		Mesh::global_uniform["Lightcolor[" + std::to_string(this->id) + "]"] = std::make_shared<Uniform>(Vec4, glm::vec4());
		Mesh::global_uniform["Intensity[" + std::to_string(this->id) + "]"] = std::make_shared<Uniform>(Float, 0);
		Mesh::global_uniform["Lightnum"] = std::make_shared<Uniform>(Int, 0);
		Mesh::global_uniform["Lightdir"] = std::make_shared<Uniform>(Vec3, glm::vec3(0, -1, -1));
		this->tid++;
		std::string c;
		int num = this->tid;
		while (num > 0) {
			int n = num % 10;
			c += (n + '0');
			num /= 10;
		}
		this->name = "Light" + c;
		this->dir = glm::vec3(0, -0.25, -1);
	}
	void Light::Moveto(const glm::vec3& position) {
		this->transform->Translate(position);
	}
	void Light::Start() {
		this->Moveto(glm::vec3(0, 5, 0));
	}
	void Light::Update() {
		Mesh::global_uniform["Lightpos[" + std::to_string(this->id) + "]"]->data.Vec3 = this->Getpos();
		Mesh::global_uniform["Lightcolor[" + std::to_string(this->id) + "]"]->data.Vec4 = this->color;
		Mesh::global_uniform["Intensity[" + std::to_string(this->id) + "]"]->data.floatvalue = this->intensity;
		Mesh::global_uniform["Lightnum"]->data.intvalue = Light::tid; 
		Mesh::global_uniform["Lightdir"]->data.Vec3 = this->dir;
	}
	glm::vec3 Light::Getpos() {
		return this->transform->Position();
	}
	glm::vec4 Light::GetColor() {
		return this->color;
	}
	float Light::Getintensity() {
		return this->intensity;
	}
	void Light::component_dis() {
		this->transform->Inspector_dis();
		ImGui::DragFloat("Intensity", &this->intensity, 0.25f, 0, FLT_MAX, "%.3f");
		ImGui::ColorEdit4("set color", (float*)&this->color);
		ImGui::DragFloat("dir x", &this->dir.x, 0.05f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("dir y", &this->dir.y, 0.05f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("dir z", &this->dir.z, 0.05f, -FLT_MAX, FLT_MAX, "%.3f");
	}
}