#include "main.h"
#include "canon.h"

Canon::Canon(float x,float y,float z) {

    this->position = glm::vec3(x, y, z);
    this->rotation =0;

    GLfloat can[] = {
        -0.2 , 0.1 , -0.1 ,
        -0.2 , 0.1 , 0.1 ,
        - 0.4 , 0.1 , -0.1 ,

        -0.2 , 0.1 , 0.1 ,
        - 0.4 , 0.1 , -0.1 ,
        -0.4 , 0.1 , 0.1 ,



        -0.9 , 0.7 , -0.1 ,
        -0.9 , 0.7 , 0.1 ,
        - 1.1 , 0.7 , -0.1 ,

        -0.9 , 0.7 , 0.1 ,
        - 1.1 , 0.7 , -0.1 ,
        -1.1 , 0.7 , 0.1 ,

        //a
        -0.2 , 0 , -0.1 ,
        -0.2 , 0 , 0.1 ,
        -0.9 , 0.7 , -0.1 ,

        -0.2 , 0 , 0.1 ,
        -0.9 , 0.7 , -0.1 ,
        -0.9 , 0.7 , 0.1 ,


        -0.4 , 0 , -0.1 ,
        -0.4 , 0 , 0.1 ,
        -1.1 , 0.7 , -0.1 ,

        -0.4 , 0 , 0.1 ,
        -1.1 , 0.7 , -0.1 ,
        -1.1 , 0.7 , 0.1 ,

        //b

        -0.9 , 0.7 , 0.1 ,
         -0.2 , 0 , 0.1 ,
        -1.1 , 0.7 , 0.1 ,

        -0.2 , 0 , 0.1 ,
        -1.1 , 0.7 , 0.1 ,
        -0.4 , 0 , 0.1 ,


        -0.9 , 0.7 , -0.1 ,
        -0.2 , 0 , -0.1 ,
        -1.1 , 0.7 , -0.1 ,

        -0.2 , 0 , -0.1 ,
        -1.1 , 0.7 , -0.1 ,
        -0.4 , 0 , -0.1 ,


        -0.9 , 0.7 , 0.1 ,
         -0.2 , 0 , 0.1 ,
        -1.1 , 0.7 , 0.1 ,

        -0.2 , 0 , 0.1 ,
        -1.1 , 0.7 , 0.1 ,
        -0.4 , 0 , 0.1 ,




    };

    this->canon = create3DObject(GL_TRIANGLES, 36, can, COLOR_CANNON, GL_FILL);
};


void Canon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(-1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->canon);

}