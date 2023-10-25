/*
 *   Filename: aalmaitah.cpp
 *   Purpose: Software Engineering Project source file.
 *  (c) Copyright Alia Al-Maitah.
 *   Author: Alia Al-Maitah
 *   Created: January 1, 2023
 *   Last Modified:
*/


#include <ctime>

struct GLData {
    bool statistics = false;
};

GLData gl;

int time_since_key_press(const bool get) {
    static int lastKeyPressTime = time(NULL); // Initialize immediately

    if (!get) {
        // Update the lastKeyPressTime to current time when get is false
        lastKeyPressTime = time(NULL);
        return 0;
    }

    return time(NULL) - lastKeyPressTime;
}

void updateKeyPressTime() {
    // Reset the time of the last key press by calling time_since_key_press with get = false
    time_since_key_press(false);
}

void keyCallback(unsigned char key, int, int) {
    if (key == 'S' || key == 's') {
        gl.statistics = !gl.statistics;
    }
    // Any key press will reset the timer
    updateKeyPressTime();
}
