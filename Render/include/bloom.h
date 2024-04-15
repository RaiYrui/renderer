#pragma once
#include"Postprocessor.h"
namespace RR {
	class Bloompost : public Postprocessor {
	private:
		GLuint FBO,RBO;
		GLuint amount;
		GLuint rendertexture[2];
		GLuint pingpongFBO[2];
		GLuint pingpongBuffer[2];
		//GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		GLuint F_fbo, F_texture,F_rbo;
		std::shared_ptr<Shader> blur_sh;
		std::shared_ptr<Shader> combine_sh;
		std::shared_ptr<Shader> input_sh;
		void bind();
		void renderquad();
	public:
		Bloompost();
		GLuint process(const GLuint& src)override;
	};
}