#version 330 core
layout(location = 0) in vec3 Pos;
layout(location = 1) in vec2 uvs;
layout(location = 2) in vec3 normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 Fragpos;
out vec3 Normal;
out vec2 UV;
void main(){
	gl_Position = projection * view * model *  vec4(Pos,1.0);
	Fragpos = vec3(model*vec4(Pos,1.0));
	UV = uvs;
	Normal = normal;
}