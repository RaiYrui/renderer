#include "RenderPipeline.h"
RenderPipeline::RenderPipeline() {
	this->render = std::make_unique<Render>();
	this->mat = std::make_shared<Material>();
	this->mat->AddShader(new Shader("../../../../Render/shaders/basic.vert", "../../../../Render/shaders/basic.frag"));
	this->mat->Setcongif(Normal);
}
void RenderPipeline::Init(std::vector<RObject*>& entitylist) {
		for(RObject* object : entitylist){
			Mesh* mesh = (Mesh*)object->GetComponent("Mesh");
			if(mesh)
				mesh->material = this->mat;
		}
	
}
void RenderPipeline::Start(std::vector<RObject*>& entitylist) {
	if (!entitylist.empty()) {
		this->render->render(entitylist);
	}
}
