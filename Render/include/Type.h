#pragma once
namespace RR {
	/// <summary>
/// Uniform类型枚举
/// </summary>
	enum Uniformv {
		Vec3 = 0,
		Vec4,
		Float,
		Int,
		Mat4,
		Bool
	};
	/// <summary>
	/// Uniform数据union
	/// </summary>
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
	/// Uniform数据类型
	/// </summary>
	struct Uniform {
		Uniformv type;
		uniform_data data;
		Uniform(const Uniform& uni) {
			this->type = uni.type;
			this->data = uni.data;
		}
		Uniform(const Uniformv& t, const uniform_data& d) {
			this->type = t;
			this->data = d;
		}
		Uniform(const Uniformv& t = Mat4, const glm::mat4& m = glm::mat4(1.0f)) {
			this->type = t;
			this->data.Mat4 = m;
		}
		Uniform(const Uniformv& t = Vec3, const glm::vec3& m = glm::vec3()) {
			this->type = t;
			this->data.Vec3 = m;
		}
		Uniform(const Uniformv& t = Vec4, const glm::vec4& m = glm::vec4()) {
			this->type = t;
			this->data.Vec4 = m;
		}
		Uniform(const Uniformv& t = Float, const float& m = 0.0f) {
			this->type = t;
			this->data.floatvalue = m;
		}
		Uniform(const Uniformv& t = Int, const int& m = 0) {
			this->type = t;
			this->data.intvalue = m;
		}
	};
	/// <summary>
	/// 相机投影类型
	/// </summary>
	enum CamType {
		Perspective = 0,
		Orthogonal
	};
}