#include "main.h"

#ifndef BOSS_H
#define BOSS_H


class Boss {
public:
    Boss() {}
    Boss(float x, float y,float z,color_t color);
    glm::vec3 position;
    float rotation;
    color_t color;
    //color_t color2;
    void draw(glm::mat4 VP);
    //void set_position(float x, float y, float z);
    //void tick();
    //double speed;
private:
    VAO *leg;
    VAO *body;
    VAO *head;
    VAO *eye;
    VAO *mouth;

};

extern const color_t COLOR_RED;
extern const color_t COLOR_DRED;
extern const color_t COLOR_SEA;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_BROWN;
extern const color_t COLOR_FIRE1;
extern const color_t COLOR_FIRE2;

#endif // BOSS_H
