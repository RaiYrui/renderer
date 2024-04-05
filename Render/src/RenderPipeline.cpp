#include "RenderPipeline.h"
namespace RR {
	RenderPipeline::RenderPipeline() {
		glEnable(GL_DEPTH_TEST);
		this->render = std::make_unique<Render>();
		this->mat = std::make_shared<Material>();
		this->mat->AddShader(new Shader("../../../../Render/shaders/basic.vert", "../../../../Render/shaders/basic.frag"));
		this->mat->Setcongif(Normal);
		this->skybox = std::make_shared<Skybox>();
		this->skybox->Rendercube();
	}
	void RenderPipeline::Init(std::vector<RObject*>& entitylist) {
		for (RObject* object : entitylist) {
			Mesh* mesh = dynamic_cast<Mesh*>(object->GetComponent("Mesh"));
			if (mesh)
				mesh->setMat(this->mat);
		}
	}
	void RenderPipeline::Start(std::vector<RObject*>& entitylist) {
		this->skybox->Render();
		if (!entitylist.empty()) {
			this->render->render(entitylist);
		}
	}
}
