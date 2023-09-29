/**
 * Author:  Karen Santiago
 * Created: 9-25-2023
 *
 **/

#include <GL/glx.h>
#include "fonts.h"

void display_gameover(int xres, int yres)
{
    Rect r;
    r.bot = yres/2;
    r.left = xres/2;
    r.center = 0;
    ggprint8b(&r, 0, 0x00000000, "Game Over");
}

void display_credits(int xres, int yres)
{
    Rect r;
    r.bot = (yres/2) - 20;
    r.left = (xres/2) - 20;
    r.center = 0;
    ggprint8b(&r, 0, 0x00000000, "Credits:");
    r.bot -= 20;
    ggprint8b(&r, 0, 0x00000000, "Alia Al-Maitah");
    r.bot -= 20;
    ggprint8b(&r, 0, 0x00000000, "Jayden Canales");
    r.bot -= 20;
    ggprint8b(&r, 0, 0x00000000, "Bryan Estrada");
    r.bot -= 20;
    ggprint8b(&r, 0, 0x00000000, "Karen Santiago");
}
