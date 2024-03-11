#include "World.h"
void World::Init() {
	this->cm = std::make_shared<ComponentManager>();
	this->rp = std::make_shared<RenderPipeline>();
	this->CreateSomething();
	this->cameras["Maincamera"] = std::make_shared<Camera>();
	this->rp->Init(this->EntityList);
	std::shared_ptr<Light>  light = std::make_shared<Light>();
	light->Moveto(glm::vec3(0, 5, 5));
	this->Lights.push_back(light);
	
	for (RObject* object : this->EntityList) {
		object->Start();
	}
	this->Maincamera()->Start();
	for (auto light : this->Lights) {
		light->Start();
		Material::lights.push_back(light);
	}
}
void World::Startp() {
	this->Maincamera()->Update();
	for (auto light : this->Lights) {
		light->Update();
	}
	this->rp->Start(this->EntityList);
}
void World::CreateSomething() {
	RObject* cube = new RObject();
	cube->name = "cube";
	Mesh* mesh = dynamic_cast<Mesh*>(cube->AddComponent("Mesh"));
	mesh->Load("../../../../Render/mesh/testm.obj");
	mesh->GPUupload();

	EntityList.push_back(cube);
}
std::shared_ptr<Camera> World::Maincamera() {
	auto it = this->cameras.find("Maincamera");
	if (it != this->cameras.end()) {
		return it->second;
	}
	return nullptr;
}
void World::Remove(const char* name) {
	for (auto obj = EntityList.begin(); obj != EntityList.end(); obj++) {
		if ( (*obj)->name == name) {
			EntityList.erase(obj);
			delete (*obj);
			(*obj) = nullptr;
		}
	}
}