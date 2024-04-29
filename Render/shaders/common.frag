#version 430 core
in vec3 Fragpos;
in vec2 UV;
in vec3 Normal;
out vec4 FragColor;
uniform vec4 Lightcolor[100];
uniform float Intensity[100];
uniform vec3 Lightdir;
uniform vec4 color;
uniform vec3 Campos;
uniform sampler2D maintex;
const float PI = 3.14159265359;
vec3 getNormalFromMap(inout vec3 tangent,inout vec3 bitangent)
{
    vec3 tangentNormal = Normal;

    vec3 Q1  = dFdx(Fragpos);
    vec3 Q2  = dFdy(Fragpos);
    vec2 st1 = dFdx(UV);
    vec2 st2 = dFdy(UV);

    vec3 N   = normalize(Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    tangent = T;
    vec3 B  = -normalize(cross(N, T));
    bitangent = B;
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}
void main(){
	vec4 unmap = texture(maintex,UV);
	if(unmap.a <= 0.1)
		discard;
    vec3 T,B;
    vec3 V = normalize(Campos - Fragpos);
    vec3 ambient = color.rgb * 0.3;
    //主要用于计算切线副切线
	vec3 nmap = getNormalFromMap(T,B);

    //得到法线副切线近似做各向异性的光照
    vec3 fnorm = normalize(Normal + B);
    vec3 H = normalize(V + Lightdir);

	float tdl = dot(fnorm,H);
    //按照公式需要夹角的sin
    float stdl = sqrt(1.0  -(tdl*tdl));
	vec3 diff = color.rgb * clamp(stdl,1,0);

    float spec = pow(clamp(stdl,1,0),32);
    vec4 specolor = spec * Lightcolor[0] * 0.1f;
	FragColor = vec4(ambient+diff*0.1 +specolor.rgb ,unmap.a);
}