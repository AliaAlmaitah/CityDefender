//Name: Bryan Estrada
//Date: 09/25/23
//Purpose:File for CityDefender
//
#include <GL/glx.h>
#include "bestrada.h"
#include "fonts.h"
#include <time.h>
#include <cmath>
#include <unistd.h>

//function to lock robot in the middle
void Test_Robot(double *xpos, double *ypos)
{
    *xpos = 300;
    *ypos = 80;
}
void moveRight(double *xpos, int xres)
{
    //code for spire to move right
    if (*xpos < xres) {
        *xpos += 6;
    }
}
void moveLeft(double *xpos)
{
    if (*xpos > 0) {
        *xpos -= 6;
    }
}
void Controls(int xres, int yres)
{
    int x = xres;
    int y = yres;
    //Black Box
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2i(0+(x/4), 0+(y/4));
        glVertex2i(0+(x/4), y-(y/4));
        glVertex2i(x-(x/4), y-(y/4));
        glVertex2i(x-(x/4), 0+(y/4));
    glEnd();
    //Text
    Rect r;
    r.bot = (y -y/4)-70;
    r.left = (x/2)-75;
    r.center = 0;
    ggprint40(&r, 0, 0x00ffffff, "Controls");
    r.bot -= 40;
    r.left -= 25;
    ggprint12(&r, 0, 0x00ffffff, "A/D - move left/right");
    r.bot -= 40;
    ggprint12(&r, 0, 0x00ffffff, "SPACE - shoot your laser");
    r.bot -= 60;
    r.left += 30;
    ggprint10(&r, 0, 0x00ffffff, "GOOD LUCK DEFENDER");
}
//------FORMATION---------
//      FORM1               FORM2           FORM3
//
//                           x x             x x
//   x x x x x x           x x x x         x x x x
//   x x x x x x           x x x x       x x x x x x
//                           x x 
//
float xformation(int form, int count)
{
    static float lst_xpos;
    int xpos;
    switch(form) {
        case 1:
            if (count == 1 || count == 7) {
             xpos = 120;
             lst_xpos = xpos;   
            } else {
                xpos = lst_xpos + 80;
                lst_xpos = xpos;
            }
            break;
        case 2:
            if (count == 1 || count == 11) {
                xpos = 295;
                lst_xpos = xpos;
            } else if (count == 3 || count == 7) {
                xpos = 225;
                lst_xpos = xpos;
            } else {
                xpos = lst_xpos+70;
                lst_xpos = xpos;
            }
            break;
        case 3:
            if (count == 1) {
                xpos = 295;
                lst_xpos = xpos;
            } else if (count == 3) {
                xpos = 225;
                lst_xpos = xpos;
            } else if (count == 7) {
                xpos = 155;
                lst_xpos = xpos;
            } else {
                xpos = lst_xpos + 70;
                lst_xpos = xpos;
            }
            break;
    }
    return xpos;
}
float yformation(int form, int count)
{
    static float lst_ypos;
    int ypos;
    switch(form) {
        case 1:
            if (count == 1) { //row one
                ypos = 400;
                lst_ypos = ypos;
            } else if (count == 7) { //row two
                ypos = 375; 
                lst_ypos = ypos;
            } else { //for drones on that row
                ypos = lst_ypos;
            }
            break;
        case 2:
            if (count == 1) { //row one
                ypos = 420;
                lst_ypos = ypos;
            } else if (count == 3) { //row two
                ypos = 380;
                lst_ypos = ypos;
            } else if (count == 7) { //row three
                ypos = 340;
                lst_ypos = ypos;
            } else if (count == 11) { //row four
                ypos = 300;
                lst_ypos = ypos;
            } else { // for the rest of the drones
                ypos = lst_ypos;
            }
            break;
        case 3:
            if (count == 1) {
                ypos = 420;
                lst_ypos = ypos;
            } else if (count == 3) {
                ypos = 380;
                lst_ypos = ypos;
            } else if (count == 7) {
                ypos = 340;
                lst_ypos = ypos;
            } else {
                ypos = lst_ypos;
            }
            break;
    }
    return ypos;
}

//---------------------------------------------------
//STATISTICS
int total_running_time(const bool get) 
{
    static int firsttime = 1;
    static int start_time;
    if (firsttime) {
        start_time = time(NULL);
        firsttime = 0;
    }
    if (get) {
        return time(NULL) - start_time;
    }
    return 0;
}
double total_mouse_distance(double x, double y, const bool get)
{
    static double distance = 0;
    static double savex;
    static double savey;
    static int firsttime = 0;
    double tempx;
    double tempy;
    if (firsttime) {
        savex = x;
        savey = y;
        firsttime = 0;
    } else if (x != 0 && y != 0) {
        tempx = x;
        tempy = y;
        tempx = tempx - savex;
        tempx = pow(tempx, 2);
        tempy = tempy - savey;
        tempy = pow(tempy, 2);
        tempx = tempx + tempy;
        tempx = sqrt(tempx);
        distance = tempx;
    }
    if (get) {
        return distance;
    }
    return 0;
}
