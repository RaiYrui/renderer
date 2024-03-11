#pragma once
#include"Shader.h"
enum ConfigType
{
	Normal=0,
	ulit,
};
class RenderConfig {
private:
	void NormalUnformset();
	std::shared_ptr <Shader>shader;
public:
	ConfigType Type;
	void Uniformset(std::shared_ptr<Shader> shader);
	RenderConfig();
	RenderConfig(const ConfigType& type);
	
};