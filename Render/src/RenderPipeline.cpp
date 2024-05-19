#include "RenderPipeline.h"
namespace RR {
	RenderPipeline::RenderPipeline() {
		glEnable(GL_DEPTH_TEST);
		this->render = std::make_unique<Render>();
		this->mat = std::make_shared<Material>();
		this->mat->AddShader(std::make_shared<Shader>("../../../../Render/shaders/pbr_s.vert", "../../../../Render/shaders/pbr_s.frag"));
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
			/*if (object->name == "cube2" || object->name == "head")
				continue;*/
			Mesh* mesh = dynamic_cast<Mesh*>(object->GetComponent("Mesh"));
			if (mesh)
				mesh->setMat(this->mat);
		}
		glGenTextures(1, &this->SRC);
		glBindTexture(GL_TEXTURE_2D, this->SRC);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->window->width, this->window->height, 0, GL_RGBA, GL_FLOAT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->window->width, this->window->height);
		glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->SRC, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->RBO);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
		this->testGenTextures();
		this->wind = new glm::vec2(5, 8);
	}
	void RenderPipeline::Start(std::vector<RObject*>& entitylist) {

		glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(1, xdis, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(2, ydis, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(3, ddx, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(4, ddz, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(5, dyx, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(6, dyz, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(7, ddzx, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		computetest->use();
		this->wind = Material::wind;
		computetest->setFloat("time", glfwGetTime());
		computetest->setVec2("wind", *wind);
		computetest->setFloat("A", 1);
		computetest->dispatch(this->size, this->size);
		glBindImageTexture(0, luttex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		lut->use();
		lut->dispatch(this->stagenum, this->size);
		this->IFFT(this->texture);
		this->IFFT(this->xdis);
		this->IFFT(this->ydis);
		this->IFFT(this->ddx);
		this->IFFT(this->ddz);
		this->IFFT(this->dyx);
		this->IFFT(this->dyz);
		this->IFFT(this->ddzx);
		Material::h = texture;
		Material::x = xdis;
		Material::z = ydis;
		Material::dyx = dyx;
		Material::dyz = dyz;
		Material::ddx = ddx;
		Material::ddz = ddz;
		Material::ddzx = ddzx;

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
	void RenderPipeline::IFFT(unsigned int tex) {
		this->ifft->use();
		this->pingpong = false;
		glBindImageTexture(0, luttex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(1, tex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(2, b1, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		this->stage = 0;
		this->ifft->setInt("H", 1);
		for (int i = 0; i < stagenum; ++i) {
			pingpong = !pingpong;
			this->ifft->setBool("pingpong", pingpong);
			this->ifft->setInt("stage", this->stage);
			this->ifft->dispatch(this->size/8, this->size / 8);
			this->stage++;
		}
		glBindImageTexture(0, luttex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(1, tex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		glBindImageTexture(2, b1, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
		this->stage = 0;
		this->ifft->setInt("H", 2);
		for (int i = 0; i < stagenum; ++i) {
			pingpong = !pingpong;
			this->ifft->setBool("pingpong", pingpong);
			this->ifft->setInt("stage", this->stage);
			this->ifft->dispatch(this->size / 8, this->size / 8);
			this->stage++;
		}
		this->ifft->setInt("H", 3);
		this->ifft->dispatch(this->size / 8, this->size / 8);
	}


	void RenderPipeline::testGenTextures() {
		this->computetest = std::make_shared<ComputeShader>("../../../../Render/shaders/heightgen.comp");
		this->computetest->Compile();
		this->lut = std::make_shared<ComputeShader>("../../../../Render/shaders/Blut.comp");
		this->lut->Compile();
		this->ifft = std::make_shared<ComputeShader>("../../../../Render/shaders/IFFT.comp");
		this->ifft->Compile();
		const unsigned int TEXTURE_WIDTH = 256, TEXTURE_HEIGHT = 256;
		this->size = 256;
		this->stagenum = 8;
		glGenTextures(1, &texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA,
			GL_FLOAT, nullptr);
		glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);


		glGenTextures(1, &xdis);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, xdis);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA,
			GL_FLOAT, nullptr);
		glBindImageTexture(1, xdis, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

		glGenTextures(1, &ydis);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, ydis);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA,
			GL_FLOAT, nullptr);
		glBindImageTexture(2, ydis, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

		glGenTextures(1, &luttex);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, luttex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, stagenum, TEXTURE_HEIGHT, 0, GL_RGBA,
			GL_FLOAT, nullptr);

		glGenTextures(1, &b1);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, b1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA,
			GL_FLOAT, nullptr);

		glGenTextures(1, &ddx);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, ddx);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA,
			GL_FLOAT, nullptr);

		glGenTextures(1, &ddz);
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, ddz);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA,
			GL_FLOAT, nullptr);

		glGenTextures(1, &dyx);
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, dyx);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA,
			GL_FLOAT, nullptr);

		glGenTextures(1, &dyz);
		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, dyz);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA,
			GL_FLOAT, nullptr);

		glGenTextures(1, &ddzx);
		glActiveTexture(GL_TEXTURE9);
		glBindTexture(GL_TEXTURE_2D, ddzx);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA,
			GL_FLOAT, nullptr);
	}
}
