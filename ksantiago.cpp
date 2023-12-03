/**
 * Author:  Karen Santiago
 * Created: 9-25-2023
 *
 **/

#include <GL/glx.h>
#include "fonts.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
#include "bestrada.h"
#include "ksantiago.h"
using namespace std;

void startscreen(int xres, int yres) //GLuint *cityTexture) 
{
    //glGenTextures(1, cityTexture);
    Rect r;
    r.bot = (yres/2);
    r.left = (xres/2) - 125;
    r.center = 0;
    ggprint40(&r, 0, 0x00ffffff, "City Defender");
    r.bot -= 20;
    r.left = (xres/2) - 50;
    ggprint12(&r, 0, 0x00ffffff, "Press 'S' to play.");
}

int start(int start_game, XEvent *e, int xres, int yres) 
{
    int key = (XLookupKeysym(&e->xkey, 0) & 0x0000ffff);
    startscreen(xres, yres);
    switch (key) {
        case XK_s:
            start_game = 1;
            return start_game;
            break;
    }

    return start_game;
}

int total_physics_function_calls(const bool get) 
{
    static int physics = 0;
    if (get == false) {
        physics++;
    }
    if (get == true) {
        return physics;
    }
    return 0;
}

int total_render_function_calls(const bool get) 
{
    static int count = 0;
    if (get == false) {
        count++;
    }
    if (get == true) {
        return count;
    }
    return 0;
}

//call highscore and player's score
void display_gameover(int xres, int yres) //, int t)
{
    //static int time = t;
    Rect r;
    r.bot = yres/2;
    r.left = xres/2 - 125;
    r.center = 0;
    ggprint40(&r, 0, 0x00ff2400, "Game Over");
    r.bot -= 20;
    r.left += 20;
    ggprint16(&r, 0, 0x00ff2400, "Better luck next time");
}

void display_scores(int xres, int yres, int t) {
    static int time = t;
    Rect r;
    r.bot = yres/2;
    r.left = xres/2 - 175; //125;
    r.center = 0;
    ggprint40(&r, 0, 0x00ff2400, "You Saved the City!!!");

    const char filename[] = "highscore.txt";
    const char pscore[] = "pscore.txt";
    
    ofstream clear;
    clear.open(pscore);
    if (clear.fail()) {
        cout << "Error - opening" << pscore << endl;
        exit(0);
    }
    clear << "";
    clear.close();

    fstream fin;
    fstream score;
    fin.open(filename);
    if (fin.fail()) {
        cout << "Error - opening" << filename << endl;
        exit(0);
    }
    score.open(pscore);
    if (score.fail()) {
        cout << "Error - opening" << pscore << endl;
        exit(0);
    }

    score << time;
    score.close();
    
    score.open(pscore);
    if (score.fail()) {
        cout << "Error - opening" << pscore << endl;
        exit(0);
    }

    char line[10000];
    char time2[10000];
    fin.getline(line, 10000);
    score.getline(time2, 10000);
    
    //if player's score is higher than high score, put into file.
    static int highscore = atoi(line);
    int h;
    if (highscore == 0) {
        h = 1000000000;
    } else {
        h = highscore;
    } 
    if (time < h) {
    //if (time < highscore) {
        new_highscore(filename, time2);

        r.bot = yres/2 + 80;
        r.left = xres/2 - 160;
        ggprint40(&r, 0, 0x00ff2400, "New High Score!");
        r.left = xres/2 - 90;
        r.bot = yres/2 - 20;
        ggprint16(&r, 0, 0x00ff2400, "High Score: ");
        r.left = xres/2 + 20;
        ggprint16(&r, 0, 0x00ff2400, line);
        r.left = xres/2 - 90;
        r.bot -= 20;
        ggprint16(&r, 0, 0x00ff2400, "Your Score: ");
        r.left = xres/2 + 20;
        ggprint16(&r, 0, 0x00ff2400, time2);
    } else {
        r.left = xres/2 - 90;
        r.bot -= 20;
        ggprint16(&r, 0, 0x00ff2400, "High Score: ");
        r.left = xres/2 + 20;
        ggprint16(&r, 0, 0x00ff2400, line);
        r.left = xres/2 - 90;
        r.bot -= 20;
        ggprint16(&r, 0, 0x00ff2400, "Your Score: ");
        r.left = xres/2 + 20;
        ggprint16(&r, 0, 0x00ff2400, time2);
    }

    score.close();
    fin.close();
}

void new_highscore(const char filename[], char time2[])
{
    ofstream clear;
    clear.open(filename);
    clear << "";
    clear.close();

    fstream newhigh;
    newhigh.open(filename);
    newhigh << time2;
    newhigh.close();

}

void display_credits(int xres, int yres)
{
    Rect r;
    r.bot = (yres/2) - 75;
    r.left = (xres/2) - 60;
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
