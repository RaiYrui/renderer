#pragma once
#include "Postprocessor.h"
namespace RR {
	class HDRpost : public Postprocessor {
	private:
		GLuint rendertexture;
		std::shared_ptr<Shader> shader;
		int width, height;
		GLuint FBO, RBO;
	public:
		HDRpost();
		GLuint process(const GLuint& src)override;
	};
}