#version 330 core
layout(location = 0) in vec3 position;
out vec3 Fragpos;
uniform mat4 view;
uniform mat4 projection;

void main(){
	mat4 rotview = mat4(mat3(view));
	vec4 pos = projection * rotview * vec4(position,1.0f);
	gl_Position = pos.xyww;
	Fragpos = position;
}