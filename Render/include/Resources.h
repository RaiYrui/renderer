#pragma once
#include<GLFW/glfw3.h>
#include<iostream>
#include<memory>
#include"stb_image.h"
#include"MeshItem.h"
MeshItem* Loadobj(const char* path);
/// <summary>
/// ��ͼ����
/// </summary>
enum Textype {
	None=0,
	RED8,
	RGB8,
	RGBA8,
	RGBA32F,
};
/// <summary>
/// ��ͼ��Ϣ
/// </summary>
struct TextureInfo {
	GLuint id=0;
	int width=0;
	int height=0;
	char* path=(char*)"";
	std::string name;
};
/// <summary>
/// ��ͼ��
/// </summary>
class Texture {
private:
	std::shared_ptr<TextureInfo> tex;
	unsigned char* data;
	int format;
public:
	Texture();
	bool LoadTexture(const char* path);
	void UpLoad();
};