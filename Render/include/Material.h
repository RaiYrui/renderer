#pragma once
#include<glm/glm.hpp>
#include<unordered_map>
#include<memory>
#include "Shader.h"
#include "Resources.h"
#include"Light.h"
namespace RR {
	//渲染设置
	enum ConfigType
	{
		Normal = 0,
		ulit,
	};
	struct Color {
		float r, g, b, a;
		Color(float red = 1.0, float green = 1.0, float blue = 1.0, float alpha = 1.0);
		void SetColor(float red, float green, float blue, float alpha = 1.0);
		Color* operator+(Color& col);
		Color* operator -(Color& col);
	};
	enum Uniformv {
		Vec3 = 0,
		Vec4,
		Float,
		Int,
		Mat4,
		Bool
	};
	union uniform_data
	{
		bool boolvalue;
		int intvalue;
		float floatvalue;
		glm::vec3 Vec3;
		glm::vec4 Vec4;
		glm::mat4 Mat4;
	};
	/// <summary>
	/// 材质类
	/// </summary>
	class Material {
	private:
		static std::unordered_map<std::string, GLuint> shadermap;
		std::shared_ptr<Texture> maintex;
		std::shared_ptr<Shader> shader;
		glm::vec4 color;
		ConfigType type;
		void Normaluniform();
	public:
		static std::vector<std::shared_ptr<Light>>lights;
		void Compileshader();
		void AddShader(Shader* shader);
		void RemoveShader();
		void setUniform(const std::string& name, Uniformv type, uniform_data value);
		std::string getkey();
		//需要定制化的uniform设置
		void Setcongif(const ConfigType& type);
		void renderConfig();
		Material();
	};
}