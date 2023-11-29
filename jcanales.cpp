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

typedef double Vec[3];

class Drone {
public:
    Vec pos;
    Vec vel;
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
void render_drones(GLuint silhouette, int xres)
{
    float droneWid = 30.0;
    float droneHei = 15.0;
    Drone drones[11];
    float fxres = xres;
    int d = 0;
    for (float i=50.0; i<= fxres-50.0; i+=50.0) {
        //MakeVector(i, 400.0, 0.0, drones[d].pos);
        //MakeVector(0.0, 0.0, 0.0, drones[d].vel);
        drones[d].pos[0] = i;
        drones[d].pos[1] = 400.0;
        drones[d].pos[2] = 0.0;
        drones[d].vel[0] = 0.0;
        drones[d].vel[1] = 0.0;
        drones[d].vel[2] = 0.0;
        glPushMatrix();
            glTranslatef(drones[d].pos[0], drones[d].pos[1], drones[d].pos[2]);
            glBindTexture(GL_TEXTURE_2D, silhouette);
            glEnable(GL_ALPHA_TEST);
            glAlphaFunc(GL_GREATER, 0.0f);
            glColor4ub(255,255,255,255);
        glBegin(GL_QUADS);
            if (drones[d].vel[0] > 0.0) {
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
        glEnd();
        glPopMatrix();
        d++;

    }
}
