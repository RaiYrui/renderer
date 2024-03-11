#pragma once
#include<iostream>
#include<unordered_map>
#include"Transform.h"
#include"Mesh.h"
typedef void* (*constructor)();
/// <summary>
/// 反射注册表
/// </summary>
extern std::unordered_map<std::string, constructor>Registry;
template<class T>
void Register(const std::string& name);
void* CreateClass(const std::string& name);
void RemoveClass(const std::string& name);
/// <summary>
/// 组件管理类
/// </summary>
class ComponentManager {
private:
public:
	ComponentManager();
};