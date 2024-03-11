#include"RenderConfig.h"
void RenderConfig::NormalUnformset() {

}
void RenderConfig::Uniformset(std::shared_ptr<Shader> shader) {
	this->shader = shader;
	switch (Type)
	{
	case Normal:
		this->NormalUnformset();
		break;
	case ulit:
		break;
	default:
		break;
	}
}
RenderConfig::RenderConfig() {
	this->Type = Normal;
}
RenderConfig::RenderConfig(const ConfigType& type) {
	this->Type = type;
}