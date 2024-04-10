#include"hdr.h"
namespace RR {
		HDRpost::HDRpost() {
		this->shader = std::make_shared<Shader>("../../../../Render/shaders/cam.vert", "../../../../Render/shaders/hdr.frag");
		this->shader->Compile();
		glGenFramebuffers(1, &this->FBO);
		glGenRenderbuffers(1, &this->RBO);
		glGenTextures(1, &this->rendertexture);
		glBindTexture(GL_TEXTURE_2D, this->rendertexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 1200, 900, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1200, 900);
		glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->rendertexture, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->RBO);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
		}
	GLuint HDRpost::process(const GLuint& src) {
		glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->shader->use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, src);
		this->shader->SetInt("src", 0);
		this->shader->SetFloat("exposure", 1.0f);
		return this->rendertexture;
	}
}