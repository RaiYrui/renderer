#include "RObject.h"
namespace RR {
	int RObject::count = 0;
	Component* RObject::AddComponent(const std::string& name) {
		auto it = components.find(name);
		if (it == components.end()) {
			components[name] = (Component*)CreateClass(name);
			components[name]->entity = std::make_shared<RObject>(*this);
			components[name]->name += (" of " + this->name);
			components[name]->Start();
			return components[name];
		}
		else {
			std::cout << "重复添加组件" << std::endl;
			return it->second;
		}
	}
	Component* RObject::GetComponent(const std::string& name) {
		if (this->components.find(name)!= this->components.end())
			return this->components[name];
		else
			return nullptr;
	}
	void RObject::ToString() {
		std::cout << this->name << std::endl;
	}
	void RObject::Start() {
		//for (const auto& com : this->components) {
		//	com.second->Start();
		//}
	}
	void RObject::Update() {
		for (const auto& com : this->components) {
			com.second->Update();
		}
	}
	RObject::RObject() {
		this->count++;
		std::string c;
		int num = this->count;
		while (num > 0) {
			int n = num % 10;
			c += (n + '0');
			num /= 10;
		}
		this->name = "物体" + c;
		this->transform = std::dynamic_pointer_cast<Transform>(std::shared_ptr<Component>(this->AddComponent("Transform")));
	}
	void RObject::MoveTo(const glm::vec3& pos) {
		this->transform->Translate(pos);
	}
	RObject::~RObject() {
		for (auto it : this->components) {
			delete it.second;
			it.second = nullptr;
		}
	}
	void RObject::component_dis() {
		for (const auto& com : this->components) {
			com.second->Inspector_dis();
		}
	}
}