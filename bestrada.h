#ifndef BESTRADA_H_
#define BESTRADA_H_

//Project Files

extern void Test_Robot(double * , double * );
extern void moveRight(double *, int );
extern void moveLeft(double *);
extern int total_running_time(const bool get);
extern double total_mouse_distance(double x, double y, const bool get);
extern void Controls(int xres, int yres);
extern float xformation(int form, int count);
extern float yformation(int form, int count);

#endif
