#include "World.h"
namespace RR {
	void World::Init() {
		this->cm = std::make_shared<ComponentManager>();
		this->rp = std::make_shared<RenderPipeline>();
		this->CreateSomething();
		this->cameras["Maincamera"] = std::make_shared<Camera>();
		this->cameras["Maincamera"]->control = std::make_shared<FlyControl>(this->cameras["Maincamera"]);
		this->rp->Init(this->EntityList);
		std::shared_ptr<Light>  light = std::make_shared<Light>();
		light->Moveto(glm::vec3(0, 5, 5));
		this->Lights.emplace_back(light);
		light = std::make_shared<Light>();
		light->Moveto(glm::vec3(2, 5, 0));
		this->Lights.emplace_back(light);
		std::stable_sort(this->EntityList.begin(), this->EntityList.end(), [](RObject* a, RObject* b) {return a->Renderqueue < b->Renderqueue; });
		for (RObject* object : this->EntityList) {
			object->Start();
		}
		this->Maincamera()->Start();
	}
	void World::Startp() {
		this->Maincamera()->Update();
		for (auto light : this->Lights) {
			light->Update();
		}
		this->rp->Start(this->EntityList);
	}
	void World::CreateSomething() {
		Mesh* mesh;
		RObject* cube = new RObject();
		cube->Renderqueue = 3000;
		cube->name = "wave";
		mesh = dynamic_cast<Mesh*>(cube->AddComponent("Mesh"));
		mesh->Load("../../../../Render/mesh/waves.obj");
		mesh->GPUupload();

		EntityList.emplace_back(cube);
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (i == j&&i == 0)
					continue;
			RObject* copy = new RObject(*cube);
			copy->MoveTo(glm::vec3(10*i, 0, 10*j));
			EntityList.emplace_back(copy);
			if (i == 0)
				continue;
			copy = new RObject(*cube);
			copy->MoveTo(glm::vec3(-10 * i, 0, 10 * j));
			EntityList.emplace_back(copy);

			}
		}
		/*
		RObject* cube2 = new RObject();
		cube2->name = "cube2";
		cube2->Renderqueue = 3000;
		mesh = dynamic_cast<Mesh*>(cube2->AddComponent("Mesh"));
		std::shared_ptr<Material> mat = std::make_shared<Material>();
		cube2->MoveTo(glm::vec3(5, -5.5f, -15));
		cube2->ScaleTo(glm::vec3(10, 10.0f, 10.0f));
		mat->AddShader(std::make_shared<Shader>("../../../../Render/shaders/common.vert", "../../../../Render/shaders/common.frag"));
		mat->Setcongif(ulit);
		mat->setColor(glm::vec4(0.18,0.09,0.05,1));
		mat->setTex("../../../../Render/tex/nt.png");
		mesh->setMat(mat);
		
		mesh->Load("../../../../Render/mesh/hair.obj");
		mesh->GPUupload();
		EntityList.emplace_back(cube2);

		RObject* head = new RObject();
		head->name = "head";
		mesh = dynamic_cast<Mesh*>(head->AddComponent("Mesh"));
		mat = std::make_shared<Material>();
		head->MoveTo(glm::vec3(5, -5.5f, -15));
		head->ScaleTo(glm::vec3(10, 10.0f, 10.0f));
		mat->AddShader(std::make_shared<Shader>("../../../../Render/shaders/common.vert", "../../../../Render/shaders/nc.frag"));
		mat->Setcongif(ulit);
		mat->setColor(glm::vec4(1,1,1, 1));
		mesh->setMat(mat);
		mesh->Load("../../../../Render/mesh/head.obj");
		mesh->GPUupload();
		EntityList.emplace_back(head);
		*/
	}
	std::shared_ptr<Camera> World::Maincamera() {
		auto it = this->cameras.find("Maincamera");
		if (it != this->cameras.end()) {
			return it->second;
		}
		return nullptr;
	}
	std::vector<RObject*>& World::get_Entitylist() {
		return this->EntityList;
	}
	std::vector<std::shared_ptr<Light>>& World::get_Lights() {
		return this->Lights;
	}
	void World::Remove(const char* name) {
		for (auto obj = EntityList.begin(); obj != EntityList.end(); obj++) {
			if ((*obj)->name == name) {
				EntityList.erase(obj);
				delete (*obj);
				(*obj) = nullptr;
			}
		}
	}
	World::~World() {
		for (RObject* obj : this->EntityList) {
			delete obj;
			obj = nullptr;
		}
	}
}