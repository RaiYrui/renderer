#version 330 core
uniform vec3 Lightpos;
uniform vec4 Lightcolor;
uniform vec4 color;
uniform vec3 Campos;
in vec3 Fragpos;
in vec3 Normal;
in vec2 UV;
out vec4 FragColor;
void main(){
	vec3 n = normalize(Normal);
	vec3 E = normalize(Campos-Fragpos);
	vec3 L = normalize(Lightpos-Fragpos);
	vec3 H = normalize(L+E);
	float spec = pow(clamp(dot(n,H),1,0),32);
	vec4 diffuse = color;
	vec4 ambientcolor = vec4(0.3,0.3,0.3,1.0)*diffuse;
	float cos = clamp(dot(n,L),1,0);
	FragColor = 
	ambientcolor+
	diffuse * Lightcolor *0.8f* cos+
	spec * Lightcolor * 0.5f;
	FragColor.a = 0.6f;
	// FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}