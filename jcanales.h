#ifndef _JAYDEN_H_
#define _JAYDEN_H_

//FUNCTIONS CALLED IN THE MAIN PROGRAM
extern void display_border(int xres, int yres);
extern void display_hp(float health, int xres, int yres);
extern int time_since_mouse_moved(const bool get, bool moved);
//extern void render_drones(GLuint silhouette, int xres);
extern void render_drones(GLuint silhouette, float xpos, float ypos, float vel, bool alive);
extern void game_instructions(int xres, int yres);
#endif
