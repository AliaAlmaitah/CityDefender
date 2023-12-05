#ifndef _ALIA_H_
#define _ALIA_H_

// Alia's project header file

// Function prototypes
extern void display_name(int, int); // Display name function
extern void display_border(int xres, int yres); // Display border function
extern int time_since_key_press(const bool get); // Calculate time since key press
extern void handleKeyPressEvent(); // Handle key press events
void cleanupOpenAL(); // Clean up OpenAL resources
void toggleSound(); // Toggle sound on/off
void playShootSound(); // Play shooting sound effect

#endif // _ALIA_H_
