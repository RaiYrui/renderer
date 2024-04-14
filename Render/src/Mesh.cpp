#include "Mesh.h"
namespace RR {
    std::unordered_map<std::string, std::shared_ptr<Uniform>> Mesh::global_uniform;
    std::unordered_map<std::string, GLuint> Mesh::vaomap;
    void Mesh::Start() {
        std::cout << "mesh start" << std::endl;
    }
    void Mesh::setGlobaluniform() {
        for (std::pair<std::string,std::shared_ptr<Uniform>> it : this->global_uniform) {
            this->material->setUniform(it.first, it.second->type, it.second->data);
            //std::cout << it.first << it.second->data.Vec3.y << std::endl;
        }
        this->material->renderConfig();
    }
    void Mesh::Update() {
        this->material->Compileshader();
        this->setGlobaluniform();
        this->draw();

    }
    void Mesh::Destroy() {

    }
    void Mesh::Inspector_dis() {
        if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen)) {
            this->material->Render_ui();
        }
    }
    Mesh::Mesh() {
        this->name = "Mesh";
        mesh_data = std::make_shared<MeshItem>();
    }
    Mesh::Mesh(const Mesh& mesh) {
        this->name = mesh.name;
        this->mesh_data = std::make_shared<MeshItem>(*mesh.mesh_data.get());
        this->vao = mesh.vao;
        this->vertexbuffer = mesh.vertexbuffer;
        this->uvbuffer = mesh.uvbuffer;
        this->normalbuffer = mesh.normalbuffer;
        this->drawsize = mesh.drawsize;
        this->material = std::make_shared<Material>(*mesh.material.get());
    }
    void Mesh::GPUupload() {
        if (vaomap.find(this->entity->name) != vaomap.end()) {
            vao = vaomap[this->entity->name];
            return;
        }
        if (!mesh_data.get()) {
            std::cout << "Íø¸ñÊı¾İÈ±Ê§" << std::endl;
            return;
        }
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, this->mesh_data->vertex.size() * sizeof(glm::vec3), &this->mesh_data->vertex[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glGenBuffers(1, &uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, this->mesh_data->uv.size() * sizeof(glm::vec2), &this->mesh_data->uv[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glGenBuffers(1, &normalbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glBufferData(GL_ARRAY_BUFFER, this->mesh_data->normal.size() * sizeof(glm::vec3), &this->mesh_data->normal[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        vaomap[this->entity->name] = vao;
    }
    void Mesh::draw() {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, this->mesh_data->vertex.size());
        //glDrawArrays(GL_LINE_STRIP, 0, this->mesh_data->vertex.size());
        glBindVertexArray(0);
    }
    void Mesh::Load(const char* path) {
        this->mesh_data = std::make_shared<MeshItem>(*Loadobj(path));
    }
    std::shared_ptr<Material> Mesh::getmaterial() {
        return this->material;
    }
    void Mesh::setMat(std::shared_ptr<Material> mat) {
        this->material = mat;
    }
    Mesh::~Mesh() {
    }
}