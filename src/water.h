#include "main.h"

#ifndef WATER_H
#define WATER_H


class Water {
public:
    Water() {}
    Water(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);


private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

extern const color_t COLOR_ISLAND;



#endif // WATERs_H