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
uniform vec4 wavep2;
uniform vec4 wavep3;
out vec3 Fragpos;
out vec3 Normal;
out vec2 UV;
vec3 Gerstner(vec4 wave,vec3 originpos, inout vec3 tangent, inout vec3 bitangent){
	vec2 dir = normalize(wave.xy);
	float  k = (2*PI)/max(1,wave.w);
	float amplitude = (abs(wave.z)/(abs(wave.z)+1))/k;
	 float speed = sqrt(9.8 / k);
	float x = k*(dot(dir,originpos.xz) - speed*time);
	float z = k*(originpos.z - time+0.5);
	originpos.y = amplitude*sin(x);
	originpos.x += amplitude*cos(x) * dir.x;
	originpos.z += amplitude*cos(x) * dir.y;
	tangent += normalize(vec3(1-amplitude*k*sin(x)* dir.x* dir.x,amplitude*k*cos(x)* dir.x,0));
	bitangent += normalize(vec3(0,amplitude*k*cos(x)* dir.y,1-amplitude*k*sin(x)* dir.y* dir.y));
	return originpos;
}
void main(){
	vec4 position = model *vec4(Pos,1.0);
	vec3 tangent,bitangent;

	vec3 Wavepos = Gerstner(wavep,position.xyz,tangent,bitangent);
	Wavepos += Gerstner(wavep2,position.xyz,tangent,bitangent);
	Wavepos += Gerstner(wavep3,position.xyz,tangent,bitangent);
	Fragpos = Wavepos;
	UV = uvs;
	Normal = cross(bitangent,tangent);
	gl_Position = projection * view *  vec4(Wavepos,1.0);
	//Normal = normal;
}