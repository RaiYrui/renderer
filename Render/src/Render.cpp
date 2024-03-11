#include "Render.h"
void Render::render(std::vector<RObject*>& entitylist) {
        for(RObject * object: entitylist){
            object->Update();
        }
}
Render::Render() {
    glEnable(GL_DEPTH_TEST);
    drawsize = 0;
}