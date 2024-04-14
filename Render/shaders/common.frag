#version 330 core
in vec3 Fragpos;
in vec2 UV;
in vec3 Normal;
out vec4 FragColor;
uniform vec4 color;
uniform sampler2D maintex;
void main(){
	vec3 c = texture(maintex,UV).rgb*0.5f;
	FragColor = vec4(c,1.0f);
}