#include "main.h"

#ifndef MAN_H
#define MAN_H


class Man {
public:
    Man() {}
    Man(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    //  color_t color1;
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

};

extern const color_t COLOR_RED;
extern const color_t COLOR_DRED;
extern const color_t COLOR_SEA;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_BROWN;
extern const color_t COLOR_PINK;

#endif // MAN_H
