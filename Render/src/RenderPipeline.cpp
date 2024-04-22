#include "RenderPipeline.h"
namespace RR {
	RenderPipeline::RenderPipeline() {
		glEnable(GL_DEPTH_TEST);
		this->render = std::make_unique<Render>();
		this->mat = std::make_shared<Material>();
		this->mat->AddShader(std::make_shared<Shader>("../../../../Render/shaders/basic.vert", "../../../../Render/shaders/pbr_s.frag"));
		this->mat->Setcongif(Pbr);
		this->cam = std::make_shared<Shader>("../../../../Render/shaders/cam.vert", "../../../../Render/shaders/cam.frag");
		this->cam->Compile();
		this->skybox = std::make_shared<Skybox>();
		this->skybox->Rendercube();
		this->setquad();
		//后处理添加
		this->Ps.emplace_back(std::make_shared<Bloompost>());
		this->Ps.emplace_back(std::make_shared<HDRpost>());//HDR
		glGenFramebuffers(1, &this->FBO);
		glGenRenderbuffers(1, &this->RBO);
		this->window = Window::getInstance();
	}
	void RenderPipeline::Init(std::vector<RObject*>& entitylist) {
		for (RObject* object : entitylist) {
			/*if (object->name == "cube2"||object->name == "head")
				continue;*/
			Mesh* mesh = dynamic_cast<Mesh*>(object->GetComponent("Mesh"));
			if (mesh)
				mesh->setMat(this->mat);
		}
		glGenTextures(1, &this->SRC);
		glBindTexture(GL_TEXTURE_2D, this->SRC);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->window->width, this->window->height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->window->width, this->window->height);
		glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->SRC, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->RBO);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
	}
	void RenderPipeline::Start(std::vector<RObject*>& entitylist) {
		glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->TRG = this->SRC;
		this->skybox->Render();
		if (!entitylist.empty()) {
			this->render->render(entitylist);
		}
		this->Postprocess();
	}
	void RenderPipeline::Postprocess() {
		int n = Ps.size();
		for (int i = 0; i < n; ++i) {
			this->TRG = Ps[i]->process(this->TRG);
			this->Renderquad();
		}
		this->window->setview();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->cam->use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->TRG);
		this->cam->SetInt("src", 0);
		this->Renderquad();
	}
	void RenderPipeline::Renderquad() {
		glBindVertexArray(this->quadvao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}
	void RenderPipeline::setquad() {
		GLfloat quadVertices[] = {
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		glGenVertexArrays(1, &this->quadvao);
		glGenBuffers(1, &this->quadvbo);
		glBindVertexArray(this->quadvao);
		glBindBuffer(GL_ARRAY_BUFFER, this->quadvbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}
}
