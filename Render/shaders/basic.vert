#version 330 core
layout(location = 0) in vec3 Pos;
layout(location = 1) in vec2 uvs;
layout(location = 2) in vec3 normal;
const float PI = 3.14159265358979323846;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform vec4 wavep;
out vec3 Fragpos;
out vec3 Normal;
out vec2 UV;
void main(){
	vec4 position = model *vec4(Pos,1.0);
	float  k = (2*PI)/8;
	float amplitude = wavep.z;
	float x = k*(position.x - time);
	float z = k*(position.z - time+0.5);
	position.y = amplitude*sin(x)+amplitude*sin(z);
	position.x += amplitude*cos(x);
	position.z += amplitude*cos(z);
	Fragpos = vec3(position);
	UV = uvs;
	vec3 tangent = normalize(vec3(1-amplitude*k*sin(x),amplitude*k*cos(x),0));
	vec3 bitangent = normalize(vec3(0,amplitude*k*cos(z),1-amplitude*k*sin(z)));
	Normal = cross(bitangent,tangent);
	gl_Position = projection * view *  position;
	//Normal = normal;
}