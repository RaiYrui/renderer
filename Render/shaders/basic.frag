#version 330 core
uniform vec3 Lightpos[100];
uniform vec4 Lightcolor[100];
uniform float Intensity[100];
uniform vec4 color;
uniform vec3 Campos;
uniform int Lightnum;
uniform samplerCube cubemap;
uniform sampler2D maintex;
uniform float time;
in vec3 Fragpos;
in vec3 Normal;
in vec2 UV;
out vec4 FragColor;
vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(maintex, vec2(UV.x-(time*0.1),UV.y-(time*0.1))).rgb * 2.0 - 1.0;

    vec3 Q1  = dFdx(Fragpos);
    vec3 Q2  = dFdy(Fragpos);
    vec2 st1 = dFdx(UV);
    vec2 st2 = dFdy(UV);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}
void main(){
	
	 vec3 n = getNormalFromMap();
	//vec3 bc = texture(maintex, vec2(UV)).rgb;
	//vec3 n = normalize(Normal);
	vec3 E = normalize(Campos-Fragpos);
	vec4 diffuse =color;
	vec4 ambientcolor = vec4(0.3,0.3,0.3,1.0)*diffuse;
	FragColor = ambientcolor;
	vec3 R = reflect(-E,n);
	vec4 refcolor = vec4(texture(cubemap,R).rgb,1.0f);

	FragColor += (refcolor*0.01f);
	for(int i =0; i < Lightnum;++i){
		vec3 L = normalize(Lightpos[i]-Fragpos);
		vec3 H = normalize(L+E);
		float fresnel = dot(H,E);
		fresnel = max(fresnel,0.0f);
		fresnel = 1.0f - fresnel;
		fresnel = pow(fresnel,5.0f);

		float spec = pow(clamp(dot(n,H),1,0),32);
		vec4 specolor = spec * Lightcolor[i] * Intensity[i] * 0.8f;
		specolor = mix(specolor,vec4(1.0f),fresnel);
		float cos = clamp(dot(n,L),1,0);
		FragColor +=
		(diffuse * Lightcolor[i] *Intensity[i]* cos+
		specolor );
	}
	
	//FragColor.a = 0.6f;
	// FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}