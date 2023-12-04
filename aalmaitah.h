#ifndef _ALIA_H_
#define _ALIA_H_

// Alia's project file

// Called from main program
extern void display_name(int, int);
extern void display_border(int xres, int yres);
extern int time_since_key_press(const bool get);
extern void handleKeyPressEvent();

#ifdef USE_OPENAL_SOUND
extern void playOpenALSample();
//extern void toggleSound();  // Declaration for toggleSound
//void cleanupOpenAL();
//void playshootSound();

#endif


//class alia {
 //   int abc;
//};

#endif // _ALIA_H_

