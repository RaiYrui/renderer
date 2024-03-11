#pragma once
#include<glm/gtc/matrix_transform.hpp>
#include "Material.h"
#include"Component.h"
#include"Transform.h";
#include"RObject.h"
#include<vector>
#include"Resources.h"
/// <summary>
/// 网格类
/// </summary>
class Mesh : public Component{
private:
	//网格数据
	std::shared_ptr<MeshItem> mesh_data;
	//Transform
	std::shared_ptr<Transform> transform;
	//模型数据路径
	char* path;
	static std::unordered_map<std::string, GLuint> vaomap;
	GLuint vao, vertexbuffer, uvbuffer, normalbuffer;
	int drawsize;
	void setGlobaluniform();
public:
	static glm::mat4 view;
	static glm::mat4 projection;
	static glm::vec3 campos;
	//网格中存储材质
	std::shared_ptr<Material> material;
	Mesh();
	void Load(const char* path);
	void Start()override;
	void Update()override;
	void Destroy()override;
	void GPUupload();
	void draw();
	std::shared_ptr<Material> getmaterial();
};