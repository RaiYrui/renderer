#pragma once
#include<vector>
#include "RObject.h"
#include"Resources.h"
#include "RenderPipeline.h"
#include"Camera.h"
#include"Light.h"
/// <summary>
///  ¿ΩÁ¿‡
/// </summary>
class World {
private:
	std::shared_ptr<RenderPipeline>rp;
	std::shared_ptr<ComponentManager>cm;
	std::vector<RObject*> EntityList;
	std::unordered_map<std::string, std::shared_ptr<Camera>> cameras;
	std::vector<std::shared_ptr<Light>> Lights;
	void CreateSomething();
public:
	void Init();
	void Startp();
	void Remove(const char *name);
	std::shared_ptr<Camera> Maincamera();
};