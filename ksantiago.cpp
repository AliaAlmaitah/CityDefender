/**
 * Author:  Karen Santiago
 * Created: 9-25-2023
 *
 **/

#include <GL/glx.h>
#include "fonts.h"

void startscreen(int xres, int yres) { //GLuint *cityTexture) {
    //glGenTextures(1, cityTexture);
    Rect r;
    r.bot = (yres/2);
    r.left = (xres/2) - 125;
    r.center = 0;
    ggprint40(&r, 0, 0x00ffffff, "City Defender");
    r.bot -= 20;
    r.left = (xres/2) - 50;
    ggprint12(&r, 0, 0x00ffffff, "Press 'X' to play.");
}

int start(int start_game, XEvent *e) {
    int key = (XLookupKeysym(&e->xkey, 0) & 0x0000ffff);
    if (key == XK_x) {
        start_game = 1;
        return start_game;
    }
    return start_game;
}

int total_physics_function_calls(const bool get) {
    static int physics = 0;
    if (get == false) {
        physics++;
    }
    if (get == true) {
        return physics;
    }
    return 0;
}

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
    ggprint13(&r, 0, 0x00ffffff, "Alia Al-Maitah");
    r.bot -= 20;
    ggprint13(&r, 0, 0x00ffffff, "Jayden Canales");
    r.bot -= 20;
    ggprint13(&r, 0, 0x00ffffff, "Bryan Estrada");
    r.bot -= 20;
    ggprint13(&r, 0, 0x00ffffff, "Karen Santiago");
}
