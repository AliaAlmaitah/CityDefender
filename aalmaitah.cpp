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
    static int firsttime = 1;
    static int lastKeyPressTime;
    if (firsttime) {
        lastKeyPressTime = time(NULL);
        firsttime = 0;
    }
    if (get) {
        return time(NULL) - lastKeyPressTime;
    }
    return 0;
}

void updateKeyPressTime() {
    time_since_key_press(false); // This resets the timer
}
/*void keyCallback(unsigned char key, int , int) {

    if (key == 'S' || key == 's') {
        gl.statistics = !gl.statistics;
    } else {
        updateKeyPressTime(); 
    }
}*/
