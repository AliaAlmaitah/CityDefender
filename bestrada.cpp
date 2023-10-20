//Name: Bryan Estrada
//Date: 09/25/23
//Purpose:File for CityDefender
//
#include <GL/glx.h>
#include "bestrada.h"

//function to lock robot in the middle
void Test_Robot(double *xpos, double *ypos) {
    *xpos = 300;
    *ypos = 300;
}
void moveRight(double *xpos, int xres) {
    //code for spire to move right
    if(*xpos < xres) {
        *xpos += 5;
    }
}
void moveLeft(double *xpos) {
    if(*xpos > 0) {
        *xpos -= 5;
    }
}
