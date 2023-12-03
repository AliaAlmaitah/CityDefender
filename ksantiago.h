#ifndef _KSANTIAGO_H_
#define _KSANTIAGO_H_

//Karen's CityDefender project files

//called from main program.
extern void display_gameover(int xres, int yres, int t);
extern void display_credits(int xres, int yres);
extern int total_physics_function_calls(const bool get);
extern int total_render_function_calls(const bool get);
extern void startscreen(int xres, int yres); //GLuint *cityTexture);
extern int start(int start_game, XEvent *e, int xres, int yres);
extern void new_highscore(const char filename[], char time2[]);

#endif //_KSANTIAGO_H_
