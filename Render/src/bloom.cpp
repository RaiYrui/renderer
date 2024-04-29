#include"bloom.h"
namespace RR {
	Bloompost::Bloompost() {
        this->bind();
        this->input_sh = std::make_shared<Shader>("../../../../Render/shaders/cam.vert", "../../../../Render/shaders/bloomin.frag");
        this->input_sh->Compile();
        this->blur_sh = std::make_shared<Shader>("../../../../Render/shaders/cam.vert", "../../../../Render/shaders/blur.frag");
        this->blur_sh->Compile();
        this->combine_sh = std::make_shared<Shader>("../../../../Render/shaders/cam.vert", "../../../../Render/shaders/mixbloom.frag");
        this->combine_sh->Compile();
		glGenFramebuffers(1, &this->FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
		glGenTextures(2, this->rendertexture);
        glGenFramebuffers(2, pingpongFBO);
        glGenTextures(2, pingpongBuffer);
        for (GLuint i = 0; i < 2; i++)
        {
            glBindTexture(GL_TEXTURE_2D, this->rendertexture[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->window->width, this->window->height, 0, GL_RGB, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, this->rendertexture[i], 0);
        }
        glGenRenderbuffers(1, &this->RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->window->width, this->window->height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->RBO);
        GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        glDrawBuffers(2, attachments);

        for (int i = 0; i < 2; ++i) {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
            glBindTexture(GL_TEXTURE_2D, pingpongBuffer[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->window->width, this->window->height, 0, GL_RGB, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongBuffer[i], 0);
        }
        this->amount = 5;
        //×îÖÕÊä³öÖ¡»º³å
        glGenFramebuffers(1, &this->F_fbo);
        glGenRenderbuffers(1, &this->F_rbo);
        glGenTextures(1, &this->F_texture);
        glBindTexture(GL_TEXTURE_2D, this->F_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->window->width, this->window->height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindRenderbuffer(GL_RENDERBUFFER, this->F_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->window->width, this->window->width);
        glBindFramebuffer(GL_FRAMEBUFFER, this->F_fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->F_texture, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->F_rbo);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
    
	}
    void Bloompost::bind() {
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
	GLuint Bloompost::process(const GLuint& src) {
        glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->input_sh->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, src);
        this->input_sh->SetInt("src", 0);
        this->renderquad();

        GLboolean horizontal = true, first_iteration = true;
        this->blur_sh->use();
        for (GLuint i = 0; i < amount; i++)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);

            this->blur_sh->SetInt("horizontal", horizontal);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, first_iteration ? this->rendertexture[1] : this->pingpongBuffer[!horizontal]);
            this->blur_sh->SetInt("src", 0);
            this->renderquad();
            horizontal = !horizontal;
            if (first_iteration)
                first_iteration = false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, this->F_fbo);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->combine_sh->use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->pingpongBuffer[1]);
        this->combine_sh->SetInt("blur", 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, this->rendertexture[0]);
        this->combine_sh->SetInt("origin", 1);
        return this->F_texture;
	}
    void Bloompost::renderquad() {
        glBindVertexArray(this->quadvao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }
}