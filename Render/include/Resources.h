#pragma once
#define GLFW_INCLUDE_NONE
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<iostream>
#include<memory>
#include"stb_image.h"
#include"MeshItem.h"
namespace RR {
	MeshItem* Loadobj(const char* path);
	/// <summary>
	/// ��ͼ��������
	/// </summary>
	enum Texdatatype {
		None = 0,
		RED8,
		RGB8,
		RGB32F,
		RGBA8,
		RGBA32F,
	};
	/// <summary>
	/// ��ͼ����
	/// </summary>
	enum Textype {
		Normaltex=0,
		HDR,
	};
	/// <summary>
	/// ��ͼ��Ϣ
	/// </summary>
	struct TextureInfo {
		GLuint id = 0;
		int width = 0;
		int height = 0;
		char* path = (char*)"";
		std::string name;
	};
	/// <summary>
	/// ��ͼ��
	/// </summary>
	class Texture {
	private:
		std::shared_ptr<TextureInfo> tex;
		Textype type;
		unsigned char* data;
		float* hdr_data;
		int format;
	public:
		Texture(std::string name = "");
		bool LoadTexture(const char* path);
		bool LoadHDR(const char* path);
		void Setname(std::string n);
		std::shared_ptr<TextureInfo> Getinfo();
		void UpLoad();
	};
}