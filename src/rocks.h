#include "main.h"

#ifndef ROCKS_H
#define ROCKS_H


class Rocks {
public:
    Rocks() {}
    Rocks(float x, float y,float z, color_t color1, color_t color2);
    glm::vec3 position;
    float rotation;
    color_t color1;
    color_t color2;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object1;
    VAO *object2;
};

extern const color_t COLOR_ROCK1;
extern const color_t COLOR_ROCK2;

#endif // ROCKS_H
