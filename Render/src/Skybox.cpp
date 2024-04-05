#include "Skybox.h"
namespace RR {
    glm::mat4 Skybox::v;
    glm::mat4 Skybox::p;
	Skybox::Skybox() {
		this->tex = std::make_shared<Texture>("map");
        this->sky_shader = std::make_shared<Shader>("../../../../Render/shaders/skybox.vert", "../../../../Render/shaders/skybox.frag");
        this->sky_shader->Compile();
		this->tex->LoadHDR("../../../../Render/tex/skycube.hdr");
        this->projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
        this->view[0] = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        this->view[1] = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        this->view[2] = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        this->view[3] = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        this->view[4] = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        this->view[5] = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        this->Uploadbuffer();
	}
    void Skybox::Rendercube() {
        std::shared_ptr<Shader> env = std::make_shared<Shader>("../../../../Render/shaders/cap.vert","../../../../Render/shaders/cap.frag");
        env->Compile();
        glGenFramebuffers(1, &capFBO);

        glGenFramebuffers(1, &capRBO);
        glBindFramebuffer(GL_FRAMEBUFFER, capFBO);
        glBindRenderbuffer(GL_RENDERBUFFER, capRBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, capRBO);
        glGenTextures(1, &cubemap);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
        Material::env.intvalue = cubemap;
        for (int i = 0; i < 6; ++i)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F,
                512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        env->use();
        env->SetInt("map", 0);
        env->SetMat4("projection", this->projection);
        
        glBindTexture(GL_TEXTURE_2D, this->tex->Getinfo()->id);
        glViewport(0, 0, 512, 512);
        glBindFramebuffer(GL_FRAMEBUFFER, capFBO);
        for (int i = 0; i < 6; ++i)
        {
            env->SetMat4("view", this->view[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, this->cubemap, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void Skybox::Render() {
        glDepthFunc(GL_LEQUAL);
        this->sky_shader->use();
        this->sky_shader->SetMat4("view", v);
        this->sky_shader->SetMat4("projection", p);
        glActiveTexture(GL_TEXTURE0);
        this->sky_shader->SetInt("cubemap", 0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
    }
	void Skybox::component_dis() {

	}
	void Skybox::Uploadbuffer() {
        float skyv[] = {
        -1.0f, 1.0f, -1.0f,-1.0f, -1.0f, -1.0f,1.0f, -1.0f, -1.0f,1.0f, -1.0f, -1.0f,1.0f, 1.0f, -1.0f,-1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,-1.0f, -1.0f, -1.0f,-1.0f, 1.0f, -1.0f,-1.0f, 1.0f, -1.0f,-1.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,1.0f, -1.0f, 1.0f,1.0f, 1.0f, 1.0f,1.0f, 1.0f, 1.0f,1.0f, 1.0f, -1.0f,1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,-1.0f, 1.0f, 1.0f,1.0f, 1.0f, 1.0f,1.0f, 1.0f, 1.0f,1.0f, -1.0f, 1.0f,-1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,1.0f, 1.0f, -1.0f,1.0f, 1.0f, 1.0f,1.0f, 1.0f, 1.0f,-1.0f, 1.0f, 1.0f,-1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,-1.0f, -1.0f, 1.0f,1.0f, -1.0f, -1.0f,1.0f, -1.0f, -1.0f,-1.0f, -1.0f, 1.0f,1.0f, -1.0f, 1.0f };
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyv), &skyv, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glBindVertexArray(0);
	}
}