/*
 *   Filename: jcanales.cpp
 *   Purpose: Software Engineering Project source file.
 *   Author: Jayden Canales
 *   Created: September 25, 2023
 *   Last Modified: December 4, 2023
*/
#include "fonts.h"
#include <GL/glx.h>
#include <ctime>
#include <vector>
#include <cstdlib>

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
    int health=3;
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
	glColor3f(1.0f, 0.0f, 0.0f);
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
    if (health >= 60.0) {
        glColor3f(0.0f, 1.0f, 0.0f);
    } else if ((health >= 30.0) && (health < 60.0)) {
        glColor3f(1.0f, 0.5f, 0.0f);
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
    if (health >= 60.0) {
        ggprint08(&r, 0, 0x00ff00, "HP");
    } else if ((health >= 30.0) && (health < 60.0)) {
        ggprint08(&r, 0, 0xffffa500, "HP");
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
bool check_drone_under(Drone* drs, double drxpos, double drypos, int max_drs)
{
    //if there are no drones under this drone (xpos are same ypos is lower)
    //drone under also has to be alive
    //return 1 if there is under
    //int max_drs = 12;
    for (int i=0; i<max_drs; i++) {
        if ((drs[i].pos[0] == drxpos) && (drs[i].pos[1] < drypos)) {
            if (drs[i].alive) {
                return 1;
            }
        }
    }
    return 0;
}
void drone_damage(Drone* drs, Bullet* barr, int max_drs, int max_buls)
{
    //int max_dr = 12;
    //int max_bul = 11;
    for (int dr=0; dr<max_drs; dr++) {
        for (int bul=0; bul<max_buls; bul++) {
            if ((barr[bul].pos[0] > drs[dr].pos[0]-15.0)&&
                                (barr[bul].pos[0] < drs[dr].pos[0]+15.0)) {
                if ((barr[bul].pos[1] > drs[dr].pos[1]-7.0)&&
                                (barr[bul].pos[1] < drs[dr].pos[1]+7.0)) {
                    //damage to drone and update alive if needed
                    bool under = check_drone_under(drs, drs[dr].pos[0],
                                                      drs[dr].pos[1], max_drs);
                    if (!under) {
                        drs[dr].health -= 1;
                        if (drs[dr].health == 0) {
                            drs[dr].alive = 0;
                        }
                    }
                }
            }
        }
    }
}
void robot_damage(double rbtxpos, double rbtypos, Fireball* fbs, float *health, int max_fbs)
{
    double lowerx = rbtxpos - 25.0;
    double upperx = rbtxpos + 25.0;
    double lowery = rbtypos - 5.0;
    double uppery = rbtypos + 5.0;
    //int max_fb = 11;
    for (int fb=0; fb<max_fbs; fb++) {
        if (*health != 0) {
            if (((fbs[fb].pos[0] > lowerx)&&(fbs[fb].pos[0] < upperx))
                    && ((fbs[fb].pos[1] < uppery)&&(fbs[fb].pos[1] > lowery))) {
            *health -= 5.0;
            }
        }
    }
}
void game_instructions(int xres, int yres)
{
    Rect r;
    r.bot = (yres/3)+30;
    r.left = (xres/2) - 125;
    r.center = 0;
    ggprint10(&r, 0, 0x8fe2, "Save the city by destroying all the drones");
    r.bot -= 15;
    r.left = (xres/2) - 130;
    ggprint10(&r, 0, 0x8fe2,
                            "with your lazer in the shortest amount of time.");
    r.bot -= 15;
    r.left = (xres/2) - 135;
    ggprint10(&r, 0, 0x8fe2,
                            "Remember to dodge their fireballs to stay alive.");
    r.bot -= 15;
    r.left = (xres/2) - 140;
    ggprint10(&r, 0, 0x8fe2,
                            "Can you beat your high-score and save the city?");

    //top line
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(8.0);
    glBegin(GL_LINES);
    glVertex2i(0, (yres/3)*2);
    glVertex2i(xres, (yres/3)*2);
    glEnd();
    glLineWidth(1.0f);

    //bottom line
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(8.0);
    glBegin(GL_LINES);
        glVertex2i(0, (yres/4));
        glVertex2i(xres, (yres/4));
    glEnd();
    glLineWidth(1.0f);

    srand(777);
    for (float i = 0.0; i < xres; i+=40.0) {
        float height = rand() % 100 + 50;
        float width = 40.0;
        float ystart = (2.0/3.0)*yres;
        glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(i, ystart);
            glVertex2f(i + width, ystart);
            glVertex2f(i + width, ystart + height);
            glVertex2f(i, ystart + height);
        glEnd();
    }
}
