//Name: Bryan Estrada
//Date: 09/25/23
//Purpose:File for CityDefender
//
#include <GL/glx.h>
#include "bestrada.h"
#include <time.h>
#include <cmath>

//function to lock robot in the middle
void Test_Robot(double *xpos, double *ypos)
{
    *xpos = 300;
    *ypos = 300;
}
void moveRight(double *xpos, int xres)
{
    //code for spire to move right
    if(*xpos < xres) {
        *xpos += 5;
    }
}
void moveLeft(double *xpos)
{
    if(*xpos > 0) {
        *xpos -= 5;
    }
}
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
    } else if( x != 0 && y != 0) {
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
