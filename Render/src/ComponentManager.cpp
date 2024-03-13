#include"ComponentManager.h"
namespace RR {
    std::unordered_map<std::string, constructor>Registry;
    template<class T>
    void Register(const std::string& name) {
        auto it = Registry.find(name);
        if (it == Registry.end())
        {
            Registry[name] = []()->void* {
                return new T();
            };
            return;
        }
        std::cout << "ÀàÖØ¸´×¢²á" << std::endl;
    }
    void* CreateClass(const std::string& name) {
        auto it = Registry.find(name);
        if (it != Registry.end())
        {
            return (it->second)();
        }
        return nullptr;
    }
    void RemoveClass(const std::string& name) {
        Registry.erase(name);
    }
    ComponentManager::ComponentManager() {
        Register<Transform>("Transform");
        Register<Mesh>("Mesh");
    }
}