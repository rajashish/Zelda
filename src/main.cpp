#include "main.h"
#include "timer.h"
#include "rocks.h"
#include "boat.h"
#include "water.h"
#include "canon.h"
#include "monster.h"
#include "fireball.h"
#include "health.h"
#include "boss.h"
#include "man.h"

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
int i;
Rocks rock[400];
Health health[80];
Health score_bonus[80];
Health booster[50];
Monster mon[80];
Canon canon;

Water water;
Boat boat;
Boss boss[50];
int boss_life[50];
Man man;
Rocks bonus;


Fireball fball;
int view = 0;
int boost_counter=0;
float a, b;
float fire_speed = 0;
float pos_y, pos_z;
float jump_speed = 2;
int life = 10;
float windspeed = 0;
int wind_timer = 300;
float wind_angle = 0;
float fire_angle, fire_y, fire_z;
float eye_x, eye_y, eye_z;
float target_x, target_y, target_z;
float monster_move;
int view_counter = 0, view_timer = 0;
int score;
int tic = 0, kill = 0;
double x_pos, y_pos;
float bossy,bossz;



float randi(float LO, float HI) {
    return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0, y_offset = 0, camera_distance = 5;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    //  glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    //follow
    // glm::vec3 eye(-2.6, -0.5, -0.3);
    //  glm::vec3 eye(-5.0f, -1, -1);
    glm::vec3 eye(eye_x, eye_y, eye_z);



    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    //glm::vec3 target(0, boat.position.y, boat.position.z );
    glm::vec3 target(target_x, target_y, target_z);

    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up(1, 0, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt(eye, target, up); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProjthis->rotation = 0;ect matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render


    water.draw(VP);
    boat.draw(VP);
    bonus.draw(VP);
    if(man.position.x <0.1)
        man.draw(VP);
    canon.draw(VP);
    if (fball.position.x < 0.1)
        fball.draw(VP);


    for (i = 0; i < 400; i++)
        rock[i].draw(VP);
    for (i = 0; i < 80; i++) {
        health[i].draw(VP);
        mon[i].draw(VP);
        score_bonus[i].draw(VP);
    }

    for (i = 0; i < 50; i++) {
        if (boss[i].position.x < 1 && boss_life[i] > 0) {
            boss[i].draw(VP);
        }
    }
    for(i=0;i<50;i++)
        booster[i].draw(VP);
}


void dispScore(){
//    cout << ball2.score << endl;
    string e = "Score : ";
    std::string s = std::to_string(score);
    s = e+s;
    string l = "                   Life : ";
    std::string f = std::to_string(life);
    s=s+l+f;
    glfwSetWindowTitle(window, const_cast<char*>(s.c_str()));
}


void view_toggle() {
    if (view_counter == 0)//follow
    {
        eye_x = -3.6;
        eye_y = boat.position.y - 4;
        eye_z = boat.position.z;

        target_x = 0;
        target_y = boat.position.y;
        target_z = boat.position.z;
    }


    if (view_counter == 1)//boat
    {
        eye_x = -1.2;
        eye_y = boat.position.y + 0.55 * cos(boat.rotation * M_PI / 180.0f);
        eye_z = boat.position.z - 0.55 * sin(boat.rotation * M_PI / 180.0f);

        target_x = 0;
        target_y = boat.position.y + 5.85 * cos(boat.rotation * M_PI / 180.0f);
        target_z = boat.position.z - 5.85 * sin(boat.rotation * M_PI / 180.0f);
    }


    if (view_counter == 2)//sky
    {
        eye_x = -25;
        eye_y = boat.position.y - 0.1;
        eye_z = boat.position.z;

        target_x = 0;
        target_y = boat.position.y;
        target_z = boat.position.z;
    }

    if (view_counter == 3)//tower
    {
        eye_x = -8.6;
        eye_y = -2.5;
        eye_z = -1.3;

        target_x = 0.1;
        target_y = boat.position.y;
        target_z = boat.position.z;
    }


    if (view_counter == 4)//helicopter
    {
        eye_y = boat.position.y-camera_distance*cos(camera_rotation_angle*M_PI/180.0f);

        eye_x = -3.6 - y_offset;

        eye_z = boat.position.z+camera_distance*sin(camera_rotation_angle*M_PI/180.0f);

        target_x = boat.position.x;
        target_y = boat.position.y;
        target_z = boat.position.z;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if(yoffset > 0) camera_distance -= 0.1;
    else camera_distance += 0.1;
}

void tick_input(GLFWwindow *window) {
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int view = glfwGetKey(window, GLFW_KEY_V);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);
    int c_left = glfwGetKey(window, GLFW_KEY_A);
    int c_right = glfwGetKey(window, GLFW_KEY_D);
    int fire = glfwGetKey(window, GLFW_KEY_F);
    double cxpos, cypos;
    glfwGetCursorPos(window, &cxpos, &cypos);
    if(abs(cxpos - x_pos) > 1){
        if(cxpos > x_pos) ++camera_rotation_angle;
        else --camera_rotation_angle;
        x_pos = cxpos;

    }
    if(abs(cypos - y_pos) > 1){
        if(cypos > y_pos) ++y_offset;
        else --y_offset;
        y_pos = cypos;
    }
    if (left) {
        boat.rotation += 1;
        canon.rotation += 1;
        man.rotation+=1;

    }
    if (right) {
        boat.rotation -= 1;
        canon.rotation -= 1;
        man.rotation -=1;
    }

    if (up) {

        boat.position.y += ((0.32+boost_counter*0.08)) * cos(boat.rotation * M_PI / 180.0f);
        boat.position.z -= ((0.32+boost_counter*0.08)) * sin(boat.rotation * M_PI / 180.0f);

    }

    if (down) {
        boat.position.y -= (0.32+boost_counter*0.08) * cos(boat.rotation * M_PI / 180.0f);
        boat.position.z += (0.32+boost_counter*0.08) * sin(boat.rotation * M_PI / 180.0f);
    }

    if (jump && jump_speed >= 0.048f) {
        jump_speed = -0.048;
    }

    if (c_left) {

        canon.rotation += 1;

    }
    if (c_right) {

        canon.rotation -= 1;
    }

    if (fire && fball.position.x >= 0.08) {
        fball.position.x = -1;
        fball.position.y = boat.position.y + 0.6 * cos(canon.rotation * M_PI / 180.0f);
        fball.position.z = boat.position.z - 0.6 * sin(canon.rotation * M_PI / 180.0f);
        fire_speed = -0.2;
        fire_angle = canon.rotation;
        fire_y = (windspeed) * cos(boat.rotation * M_PI / 180.0f);
        fire_z = (windspeed) * sin(boat.rotation * M_PI / 180.0f);
        if (up) {
            fire_y = ((0.32+boost_counter*0.08) + windspeed) * cos(boat.rotation * M_PI / 180.0f);
            fire_z = ((0.32+boost_counter*0.08) + windspeed) * sin(boat.rotation * M_PI / 180.0f);

        }
    }

    if (view && view_timer == 0) {
        view_timer = 60;
        view_counter = (view_counter + 1) % 5;

    }
}

void tick_elements() {
    // boat.tick();
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models


    water = Water(0, 0, COLOR_SEA);
    boat = Boat(0, 0, 0);
    man = Man( 5, 0 , 0);
    canon = Canon(0, 0, 0);
    fball = Fireball(10, 1, 1, COLOR_FIRE1, COLOR_FIRE2);
    bonus= Rocks(-0.8 , 550 , 0 , COLOR_FIRE2 , COLOR_GREEN);
    for (i = 0; i < 50; i++) {
        boss[i] = Boss(10, -10, -10, COLOR_RED);
    }

    for (i = 0; i < 400; i++) {
        a =  randi(-300, 300);
        b =  randi(-300, 300);

        pos_y = boat.position.y + a;
        pos_z = boat.position.z + b;

        rock[i] = Rocks(-0.5f, pos_y, pos_z, COLOR_ROCK1, COLOR_ROCK2);

    }


    for (i = 0; i < 80; i++) {
        a = (float) randi(-300, 300);
        b = (float) randi(-300, 300);

        pos_y = a;
        pos_z = b;


        health[i] = Health(-1.5f, pos_y, pos_z, COLOR_HEALTH1, COLOR_HEALTH2);
    }

        for (i = 0; i < 50; i++) {


            booster[i] = Health(15.0f, 5, 7, COLOR_BLACK, COLOR_FIRE1);
        }


    for (i = 0; i < 80; i++) {
        a = (float) randi(-300, 300);
        b = (float) randi(-300, 300);

        pos_y = a;
        pos_z = b;


        score_bonus[i] = Health(-1.5f, pos_y, pos_z, COLOR_RED, COLOR_FIRE2);

    }

    for (i = 0; i < 80; i++) {
        a = (float) randi(-300, 300);
        b = (float) randi(-300, 300);

        pos_y = a;
        pos_z = b;


        mon[i] = Monster(-0.5f, pos_y, pos_z);

    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0,
                 0.0f); // R, G, B, A
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width = 1067;
    int height = 600;
    int i;
    float a, b;
    float rand;
    float pos_y, pos_z;
    wind_timer = 300;

    for(i=0;i<49;i++)
        boss_life[i]=3;


    window = initGLFW(width, height);

    initGL(window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {

                dispScore();

            tic = (tic + 1) % 60;



            //wind

            if (wind_timer >= 300) {
                wind_angle = randi(1, 360);
                rand = randi(0, 0.1);
            }
            wind_timer--;
            if (wind_timer <= 0)
                wind_timer = 300;

           windspeed = rand*cos((wind_angle-boat.rotation)*M_PI/180.0f);

            boat.position.y += windspeed * cos(boat.rotation * M_PI / 180.0f);
            boat.position.z -= windspeed * sin(boat.rotation * M_PI / 180.0f);
            boat.rotation_f = wind_angle;
            boat.position_f.x = boat.position.x;
            boat.position_f.y = boat.position.y;
            boat.position_f.z = boat.position.z;



//rock regenerate
            for (i = 0; i < 400; i++) {

                if (fabs(rock[i].position.y - boat.position.y) > 301 ||
                    fabs(rock[i].position.z - boat.position.z) > 301 ||
                    (fabs(rock[i].position.y - boat.position.y) > 220 &&
                     fabs(rock[i].position.z - boat.position.z) > 220)) {
                    a = (float) randi(-300, 300);
                    b = (float) randi(-300, 300);

                    pos_y = boat.position.y + a;
                    pos_z = boat.position.z + b;

                    rock[i] = Rocks(-0.5f, pos_y, pos_z, COLOR_ROCK1, COLOR_ROCK2);

                }

            }
//health regenerate
            for (i = 0; i < 80; i++) {
                health[i].rotation += 1;
                if (fabs(health[i].position.y - boat.position.y) > 301 ||
                    fabs(health[i].position.z - boat.position.z) > 301 ||
                    (fabs(health[i].position.y - boat.position.y) > 220 &&
                     fabs(health[i].position.z - boat.position.z) > 220)) {
                    a = (float) randi(-300, 300);
                    b = (float) randi(-300, 300);

                    pos_y = boat.position.y + a;
                    pos_z = boat.position.z + b;


                    health[i] = Health(-1.5f, pos_y, pos_z, COLOR_HEALTH1, COLOR_HEALTH2);

                }

            }

            //score_bonus regenerate
            for (i = 0; i < 80; i++) {
                score_bonus[i].rotation += 1;
                if (fabs(score_bonus[i].position.y - boat.position.y) > 301 ||
                    fabs(score_bonus[i].position.z - boat.position.z) > 301 ||
                    (fabs(score_bonus[i].position.y - boat.position.y) > 220 &&
                     fabs(score_bonus[i].position.z - boat.position.z) > 220)) {
                    a = (float) randi(-300, 300);
                    b = (float) randi(-300, 300);

                    pos_y = boat.position.y + a;
                    pos_z = boat.position.z + b;


                    score_bonus[i] = Health(-1.5f, pos_y, pos_z, COLOR_RED, COLOR_FIRE2);

                }

            }

            //monster regenerate
            for (i = 0; i < 80; i++) {
                mon[i].rotation += 1;
                if(tic==0)
                monster_move = randi(1,359);
                mon[i].position.y += (float) 0.1*cos(monster_move * M_PI / 180.0f)/2.0f;
                mon[i].position.z += (float) 0.1*sin(monster_move * M_PI / 180.0f)/2.0f;


                if (fabs(mon[i].position.y - boat.position.y) > 301 ||
                    fabs(mon[i].position.z - boat.position.z) > 301 ||
                    (fabs(mon[i].position.y - boat.position.y) > 220 &&
                     fabs(mon[i].position.z - boat.position.z) > 220)) {
                    a = (float) randi(-300, 300);
                    b = (float) randi(-300, 300);

                    pos_y = boat.position.y + a;
                    pos_z = boat.position.z + b;


                    mon[i] = Monster(-0.5f, pos_y, pos_z);

                }

            }



            //collision boss-boat
            for (i = 0; i < 50; i++) {
                if (boss[i].position.x < 0.1 )
                    if (fabs(boat.position.y - boss[i].position.y) < 2.8 &&
                        fabs(boat.position.z - boss[i].position.z) < 2.6)
                    {
                        printf("GAME OVER\n");
                        printf("YOUR SCORE IS %d", score);


                        exit(0);

                    }
            }

            //collision boss-fireball
            for (i = 0; i < 50; i++) {


                if (boss[i].position.x < 0.1) {
                    boss[i].rotation += 1;
               if (tic == 0)
                        monster_move = randi(1, 359);
                    boss[i].position.y += (float) 0.06 * cos(monster_move * M_PI / 180.0f) / 2.0f;
                    boss[i].position.z += (float) 0.06 * sin(monster_move * M_PI / 180.0f) / 2.0f;

//                    if(tic==0)
//                    {
//                        bossy=((boat.position.y-boss[i].position.y))/10;
//                        bossz=((boat.position.z-boss[i].position.z))/10;
//                    }
//                    boss[i].position.y+=bossy;
//                    boss[i].position.z+=bossz;


                }


                if (boss[i].position.x < 0.1 && fball.position.x < 0)
                {

                    if (fabs(fball.position.y - boss[i].position.y) < 2.3 &&
                        fabs(fball.position.z - boss[i].position.z) < 2.3) {
                        boss_life[i] = boss_life[i]- 1;


                        if (boss_life[i] == 0) {
                            score =score+ 1000;
                            boss[i].position.x = 10;
                            boss_life[i] = 3;
                            for (int j = 0; j < 50; j++) {
                                if (booster[j].position.x >= 0.1) {
                                    booster[j] = Health(-1.8, boss[i].position.y, boss[i].position.z, COLOR_BLACK,COLOR_FIRE1);
                                    boss_life[j] == 3;
                                    break;
                                }

                            }

                        }
                        else if (boss_life[i] == 2){
                            score += 100;
                            boss[i] = Boss(0,boss[i].position.y,boss[i].position.z,COLOR_FIRE2);
                        }

                        else if (boss_life[i] == 1) {
                            score += 100;
                            boss[i] = Boss(0,boss[i].position.y,boss[i].position.z,COLOR_FIRE1);

                        }

                        fball.position.x = 10;

                    }
                }
            }


            //collision rock
            for (i = 0; i < 400; i++) {
                if (fabs(boat.position.y - rock[i].position.y) < 1.2 &&
                    fabs(boat.position.z - rock[i].position.z) < 0.75 &&fabs(boat.position.x - rock[i].position.x)<1.2) {
                    a = (float) randi(-300, 300);
                    b = (float) randi(-300, 300);

                    pos_y = boat.position.y + a;
                    pos_z = boat.position.z + b;

                    rock[i] = Rocks(-0.5f, pos_y, pos_z, COLOR_ROCK1, COLOR_ROCK2);


                    life--;


                }
            }

            //collision bonus
                    bonus.rotation+=1;
            if(bonus.position.x<0) {
                if (fabs(boat.position.y - bonus.position.y) < 1.2 &&
                    fabs(boat.position.z - bonus.position.z) < 0.75) {

                    score += 5000;
                    life += 10;
                    bonus.position.x = 5;

                }
            }


            //collision health
            if (boat.position.x < 0)
                for (i = 0; i < 80; i++) {

                    if (fabs(boat.position.y - health[i].position.y) < 1.2 &&
                        fabs(boat.position.z - health[i].position.z) < 0.75) {
                        a = (float) randi(-300, 300);
                        b = (float) randi(-300, 300);

                        pos_y = boat.position.y + a;
                        pos_z = boat.position.z + b;


                        health[i] = Health(-1.5f, pos_y, pos_z, COLOR_HEALTH1, COLOR_HEALTH2);


                        life++;


                    }
                }


            //collision Booster boat
            if (boat.position.x < 0)
                for (i = 0; i < 50; i++) {

                    if (fabs(boat.position.y - booster[i].position.y) < 1.2 &&
                        fabs(boat.position.z - booster[i].position.z) < 0.75) {
                        boost_counter++;
                        booster->position.x=15;

                    }
                }
//collision score_bonus
            if (boat.position.x < 0)
                for (i = 0; i < 80; i++) {

                    if (fabs(boat.position.y - score_bonus[i].position.y) < 1.2 &&
                        fabs(boat.position.z - score_bonus[i].position.z) < 0.75) {
                        a = (float) randi(-300, 300);
                        b = (float) randi(-300, 300);

                        pos_y = boat.position.y + a;
                        pos_z = boat.position.z + b;


                        score_bonus[i] = Health(-1.5f, pos_y, pos_z, COLOR_RED, COLOR_FIRE2);


                        score+=100;


                    }
                }


            //collision monster boat
            for (i = 0; i < 80; i++) {

                if (fabs(boat.position.y - mon[i].position.y) < 1.6 &&
                    fabs(boat.position.z - mon[i].position.z) < 1.2) {
                    a = (float) randi(-300, 300);
                    b = (float) randi(-300, 300);

                    pos_y = boat.position.y + a;
                    pos_z = boat.position.z + b;


                    mon[i] = Monster(-0.5f, pos_y, pos_z);


                    life = life - 2.5;


                }
            }

            //fireball monster collision
            if (fball.position.x < 0) {
                for (i = 0; i < 80; i++) {

                    if (fabs(fball.position.y - mon[i].position.y) < 0.9 &&
                        fabs(fball.position.z - mon[i].position.z) < 0.9)
                    {
                        kill++;
                        if (kill % 5 == 0) {
                            for (int j = 0; j < 50; j++) {
                                if (boss[j].position.x >= 0.1) {
                                    boss[j] = Boss(0, mon[i].position.y, mon[i].position.z, COLOR_RED);
                                    boss_life[j] == 3;
                                    break;
                                }

                            }
                        }


                        a = (float) randi(-300, 300);
                        b = (float) randi(-300, 300);

                        pos_y = boat.position.y + a;
                        pos_z = boat.position.z + b;


                        mon[i] = Monster(-1.0f, pos_y, pos_z);


                        score = score + 50;
                        fball.position.x = 10;

                    }
                }
            }

            //fireball rock collision

            if (fball.position.x < 0)
                for (i = 0; i < 400; i++) {

                    if (fabs(fball.position.y - rock[i].position.y) < 1.5 &&
                        fabs(fball.position.z - rock[i].position.z) < 1.5 &&
                        fabs(fball.position.x - rock[i].position.x) < 2.8) {
                        a = (float) randi(-300, 300);
                        b = (float) randi(-300, 300);

                        pos_y = boat.position.y + a;
                        pos_z = boat.position.z + b;


                        rock[i] = Rocks(-0.5f, pos_y, pos_z, COLOR_ROCK1, COLOR_ROCK2);


                        score = score + 5;


                    }
                }



            //JUMP EXECUTE
            if (jump_speed < 0.048f) {
                boat.position.x = boat.position.x + jump_speed;
                canon.position.x = canon.position.x + jump_speed;

                jump_speed += 0.0016;
            }

            if (jump_speed >= 0.048f) {
                boat.position.x = 0;
                canon.position.x = 0;
            }

            //canon positioning

            canon.position.y = boat.position.y;
            canon.position.z = boat.position.z;




            // fireball execution
            if (fball.position.x < 0.1) {
                fball.position.x = fball.position.x + fire_speed;
                fball.position.y = fball.position.y + (0.048 * 5 * cos(fire_angle * M_PI / 180.0f)) + fire_y;
                fball.position.z = fball.position.z - (0.048 * 5 * sin(fire_angle * M_PI / 180.0f)) - fire_z;
                fire_speed += 0.01;

            }

            //view timer
            if (view_timer > 0)
                view_timer--;
            // view

            view_toggle();


            //man island
            man.position.y = boat.position.y;
            man.position.z = boat.position.z ;

            if(boat.position.y >500 && boat.position.y <600 && boat.position.z > -100 && boat.position.z<100)
            {   if(boat.position.x<=0) {
                    boat.position.x = 5;
                    boat.position_f.x=5;
                    man.position.x =-0.3;
                }
            }

            else{
                if(boat.position.x>0) {
                    boat.position.x = 0;
                    boat.position_f.x =0;
                    man.position.x = 5;
                }
            }
            if(!(boat.position.y >500 && boat.position.y <600 && boat.position.z > -100 && boat.position.z<100))
                man.position.x = 5;
            // 60 fps
            // OpenGL Draw commands
            draw();
            if (life <= 0) {
                printf("GAME OVER\n");
                printf("YOUR SCORE IS %d", score);


                exit(0);

            }

            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse eventscos(camera_rotation_angle*M_PI/180.0f)
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
//    float top    = screen_center_y + 4 / screen_zoom;
//    float bottom = screen_center_y - 4 / screen_zoom;
//    float left   = screen_center_x - 4 / screen_zoom;
//    float right  = screen_center_x + 4 / screen_zoom;
    float near = 0.01f;
    float far = 800.0f;

//    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 800.0f);
    Matrices.projection = glm::perspective(-1.57f, 1.77f, near, far);
}
