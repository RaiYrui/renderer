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
uniform sampler2D height;
uniform sampler2D xdis;
uniform sampler2D zdis;
uniform sampler2D dyx;
uniform sampler2D dyz;
uniform sampler2D ddx;
uniform sampler2D ddz;


void main(){
    vec3 p = pos;
	vec4 position = model * vec4(pos,1.0f);
	UV = uvs;
	float h = texture(height,uvs).r;
	float xd = texture(xdis,uvs).r;
	float zd = texture(zdis,uvs).r;

	float dyxf = texture(dyx,uvs).r;
	float dyzf = texture(dyz,uvs).r;
	float ddxf = texture(ddx,uvs).r;
	float ddzf = texture(ddz,uvs).r;



	position.xyz += vec3(xd,h,zd)*0.5;



	vec2 slope = vec2(-dyxf/(1+ddxf),-dyzf/(1+ddzf));
	vec3 n = vec3(slope.x,1,slope.y);
	Fragpos = position.xyz;
	gl_Position = projection * view * position;
	Normal = normalize(n);
	orinormal =  normalize(n);
}