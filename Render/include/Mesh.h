#pragma once
#include<glm/gtc/matrix_transform.hpp>
#include "Material.h"
#include"Component.h"
#include<vector>
namespace RR {
	/// <summary>
	/// ������
	/// </summary>
	class Mesh : public Component {
	private:
		//��������
		std::shared_ptr<MeshItem> mesh_data;
		//ģ������·��
		char* path;
		static std::unordered_map<std::string, GLuint> vaomap;
		GLuint vao, vertexbuffer, uvbuffer, normalbuffer;
		int drawsize;
		void setGlobaluniform();
		void draw();
		//�����д洢����
		std::shared_ptr<Material> material;
	public:
		static std::unordered_map<std::string, std::shared_ptr<Uniform>>global_uniform;
		Mesh();
		Mesh(const Mesh& mesh);
		Component* copy()override;
		void Load(const char* path);
		void Start()override;
		void Update()override;
		void Destroy()override;
		void Inspector_dis()override;
		void setMat(std::shared_ptr<Material>mat);
		void GPUupload();
		std::shared_ptr<Material> getmaterial();
		~Mesh();
	};
}