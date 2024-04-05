#include"Resources.h"
namespace RR {
    //---------------------------Texture---------------------------------
    Texture::Texture(std::string name) {
        tex = std::make_shared<TextureInfo>();
        this->tex->name = name;
        glGenTextures(1, &this->tex->id);
    }
    bool Texture::LoadTexture(const char* path) {
        stbi_set_flip_vertically_on_load(false);
        this->type = Normaltex;
        this->tex->path = (char*)path;
        if (this->tex.get() != nullptr) {
            this->data = stbi_load(this->tex->path, &this->tex->width, &this->tex->height, &this->format, 0);
            if (this->data) {
                 glBindTexture(GL_TEXTURE_2D, this->tex->id);
                 GLenum f;
                 if (this->format == 1)
                     f = GL_RED;
                 else if (this->format == 4)
                     f = GL_RGBA;
                 else
                     f = GL_RGB;
                 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->tex->width, this->tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(this->data);
                glGenerateMipmap(GL_TEXTURE_2D);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                return true;
            }
        }
        std::cout << "��ͼδ��ʼ��" << std::endl;
        return false;
    }
    bool Texture::LoadHDR(const char* path) {
        stbi_set_flip_vertically_on_load(true);
        this->type = HDR;
        this->tex->path = (char*)path;
        if (this->tex.get() != nullptr) {
            this->hdr_data = stbi_loadf(path, &this->tex->width, &this->tex->height, &this->format, 0);
            if (this->hdr_data) {
                GLenum f1,f2;
                if (this->format == 4) {
                    f1 = GL_RGBA;
                    f2 = GL_RGBA16F;
                }
                else {
                    f1 = GL_RGB;
                    f2 = GL_RGB16F;
                }
                glBindTexture(GL_TEXTURE_2D, this->tex->id);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->tex->width, this->tex->height, 0, GL_RGB, GL_FLOAT, this->hdr_data);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                
                stbi_image_free(this->hdr_data);
                std::cout << "HDR����" << std::endl;
                return true;
            }
        }
        std::cout << "HDR����ʧ��" << std::endl;
        return false;
    }
    void Texture::Setname(std::string n) {
        this->tex->name = n;
    }
    std::shared_ptr<TextureInfo> Texture::Getinfo() {
        return this->tex;
    }
    //---------------------------Model---------------------------------
    MeshItem* Loadobj(const char* path) {
        printf("Loading OBJ file %s...\n", path);
        MeshItem* mesh_data = new MeshItem();
        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<glm::vec3> temp_vertices;
        std::vector<glm::vec2> temp_uvs;
        std::vector<glm::vec3> temp_normals;

        FILE* file = fopen(path, "r");
        if (file == NULL)
        {
            printf("Impossible to open the file ! right path ? \n");
            getchar();
            return mesh_data;
        }
        mesh_data->vertex.clear();
        mesh_data->uv.clear();
        mesh_data->normal.clear();
        while (1)
        {

            char lineHeader[128];

            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF)
                break;
            // else : parse lineHeader

            if (strcmp(lineHeader, "v") == 0)
            {
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                temp_vertices.push_back(vertex);
            }
            else if (strcmp(lineHeader, "vt") == 0)
            {
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y);
                uv.y = -uv.y;
                temp_uvs.push_back(uv);
            }
            else if (strcmp(lineHeader, "vn") == 0)
            {
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                temp_normals.push_back(normal);
            }
            else if (strcmp(lineHeader, "f") == 0)
            {
                char buf[128];
                fscanf(file, "%s", buf);

                int v, n, t;
                if (strstr(buf, "//"))
                {

                    sscanf(buf, "%d//%d", &v, &n);
                    vertexIndices.push_back(v);
                    normalIndices.push_back(n);
                    fscanf(file, "%d//%d", &v, &n);
                    vertexIndices.push_back(v);
                    normalIndices.push_back(n);
                    fscanf(file, "%d//%d", &v, &n);
                    vertexIndices.push_back(v);
                    normalIndices.push_back(n);
                }
                else if (sscanf(buf, "%d/%d/%d", &v, &t, &n) == 3)
                {

                    vertexIndices.push_back(v);
                    uvIndices.push_back(t);
                    normalIndices.push_back(n);
                    fscanf(file, "%d/%d/%d", &v, &t, &n);
                    vertexIndices.push_back(v);
                    uvIndices.push_back(t);
                    normalIndices.push_back(n);
                    fscanf(file, "%d/%d/%d", &v, &t, &n);
                    vertexIndices.push_back(v);
                    uvIndices.push_back(t);
                    normalIndices.push_back(n);
                }
                else if (sscanf(buf, "%d/%d", &v, &t) == 2)
                {

                    vertexIndices.push_back(v);
                    uvIndices.push_back(t);
                    fscanf(file, "%d/%d", &v, &t);
                    vertexIndices.push_back(v);
                    uvIndices.push_back(t);
                    fscanf(file, "%d/%d", &v, &t);
                    vertexIndices.push_back(v);
                    uvIndices.push_back(t);
                }
                else
                {

                    sscanf(buf, "%d", &v);
                    vertexIndices.push_back(v);
                    fscanf(file, "%d", &v);
                    vertexIndices.push_back(v);
                    fscanf(file, "%d", &v);
                    vertexIndices.push_back(v);
                }
            }
            else
            {

                char stupidBuffer[1000];
                fgets(stupidBuffer, 1000, file);
            }
        }

        for (unsigned int i = 0; i < vertexIndices.size(); i++)
        {
            unsigned int vertexIndex = vertexIndices[i];
            glm::vec3 vertex = temp_vertices[vertexIndex - 1];
            mesh_data->vertex.push_back(vertex);

            glm::vec2 uv;
            if (temp_uvs.size())
            {
                unsigned int uvIndex = uvIndices[i];
                uv = temp_uvs[uvIndex - 1];
            }
            else
                // uv = glm::vec2(float(i)/vertexIndices.size(),1.0f-float(i)/vertexIndices.size());
                uv = glm::vec2(0, 0);
            mesh_data->uv.push_back(uv);

            glm::vec3 normal;
            if (normalIndices.size())
            {
                unsigned int normalIndex = normalIndices[i];
                normal = temp_normals[normalIndex - 1];
            }
            else
                normal = glm::vec3(1, 1, 1);
            mesh_data->normal.push_back(normal);
        }

        fclose(file);
        std::cerr << "file loaded!\n";
        return mesh_data;
    }

}