#include "water.h"
#include "main.h"

Water::Water(float x,float z,color_t color) {

    this->position = glm::vec3(x, 0, z);
    this->color = color;
    this->rotation = 0;


    GLfloat wat1[100000];
    GLfloat wat2[100000];
    int count1=0,count2=0,i,j;

    for(i=-500;i<=480;i+=20)
    {
        for(j=-500;j<=480;j+=20)
        {
            wat1[count1]=0;
            count1++;
            wat1[count1]=i;
            count1++;
            wat1[count1]=j;
            count1++;

            wat1[count1]=0;
            count1++;
            wat1[count1]=i+20;
            count1++;
            wat1[count1]=j;
            count1++;

            wat1[count1]=0;
            count1++;
            wat1[count1]=i;
            count1++;
            wat1[count1]=j+20;
            count1++;

            wat2[count2]=0;
            count2++;
            wat2[count2]=i+20;
            count2++;
            wat2[count2]=j;
            count2++;


            wat2[count2]=0;
            count2++;
            wat2[count2]=i+20;
            count2++;
            wat2[count2]=j+20;
            count2++;


            wat2[count2]=0;
            count2++;
            wat2[count2]=i;
            count2++;
            wat2[count2]=j+20;
            count2++;





        }
    }


    GLfloat wat3[] = {

            0 , 10000 , 500 ,
            0 , 10000 , 10000 ,
            0 , -10000 , 500 ,

            0 , 10000 , 10000 ,
            0 , -10000 , 500 ,
            0 , -10000 , 10000 ,


            0 , 10000 , -500 ,
            0 , 10000 , -10000 ,
            0 , -10000 , -500 ,

            0 , 10000 , -10000 ,
            0 , -10000 , -500 ,
            0 , -10000 , -10000 ,


            0 , 500 , -500 ,
            0 , 10000 , -500 ,
            0 , 500 , 500 ,

            0 , 10000 , -500 ,
            0 , 500 , 500 ,
            0 , 10000 , 500 ,

            0 , -500 , -500 ,
            0 , -10000 , -500 ,
            0 , -500 , 500 ,

            0 , -10000 , -500 ,
            0 , -500 , 500 ,
            0 , -10000 , 500 ,


    };

    this->object = create3DObject(GL_TRIANGLES, 7500, wat1, this->color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 24, wat3, this->color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 7500, wat2, COLOR_BLUE, GL_FILL);
   // this->object2 = create3DObject(GL_TRIANGLES, 7500, wat2, this->color, GL_FILL);
    //COLOR_BLUE




    GLfloat barrels[] = {
            0.4 , 600 , -100 ,
            -0.1 , 600 , 100 ,
            -0.1 ,  500 , -100 ,

            -0.1 ,  500 , 100 ,
            -0.1 , 600 , 100 ,
            -0.1 ,  500 , -100 ,

            -0.3 , 600 , -100 ,
            -0.3 , 600 , 100 ,
            -0.3 ,  500 , -100 ,

            -0.3 ,  500 , 100 ,
            -0.3 , 600 , 100 ,
            -0.3 ,  500 , -100 ,

            // rt
            -0.1 , 600 , 100 ,
            -0.1 ,  500 , 100 ,
            -0.3 , 600 , 100 ,

            -0.3 ,  500 , 100 ,
            -0.1 ,  500 , 100 ,
            -0.3 , 600 , 100 ,
            //brt
            -0.1 , 600 , -100 ,
            -0.1 ,  500 , -100 ,
            -0.3 , 600 , -100 ,

            -0.3 ,  500 , -100 ,
            -0.1 ,  500 , -100 ,
            -0.3 , 600 , -100 ,

            //frnt

            -0.1 , 600 , -100 ,
            -0.1 , 600 , 100 ,
            -0.3 , 600 , -100 ,

            -0.1 , 600 , 100 ,
            -0.3 , 600 , -100,
            -0.3 , 600 , 100 ,

            //bfrnt
            -0.1 ,  500 , -100 ,
            -0.1 ,  500 , 100 ,
            -0.3 ,  500 , -100 ,

            -0.1 ,  500 , 100 ,
            -0.3 ,  500 , -100,
            -0.3 ,  500 , 100 ,
    };
    this->object4 = create3DObject(GL_TRIANGLES, 36, barrels , COLOR_ISLAND, GL_FILL);


}







void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1 , 0 , 0));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object3);
    draw3DObject(this->object2);
    draw3DObject(this->object4);
}

void Water::set_position(float x, float z){
    this->position = glm::vec3(x, 0, z);}




