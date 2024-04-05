#version 330 core
in vec3 Fragpos;
out vec4 FragColor;
uniform samplerCube cubemap;

void main(){
	vec3 envColor = texture(cubemap,Fragpos).rgb;
    envColor = envColor/(envColor+vec3(1.0));
    envColor = pow(envColor,vec3(1.0/2.2));
    FragColor = vec4(envColor,1.0);
}
