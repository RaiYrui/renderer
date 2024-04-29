#version 430 core
layout(location = 0)in vec3 pos;
layout(location = 1)in vec2 uvs;
layout(location = 2)in vec3 normal;
out vec2 UV;
out vec3 Normal;
out vec3 Fragpos;
out vec3 orinormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	vec4 position = model * vec4(pos,1.0f);
	UV = uvs;
	Fragpos = position.xyz;
	gl_Position = projection * view * position;
}