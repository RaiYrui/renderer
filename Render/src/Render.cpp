#include "Render.h"
namespace RR {
    void Render::render(std::vector<RObject*>& entitylist) {
        for (RObject* object : entitylist) {
            object->Update();
        }
    }
    Render::Render() {
        drawsize = 0;
    }
}