#include "main.h"

#ifndef CANON_H
#define CANON_H


class Canon {
public:
    Canon() {}
    Canon(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    //  color_t color1;
    //color_t color2;
    void draw(glm::mat4 VP);
    //void set_position(float x, float y, float z);
    //void tick();
    //double speed;
private:
    VAO *canon;



};

extern const color_t COLOR_RED;
extern const color_t COLOR_DRED;
extern const color_t COLOR_SEA;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_CANNON;

#endif // CANON_H
