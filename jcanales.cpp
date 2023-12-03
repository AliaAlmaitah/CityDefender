/*
 *   Filename: jcanales.cpp
 *   Purpose: Software Engineering Project source file.
 *   Author: Jayden Canales
 *   Created: September 25, 2023
 *   Last Modified:
*/
#include "fonts.h"
#include <GL/glx.h>
#include <ctime>
#include <vector>

//NOTE TO SELF THINGS I CAN ADD
//background pic to start screen
//drone damage
//cooler looking fireballs
//powerups

typedef double Vec[3];

class Bullet {
public:
    Vec pos;
    Vec vel;
    float color[3];
    struct timespec time;
public:
    Bullet() {}
};

class Drone {
public:
    Vec pos;
    Vec vel;
    bool alive=1;
    int health=4;
};

class Fireball {
public:
    Vec pos;
    Vec vel;
    struct timespec timef;
public:
    Fireball() {}
};

void display_border(int xres, int yres)
{
	//draw a border around the window to indicate your test mode
	int b = 50;
	glColor3f(0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2i(0,	0);
		glVertex2i(0+b,   0+b);
		glVertex2i(0,   0+yres);
		glVertex2i(0+b,   0+yres-b);
		glVertex2i(xres,   0+yres);
		glVertex2i(xres-b,   0+yres-b);
		glVertex2i(xres,   0);
		glVertex2i(xres-b,   b);
		glVertex2i(0,   0);
		glVertex2i(0+b,   0+b);
    glEnd();
    glPopMatrix();
}
void display_hp(float health, int xres, int yres)
{
    const float sep = 2.0;
    const float barWidth = 5.0;
    if (health > 50.0) {
        glColor3f(0.0f, 1.0f, 0.0f);
    } else {
        glColor3f(1.0f, 0.0f, 0.0f);
    }
    glPushMatrix();
    glBegin(GL_QUADS);
        for (float i = xres-125; i < health + xres-125; i += (sep + barWidth)) {
            glVertex2f(i, yres-40);
            glVertex2f(i, yres-20);
            glVertex2f(i + barWidth, yres-20);
            glVertex2f(i + barWidth, yres-40);
        }
    glEnd();
    glPopMatrix();
    //HP words
    Rect r;
    r.bot = yres-60;
    r.left = xres-125;
    r.center = 0;
    if (health > 50.0) {
        ggprint08(&r, 0, 0x00ff00, "HP");
    } else {
        ggprint08(&r, 0, 0x00ff2400, "HP");
    }
}
int time_since_mouse_moved(const bool get, bool moved)
{
    static int start_time;
    //int time_passed = time(NULL) - start_time;
    if (moved) {
        start_time = time(NULL);
        moved = 0;
    }
    if (get) {
       // return time_passed;
       return time(NULL) - start_time;
    }
    return 0;
}
void render_drones(GLuint silhouette, float xpos, float ypos, float vel)
{
    //commented out parts indicate functionality before having to move some
    //to the main file for other people to use

    float droneWid = 30.0;
    float droneHei = 15.0;
    //Drone drones[11];
    //loat fxres = xres;
    //int d = 0;
    //for (float i=50.0; i<= fxres-50.0; i+=50.0)
        //MakeVector(i, 400.0, 0.0, drones[d].pos);
        //MakeVector(0.0, 0.0, 0.0, drones[d].vel);
        //drones[d].pos[0] = xpos;
        //drones[d].pos[1] = ypos;
        //drones[d].pos[2] = 0.0;
        //drones[d].vel[0] = 0.0;
        //drones[d].vel[1] = 0.0;
        //drones[d].vel[2] = 0.0;
        glPushMatrix();
            //glTranslatef(xpos, ypos, drones[d].pos[2]);
            glTranslatef(xpos, ypos, 0);
            glBindTexture(GL_TEXTURE_2D, silhouette);
            glEnable(GL_ALPHA_TEST);
            glAlphaFunc(GL_GREATER, 0.0f);
            glColor4ub(255,255,255,255);
        glBegin(GL_QUADS);
        //if (alive) {
            if (vel > 0.0) {
                glTexCoord2f(0.0f, 1.0f); glVertex2i(-droneWid,-droneHei);
                glTexCoord2f(0.0f, 0.0f); glVertex2i(-droneWid, droneHei);
                glTexCoord2f(1.0f, 0.0f); glVertex2i( droneWid, droneHei);
                glTexCoord2f(1.0f, 1.0f); glVertex2i( droneWid,-droneHei);
            } else {
                glTexCoord2f(1.0f, 1.0f); glVertex2i(-droneWid,-droneHei);
                glTexCoord2f(1.0f, 0.0f); glVertex2i(-droneWid, droneHei);
                glTexCoord2f(0.0f, 0.0f); glVertex2i( droneWid, droneHei);
                glTexCoord2f(0.0f, 1.0f); glVertex2i( droneWid,-droneHei);
            }
        //}
        glEnd();
        glPopMatrix();
        //d++;
}
void drone_damage(Drone* drs, Bullet* barr)
{
    int max_dr = 12;
    int max_bul = 11;
    for (int dr=0; dr<max_dr; dr++) {
        for (int bul=0; bul<max_bul; bul++) {
            if ((barr[bul].pos[0] > drs[dr].pos[0]-15.0)&&
                                (barr[bul].pos[0] < drs[dr].pos[0]+15.0)) {
                if ((barr[bul].pos[1] > drs[dr].pos[1]-7.0)&&
                                (barr[bul].pos[1] < drs[dr].pos[1]+7.0)) {
                    //damage to drone and update alive if needed
                    drs[dr].health -= 1;
                    if (drs[dr].health == 0) {
                        drs[dr].alive = 0;
                    }
                } 
            }
        }
    }
}
void robot_damage(double rbtxpos, double rbtypos, Fireball* fbs, float *health)
{
    double lowerx = rbtxpos - 25.0;
    double upperx = rbtxpos + 25.0;
    double lowery = rbtypos - 5.0;
    double uppery = rbtypos + 5.0;
    int max_fb = 11;
    for (int fb=0; fb<max_fb; fb++) {
        if (*health != 0) {
            if (((fbs[fb].pos[0] > lowerx)&&(fbs[fb].pos[0] < upperx))
                    && ((fbs[fb].pos[1] < uppery)&&(fbs[fb].pos[1] > lowery))) {
            *health -= 5.0;
            }
        }
    }
}
