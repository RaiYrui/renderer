#version 330 core
in vec2 UV;
out vec4 FragColor;
uniform sampler2D origin;
uniform sampler2D blur;

void main(){
	FragColor = vec4(texture(origin,UV).rgb+texture(blur,UV).rgb,1.0f);
	//FragColor = texture(origin,UV);
}