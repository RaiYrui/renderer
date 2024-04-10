#pragma once
#include<glm/glm.hpp>
#include<unordered_map>
#include<memory>
#include<IMGUI/imgui.h>
#include "Shader.h"
#include "Resources.h"
#include "Type.h"
namespace RR {
	//渲染设置
	enum ConfigType
	{
		Normal = 0,
		ulit,
		Pbr,
	};
	struct Color {
		float r, g, b, a;
		Color(float red = 1.0, float green = 1.0, float blue = 1.0, float alpha = 1.0);
		void SetColor(float red, float green, float blue, float alpha = 1.0);
		Color* operator+(Color& col);
		Color* operator -(Color& col);
	};

	/// <summary>
	/// 材质类
	/// </summary>
	class Material {
	private:
		static std::unordered_map<std::string, GLuint> shadermap;
		std::unordered_map<std::string, std::shared_ptr<Uniform>> uniform_map;
		std::shared_ptr<Texture> maintex;
		std::shared_ptr<Shader> shader;
		glm::vec4 color;
		ConfigType type;
		void Normaluniform();
		void Pbruniform();
		//测试用
		glm::vec4 w1, w2, w3;
		glm::vec4 nst;
		float mat, rough, ao;
	public:
		//天空盒
		static uniform_data env;
		//UI对接
		void Render_ui();
		void Compileshader();
		void AddShader(std::shared_ptr<Shader> shader);
		void RemoveShader();
		void setUniform(const std::string& name, Uniformv type, uniform_data value);
		std::string getkey();
		//需要定制化的uniform设置
		void Setcongif(const ConfigType& type);
		void renderConfig();
		Material();
	};
}