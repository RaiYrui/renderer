#include "Material.h"
namespace RR {
	std::unordered_map<std::string, GLuint> Material::shadermap;
	std::vector<std::shared_ptr<Light>> Material::lights;
	Color::Color(float red, float green, float blue, float alpha) {
		this->r = red;
		this->g = green;
		this->b = blue;
		this->a = alpha;
	}
	void Color::SetColor(float red, float green, float blue, float alpha) {
		this->r = red;
		this->g = green;
		this->b = blue;
		this->a = alpha;
	}
	Color* Color::operator+(Color& col) {
		return new Color(this->r + col.r, this->g + col.g, this->b + col.b, this->a + col.a);
	}
	Color* Color::operator-(Color& col) {
		return new Color(this->r - col.r, this->g - col.g, this->b - col.b, this->a - col.a);
	}

	Material::Material() {
		this->type = Normal;
		this->color = glm::vec4(0.8, 0.8, 0.8, 1);
	}
	void Material::AddShader(Shader* shader) {
		this->shader = std::make_shared<Shader>(*shader);
	}
	std::string Material::getkey() {
		return this->shader->Key();
	}
	void Material::RemoveShader() {
		delete this->shader.get();
	}
	void Material::setUniform(const std::string& name, Uniformv type, uniform_data value) {
		if (shader) {
			switch (type)
			{
			case Vec3:
				shader->SetVec3(name, value.Vec3);
				break;
			case Vec4:
				shader->SetVec4(name, value.Vec4);
				break;
			case Float:
				shader->SetFloat(name, value.floatvalue);
				break;
			case Int:
				shader->SetInt(name, value.intvalue);
				break;
			case Mat4:
				shader->SetMat4(name, value.Mat4);
				break;
			case Bool:
				shader->Setbool(name, value.boolvalue);
				break;
			default:
				break;
			}
		}
		else {
			std::cout << "shader of the material not found" << std::endl;
		}
	}
	void Material::Compileshader() {
		GLuint shaderID;
		std::string key = this->shader->Key();
		auto it = shadermap.find(key);
		if (it != shadermap.end()) {
			shaderID = it->second;
		}
		else {
			shadermap[key] = this->shader->Compile();
			shaderID = shadermap[key];
		}
		glUseProgram(shaderID);
	}
	void Material::Setcongif(const ConfigType& type) {
		this->type = type;
	}
	void Material::renderConfig() {
		switch (this->type)
		{
		case Normal:
			this->Normaluniform();
			break;
		case ulit:
			break;
		default:
			break;
		}
	}
	void Material::Normaluniform() {
		this->shader->SetVec4("color", this->color);
		//glGetInteger(GL_MAX_FRAGMENT_UNIFORM_VECTORS)
		this->shader->SetVec3("Lightpos", this->lights[0]->Getpos());
		this->shader->SetVec4("Lightcolor", this->lights[0]->GetColor());
		this->shader->SetFloat("time", glfwGetTime());
	}
}