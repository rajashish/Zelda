#include "health.h"
#include "main.h"

Health::Health(float x, float y,float z, color_t color1, color_t color2) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->color1=color1;
    this->color2 = color2;


    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {
       0 , 0 , 0.6 ,
       0 , 0.6 , 0 ,
       -0.3, 0 , 0 ,

       0 , 0 , 0.6 ,
       0 , 0.6 , 0 ,
       0.3, 0 , 0 ,



            //a

       0 , 0 , -0.6 ,
       0 , -0.6 , 0 ,
       -0.3 , 0 , 0 ,

       0 , 0 , -0.6 ,
       0 , -0.6 , 0 ,
       0.3 , 0 , 0 ,



    };

    this->object1 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data1 , this->color1, GL_FILL);

static const GLfloat vertex_buffer_data2[] = {

        0 , 0 , 0.6 ,
        0 , -0.6 , 0 ,
        -0.3 , 0 , 0 ,

        0 , 0 , 0.6 ,
        0 , -0.6 , 0 ,
        0.3 , 0 , 0 ,

        //c
        0 , 0 , -0.6 ,
        0 , 0.6 , 0 ,
        -0.3, 0 , 0 ,

        0 , 0 , -0.6 ,
        0 , 0.6 , 0 ,
        0.3, 0 , 0 ,

};
this->object2 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data2 , this->color2, GL_FILL);


    GLfloat barrels[] = {
            1.3 , 0.9 , -0.9 ,
            1.3 , 0.9 , 0.9 ,
            1.3 , -0.9 , -0.9 ,

            1.3 , -0.9 , 0.9 ,
            1.3 , 0.9 , 0.9 ,
            1.3 , -0.9 , -0.9 ,

            1.2 , 0.9 , -0.9 ,
            1.2 , 0.9 , 0.9 ,
            1.2 , -0.9 , -0.9 ,

            1.2 , -0.9 , 0.9 ,
            1.2 , 0.9 , 0.9 ,
            1.2 , -0.9 , -0.9 ,

            // rt
            1.3 , 0.9 , 0.9 ,
            1.3 , -0.9 , 0.9 ,
            1.2 , 0.9 , 0.9 ,

            1.2 , -0.9 , 0.9 ,
            1.3 , -0.9 , 0.9 ,
            1.2 , 0.9 , 0.9 ,
            //brt
            1.3 , 0.9 , -0.9 ,
            1.3 , -0.9 , -0.9 ,
            1.2 , 0.9 , -0.9 ,

            1.2 , -0.9 , -0.9 ,
            1.3 , -0.9 , -0.9 ,
            1.2 , 0.9 , -0.9 ,

            //frnt

            1.3 , 0.9 , -0.9 ,
            1.3 , 0.9 , 0.9 ,
            1.2 , 0.9 , -0.9 ,

            1.3 , 0.9 , 0.9 ,
            1.2 , 0.9 , -0.9,
            1.2 , 0.9 , 0.9 ,

            //bfrnt
            1.3 , -0.9 , -0.9 ,
            1.3 , -0.9 , 0.9 ,
            1.2 , -0.9 , -0.9 ,

            1.3 , -0.9 , 0.9 ,
            1.2 , -0.9 , -0.9,
            1.2 , -0.9 , 0.9 ,
    };
    this->barrel = create3DObject(GL_TRIANGLES, 36, barrels , COLOR_BARREL, GL_FILL);
};

void Health::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.9, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->barrel);
}

void Health::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Health::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

