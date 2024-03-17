#version 330 core
layout(location = 0) in vec3 Pos;
layout(location = 1) in vec2 uvs;
layout(location = 2) in vec3 normal;
const float PI = 3.14159265358979323846;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
out vec3 Fragpos;
out vec3 Normal;
out vec2 UV;
void main(){
	vec4 position = model *vec4(Pos,1.0);
	position.y =  0.5 *sin(position.x-time);
	position.x +=   cos(position.x-time);
	
	gl_Position = projection * view *  position;
	Fragpos = vec3(model*vec4(Pos,1.0));
	UV = uvs;
	Normal = normal;
}