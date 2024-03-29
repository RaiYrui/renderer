#include "Mesh.h"
namespace RR {
    glm::mat4 Mesh::view;
    glm::mat4 Mesh::projection;
    glm::vec3 Mesh::campos;
    std::unordered_map<std::string, GLuint> Mesh::vaomap;
    void Mesh::Start() {
        this->transform.reset(dynamic_cast<Transform*>(this->entity->GetComponent("Transform")));
        std::cout << "mesh start" << std::endl;
    }
    void Mesh::setGlobaluniform() {
        uniform_data model, view, projection, Campos;
        //model.Mat4 = glm::scale(model.Mat4, glm::vec3(0.1f, 0.1f, 0.1f));
        model.Mat4 = this->transform->Pos_mat();
        std::cout << model.Mat4[3][1];
        this->material->setUniform("model", Mat4, model);
        view.Mat4 = Mesh::view;
        this->material->setUniform("view", Mat4, view);
        projection.Mat4 = Mesh::projection;
        this->material->setUniform("projection", Mat4, projection);
        Campos.Vec3 = this->campos;
        this->material->setUniform("Campos", Vec3, Campos);
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

        }
    }
    Mesh::Mesh() {
        this->name = "Mesh";
        material = std::make_shared<Material>();
        mesh_data = std::make_shared<MeshItem>();
    }
    void Mesh::GPUupload() {
        if (vaomap.find(this->entity->name) != vaomap.end()) {
            vao = vaomap[this->entity->name];
            return;
        }
        if (!mesh_data.get()) {
            std::cout << "Íø¸ñÊý¾ÝÈ±Ê§" << std::endl;
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
    Mesh::~Mesh() {
    }
}