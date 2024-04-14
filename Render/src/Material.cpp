#include "Material.h"
namespace RR {
	std::unordered_map<std::string, GLuint> Material::shadermap;
	uniform_data Material::env;
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
		this->color = glm::vec4(0.055f, 0.6f, 0.8f, 1.0f);
		this->w1 = glm::vec4(3.5f, 3.0f, 0.25f, 3.0f);
		this->w2 = glm::vec4(-0.25f, -0.75f, 0.3f, 2.25f);
		this->w3 = glm::vec4(6.0f, -6.0f, 0.45f, 1.75f);
		this->maintex = std::make_shared<Texture>("maintex");
		this->maintex->LoadTexture("../../../../Render/tex/normalMap.png");
		this->nst = glm::vec4(1.0f,2.0f,2.0f,0.75f);
		this->mat = 1;
		this->rough = 0.05;
		this->ao = 1;
	}
	Material::Material(const Material& mat) {
		this->type = mat.type;
		this->color =mat.color;
		this->w1 = mat.w1;
		this->w2 = mat.w2;
		this->w3 = mat.w3;
		this->maintex = std::make_shared<Texture>(*mat.maintex.get());
		this->shader = mat.shader;
		this->nst = mat.nst;
		this->mat = mat.mat;
		this->rough = mat.rough;
		this->ao = mat.ao;
	}
	void Material::setTex(const char* path) {
		this->maintex->LoadTexture(path);
	}
	void Material::AddShader(std::shared_ptr<Shader> shader) {
		this->shader = shader;
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
			this->ulituniform();
			break;
		case Pbr:
			this->Pbruniform();
			break;
		default:
			break;
		}
	}
	void Material::Normaluniform() {
		this->shader->SetVec4("color", this->color);
		//glGetInteger(GL_MAX_FRAGMENT_UNIFORM_VECTORS)
		this->shader->SetFloat("time", glfwGetTime()*0.5f);
		this->shader->SetVec4("wavep", this->w1);
		this->shader->SetVec4("wavep2",this->w2);
		this->shader->SetVec4("wavep3", this->w3);
		this->shader->SetVec4("NST", this->nst);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, env.intvalue);
		this->shader->SetInt("cubemap", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, this->maintex->Getinfo()->id);
		this->shader->SetInt("maintex", 1);
		
	}
	void Material::Pbruniform() {
		this->shader->SetVec4("color", this->color);
		//glGetInteger(GL_MAX_FRAGMENT_UNIFORM_VECTORS)
		this->shader->SetFloat("time", glfwGetTime() * 0.5f);
		this->shader->SetVec4("wavep", this->w1);
		this->shader->SetVec4("wavep2", this->w2);
		this->shader->SetVec4("wavep3", this->w3);
		this->shader->SetVec4("NST", this->nst);
		this->shader->SetFloat("metallic", this->mat);
		this->shader->SetFloat("roughness", this->rough);
		this->shader->SetFloat("ao", this->ao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, env.intvalue);
		this->shader->SetInt("cubemap", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, this->maintex->Getinfo()->id);
		this->shader->SetInt("maintex", 1);
	}
	void Material::ulituniform() {
		this->shader->SetVec4("color", this->color);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->maintex->Getinfo()->id);
		this->shader->SetInt("maintex", 0);
	}
	void Material::Render_ui() {
		ImGui::Text("Main Color");
		ImGui::ColorEdit4("set color", (float*)&this->color);
		ImGui::Text("wave1");
		ImGui::DragFloat("x dir", &this->w1.x, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("y dir", &this->w1.y, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("amplitude", &this->w1.z, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("k", &this->w1.w, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::Text("wave2");
		ImGui::DragFloat("x2 dir", &this->w2.x, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("y2 dir", &this->w2.y, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("amplitude2", &this->w2.z, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("k2", &this->w2.w, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::Text("wave3");
		ImGui::DragFloat("x3 dir", &this->w3.x, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("y3 dir", &this->w3.y, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("amplitude3", &this->w3.z, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("k3", &this->w3.w, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("nstx", &this->nst.x, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("nsty", &this->nst.y, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("nstz", &this->nst.z, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("nstw", &this->nst.w, 0.25f, -FLT_MAX, FLT_MAX, "%.3f");
		ImGui::DragFloat("mat", &this->mat, 0.05f, 0, 1, "%.3f");
		ImGui::DragFloat("rough", &this->rough, 0.05f, 0, 1, "%.3f");
		ImGui::DragFloat("ao", &this->ao, 0.05f, 0, 1, "%.3f");
	}
}