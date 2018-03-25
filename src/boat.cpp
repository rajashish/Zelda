#include"main.h"
#include "boat.h"


Boat::Boat(float x,float y,float z) {

    this->position = glm::vec3(x, y, z);
    this->position_f = glm::vec3(x, y, z);
    this->color = color;
    this->rotation = 0;
    this->rotation_f = 0;
    GLfloat boat_base[10000];

    boat_base[0] = -0.1;
    boat_base[1] = 0.8;
    boat_base[2] = 0.4;


    boat_base[3] = -0.1;
    boat_base[4] = 1.2;
    boat_base[5] = 0;

    boat_base[6] = -0.1;
    boat_base[7] = 0.8;
    boat_base[8] = -0.4;


    boat_base[9] = -0.1;
    boat_base[10] = 0.8;
    boat_base[11] = 0.4;

    boat_base[12] = -0.1;
    boat_base[13] = 0.8;
    boat_base[14] = -0.4;

    boat_base[15] = -0.1;
    boat_base[16] = -0.8;
    boat_base[17] = -0.4;


    boat_base[18] = -0.1;
    boat_base[19] = 0.8;
    boat_base[20] = 0.4;

    boat_base[21] = -0.1;
    boat_base[22] = -0.8;
    boat_base[23] = -0.4;

    boat_base[24] = -0.1;
    boat_base[25] = -0.8;
    boat_base[26] = 0.4;


    boat_base[27] = -0.1;
    boat_base[28] = -0.8;
    boat_base[29] = -0.4;

    boat_base[30] = -0.1;
    boat_base[31] = -0.8;
    boat_base[32] = 0.4;

    boat_base[33] = -0.1;
    boat_base[34] = -1.2;
    boat_base[35] = 0;

    this->base = create3DObject(GL_TRIANGLES, 12, boat_base, COLOR_GREEN, GL_FILL);

   GLfloat boat_side[] = {
           -0.1 ,1.2 ,0 ,
           -0.1 ,0.8 ,0.4 ,
           -0.5 ,1.44 ,0 ,

           -0.4, 0.96, 0.48,
           -0.1 ,0.8 ,0.4 ,
           -0.5 ,1.44 ,0,




           -0.1 , -0.8 , 0.4 ,
           -0.1, -1.2 , 0 ,
           -0.5 , -1.44 , 0 ,


           -0.1 , -0.8 , 0.4 ,
         -0.4 , -0.96 , 0.48,
           -0.5 , -1.44 , 0 ,

           //aa


           -0.1 ,1.2 ,0 ,
           -0.1 ,0.8 ,-0.4 ,
           -0.5 ,1.44 ,0 ,

           -0.4, 0.96, -0.48,
           -0.1 ,0.8 ,-0.4 ,
           -0.5 ,1.44 ,0,




           -0.1 , -0.8 , -0.4 ,
           -0.1, -1.2 , 0,
           -0.5 , -1.44 , 0 ,


           -0.1 , -0.8 , -0.4 ,
           -0.4 , -0.96 , -0.48,
           -0.5 , -1.44 , 0 ,

           //aaaaa




           };

    this->side = create3DObject(GL_TRIANGLES, 24, boat_side, COLOR_RED, GL_FILL);

    GLfloat boat_corner[] = {
            -0.1 , 0.8 , 0.4 ,
            -0.1 , -0.8 , 0.4 ,
            -0.4 , 0.96 , 0.48 ,

            -0.4 , -0.96 , 0.48 ,
            -0.1 , -0.8 , 0.4 ,
            -0.4 , 0.96 , 0.48 ,


            -0.1 , 0.8 , -0.4 ,
            -0.1 , -0.8 ,-0.4 ,
            -0.4 , 0.96 , -0.48 ,

            -0.4 , -0.96 , -0.48 ,
            -0.1 , -0.8 , -0.4 ,
            -0.4 , 0.96 , -0.48 ,

   };

   this->corner = create3DObject(GL_TRIANGLES, 12, boat_corner, COLOR_DRED, GL_FILL);

    GLfloat boat_rod[] = {

            -0.1 , 0.0 , 0.05,
            -0.1 , 0.0 , -0.05,
            -1.2 , 0.0, 0.05,

            -0.1 , 0.0 , -0.05,
            -1.2 , 0.0, 0.05,
            -1.2, 0.0 , -0.05,






    };

    this->rod = create3DObject(GL_TRIANGLES, 6, boat_rod, COLOR_BROWN, GL_FILL);

    GLfloat boat_flag[] = {

            //-1.05, 0.5, 0.6,
            //-0.9, 0.5, 0.05,
            //-1.2, 0.5, 0.05,

            -1.05, 0, 0.6,
            -0.9, 0, 0.05,
            -1.2, 0, 0.05,

    };

    this->flag = create3DObject(GL_TRIANGLES, 3, boat_flag, COLOR_BLACK, GL_FILL);


 draw3DObject(this->rod);
}

    void Boat::draw(glm::mat4 VP) {
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(-1,  0, 0));
        rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
        Matrices.model *= (translate * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->base);
        draw3DObject(this->side);
        draw3DObject(this->rod);

        draw3DObject(this->corner);

        Matrices.model = glm::mat4(1.0f);
         translate = glm::translate (this->position_f);    // glTranslatef
         rotate    = glm::rotate((float) ((this->rotation_f) * M_PI / 180.0f), glm::vec3(-1,  0, 0));
        rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
        Matrices.model *= (translate * rotate);
         MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->flag);

    }

