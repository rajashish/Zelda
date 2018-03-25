#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y,float z);
    glm::vec3 position;
    glm::vec3 position_f;
    float rotation;
    float rotation_f;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x,float y, float z);


private:
    VAO *base;
    VAO *side;
    VAO *rod;
    VAO *flag;
    VAO *corner;
};

extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_RED;
extern const color_t COLOR_DRED;
extern const color_t COLOR_BROWN;

#endif // BOAT_H