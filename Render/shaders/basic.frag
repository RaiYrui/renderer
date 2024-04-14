#version 330 core
uniform vec3 Lightpos[100];
uniform vec4 Lightcolor[100];
uniform float Intensity[100];
uniform vec4 color;
uniform vec3 Campos;
uniform int Lightnum;
uniform vec3 Lightdir;
uniform samplerCube cubemap;
uniform sampler2D maintex;
uniform float time;
uniform vec4 NST;
in vec3 Fragpos;
in vec3 Normal;
in vec2 UV;
in vec3 orinormal;
out vec4 FragColor;
vec3 getNormalFromMap()
{
    vec3 tangentNormal = (texture(maintex, vec2(UV.x-(time*0.1f),UV.y-(time*0.1f)) * NST.xy  * NST.zw).rgb * 2.0 - 1.0)*5;

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
vec3 blendNormals(vec3 n1, vec3 n2,float factor) {
    return normalize(mix(n1,n2,factor));
}
void main(){
	//refraction
	 float ratio = 1.00 / 1.52;

	 vec3 nmap = getNormalFromMap();
	vec3 n = normalize(Normal);
	vec3 E = normalize(Campos-Fragpos);
	vec4 diffuse =color;
	//∑¥…‰
	vec3 blendn = blendNormals(nmap,n,0.5f);
	vec3 R = reflect(-E,blendn);
	vec4 refcolor = vec4(texture(cubemap,R).rgb,1.0f);
	//’€…‰
	vec3 refraction = refract(-E, n, ratio);
	vec4 refracolor = vec4(texture(cubemap,refraction).rgb,1.0f);
	diffuse.rgb = mix(refracolor.rgb,diffuse.rgb,diffuse.a);
	diffuse.a = 1.0f;

	FragColor = diffuse;
	FragColor.rgb += (refcolor.rgb*0.1f);
	for(int i =0; i < Lightnum;++i){
		vec3 L = normalize(-Lightdir);
		vec3 H = normalize(L+E);
		float fresnel = dot(H,E);
		fresnel = max(fresnel,0.0f);
		fresnel = 1.0f - fresnel;
		fresnel = pow(fresnel,6.0f);

		float spec = pow(clamp(dot(blendn,H),1,0),32);
		vec4 specolor = spec * Lightcolor[i] * Intensity[i];
		//specolor = mix(specolor,vec4(1.0f),fresnel);
		FragColor += specolor;
	}
	//FragColor.a = 0.7;
	// FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}