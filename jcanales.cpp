/*
 *   Filename: jcanales.cpp
 *   Purpose: Software Engineering Project source file.
 *   Author: Jayden Canales
 *   Created: September 25, 2023
 *   Last Modified:
*/
#include "fonts.h"
#include <GL/glx.h>

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

