#pragma once
#include<glm/gtc/matrix_transform.hpp>
#include "Material.h"
#include"Component.h"
#include"Transform.h";
#include"RObject.h"
#include<vector>
#include"Resources.h"
namespace RR {
	/// <summary>
	/// ������
	/// </summary>
	class Mesh : public Component {
	private:
		//��������
		std::shared_ptr<MeshItem> mesh_data;
		//Transform
		std::shared_ptr<Transform> transform;
		//ģ������·��
		char* path;
		static std::unordered_map<std::string, GLuint> vaomap;
		GLuint vao, vertexbuffer, uvbuffer, normalbuffer;
		int drawsize;
		void setGlobaluniform();
		void draw();
	public:
		static glm::mat4 view;
		static glm::mat4 projection;
		static glm::vec3 campos;
		//�����д洢����
		std::shared_ptr<Material> material;
		Mesh();
		void Load(const char* path);
		void Start()override;
		void Update()override;
		void Destroy()override;
		void GPUupload();
		std::shared_ptr<Material> getmaterial();
	};
}