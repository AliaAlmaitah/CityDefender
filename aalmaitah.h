#ifndef _ALIA_H_
#define _ALIA_H_

// Include OpenAL headers
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

// Extern declarations for global variables (if they are defined in another file)
extern bool isSoundInitialized;
extern ALuint alSource[2];

// Function prototypes
extern void display_name(int, int); // Display name function
extern void display_border(int xres, int yres); // Display border function
extern int time_since_key_press(const bool get); // Calculate time since key press
extern void handleKeyPressEvent(); // Handle key press events
extern void cleanupOpenAL(); // Clean up OpenAL resources
extern void toggleSound(); // Toggle sound on/off
extern void playShootSound(); // Play shooting sound effect

// New function prototypes for advanced sound control
void setVolume(ALuint sourceIndex, float volume); // Set volume of a sound source
void setPitch(ALuint sourceIndex, float pitch); // Set pitch of a sound source
void enableLooping(ALuint sourceIndex, bool shouldLoop); // Enable/disable looping for a sound source

#endif // _ALIA_H_
