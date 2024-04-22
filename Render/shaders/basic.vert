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
uniform int particlenum;
uniform vec2 dir[100];
uniform vec2 pivot[100];
uniform sampler2D flowmap;
out vec3 Fragpos;
out vec3 Normal;
out vec2 UV;
out vec3 orinormal;

const vec2 ranpos = vec2(0.5,0.5);
vec3 Gerstner(vec4 wave,vec3 originpos, inout vec3 tangent, inout vec3 bitangent){
	vec2 dir = normalize(wave.xy);
	float  k = (2*PI)/max(1,wave.w);
	float amplitude = (abs(wave.z)/(abs(wave.z)+1))/k;
	 float speed = sqrt(9.8 / k);
	float x = k*(dot(dir,originpos.xz) - speed*time);
	float z = k*(originpos.z - time+0.5);
	originpos.y += amplitude*sin(x);
	originpos.x += amplitude*cos(x) * dir.x;
	originpos.z += amplitude*cos(x) * dir.y;
	float dy = amplitude*k*cos(x);
	tangent += normalize(vec3(1-amplitude*k*sin(x)* dir.x* dir.x , dy* dir.x ,  0));
	bitangent += normalize(vec3(0 ,  dy* dir.y  ,  1-amplitude*k*sin(x)* dir.y* dir.y));
	return originpos;
}
float customRect(float x) {
	x = abs(x);
	if(x < 0.5f)
		return 1;
	else if(x == 0.5f)
		return 0.5f;
	return 0;
}
vec3 Partical(vec3 origin,vec2 dir,float step,vec2 pivot){
	//float  k = (2*PI)/max(1,wave.w);
	//origin.y += (cos((2*PI)*(origin.x+time)/5)) * customRect((origin.x+time)/5)*(cos((2*PI)*(origin.z+time)/5))* customRect((origin.z+time)/5);
	//float x = dot(dir,originpos.xz);

	//smoothstepÄ£Äâ
	float xleft = (pivot.x+sin(time*dir.x));
	float xright = xleft+step;
	float zleft = (pivot.y+sin(time*dir.y));
	float zright = zleft+step;
	float xmid = (xleft + xright)/2;
	float zmid = (zleft + zright)/2;
	float y1 = smoothstep(xleft,xmid,origin.x );
	float y2 = smoothstep(xmid,xright,origin.x );
	float y3 = smoothstep(zleft,zmid,origin.z );
	float y4 = smoothstep(zmid,zright,origin.z );
	origin.y +=(y1-y2)*(y3-y4);
	origin.x = 0;
	origin.z = 0;
	return origin;
}
void main(){
	vec4 position = model *vec4(Pos,1.0);
	vec3 tangent,bitangent;
	vec3 Wavepos = position.xyz;
	for(int i = 0; i < particlenum;++i){
		vec2 direction = texture(flowmap,dir[i]).rg*2.0-1.0;
		Wavepos += Partical(position.xyz,direction,6,pivot[i]);
	}
	//position = model *vec4(Wavepos,1.0);
	Wavepos += Gerstner(wavep,position.xyz,tangent,bitangent);
	Wavepos += Gerstner(wavep2,position.xyz,tangent,bitangent);
	Wavepos += Gerstner(wavep3,position.xyz,tangent,bitangent);
	Fragpos =Wavepos;
	UV = uvs;
	Normal = cross(bitangent,tangent);
	//Normal = normal;
	orinormal = normal;
	gl_Position = projection * view*  vec4(Wavepos,1.0f);
	//Normal = normal;
}
//	float mid = (left + right)/2;
//float y1 = smoothstep(left,mid,origin.x );
//float y2 = smoothstep(mid,right,origin.z );
//origin.y = y1 - y2;