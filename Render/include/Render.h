#pragma once
#include<vector>
#include"RObject.h"
/// <summary>
/// ��Ⱦʵ����
/// </summary>
class Render {
private:
	int drawsize;
	GLuint vao;
	GLuint vbo;
	GLuint vertexbuffer, uvbuffer, normalbuffer;
	std::unordered_map<std::string, GLuint>vaomap;
public:
	void render(std::vector<RObject*>& entitylist);
	Render();
};