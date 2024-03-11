#include "RObject.h"
int RObject::count = 0;
Component* RObject::AddComponent(const std::string& name) {
	auto it = components.find(name);
	if (it == components.end()) {
		components[name] = (Component *)CreateClass(name);
		components[name]->entity = std::make_shared<RObject>(*this);
		components[name]->name += (" of " + this->name);
		return components[name];
	}
	else {
		std::cout << "重复添加组件" << std::endl;
		return it->second;
	}
}
Component* RObject::GetComponent(const std::string& name) {
	Component* res = components[name];
	if (res)
		return res;
	else
		return nullptr;
}
void RObject::ToString() {
	std::cout << this->name << std::endl;
}
void RObject::Start() {
	for (const auto &com : this->components) {
		com.second->Start();
	}
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
	this->AddComponent("Transform");
}