/**
 * Author:  Karen Santiago
 * Created: 9-25-2023
 *
 **/

#include <GL/glx.h>
#include "fonts.h"

int total_render_function_calls(const bool get) {
    static int count = 0;
    if (get == false) {
        count++;
    }
    if (get == true) {
        return count;
    }
    return 0;
}

void display_gameover(int xres, int yres)
{
    Rect r;
    r.bot = yres/2;
    r.left = xres/2 - 125;
    r.center = 0;
    ggprint40(&r, 0, 0x00ff2400, "Game Over");
}

void display_credits(int xres, int yres)
{
    Rect r;
    r.bot = (yres/2) - 20;
    r.left = (xres/2) - 50;
    r.center = 0;
    ggprint16(&r, 0, 0x00ffffff, "Credits:");
    r.bot -= 20;
    ggprint12(&r, 0, 0x00ffffff, "Alia Al-Maitah");
    r.bot -= 20;
    ggprint12(&r, 0, 0x00ffffff, "Jayden Canales");
    r.bot -= 20;
    ggprint12(&r, 0, 0x00ffffff, "Bryan Estrada");
    r.bot -= 20;
    ggprint12(&r, 0, 0x00ffffff, "Karen Santiago");
    r.bot -= 20;
}
