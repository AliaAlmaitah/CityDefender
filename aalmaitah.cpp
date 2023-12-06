/*   Filename: aalmaitah.cpp
 *   Purpose: Software Engineering Project source file.
 *   Copyright (c) Alia Al-Maitah.
 *   Author: Alia Al-Maitah
 *   Created: October 1, 2023
 *   Last Modified: Dec 5.2023
 */

// Header information for the file, including filename, purpose, copyright, author, and modification history
#include "aalmaitah.h" // Including the custom header file associated with this source file.
#include <cstdio>      // Including standard I/O header for C, used for input and output operations.
#include <unistd.h>    // Including POSIX API for various constants and types.
#include <ctime>       // Including standard library for handling time.
#include <AL/al.h>     // Including OpenAL headers for audio functionality.
#include <AL/alc.h>    // Including OpenAL headers for context (device) management.
#include <AL/alut.h>   // Including OpenAL Utility Toolkit headers.

// Structure to hold OpenGL related data.
struct GLData {
    bool showStatistics = false;  // Boolean variable to control the display of statistics.
};

GLData glData;		          // Instance of GLData structure to maintain OpenGL data.


// Function to calculate the time elapsed since the last key press.
int time_since_key_press(const bool get) {

    static int lastKeyPressTime = time(nullptr);  // Static variable to store the last key press time.

    if (!get) {
        lastKeyPressTime = time(nullptr);     // Update last key press time.
        return 0;
    }

    return time(nullptr) - lastKeyPressTime;  // Calculate and return the time elapsed since the last key press.
}

// Function to update the time of the last key press.
void updateKeyPressTime() {
    time_since_key_press(false);
}

// OpenAL sound code is now always included in the compilation
static bool isSoundInitialized = false;  // Flag to check if sound is initialized.
static ALuint alSource[2];		 // Array to store sound sources.
static ALuint alBuffer[2];		 // Array to store sound sources.
static ALuint shootSoundBuffer;		 // Variable to store shooting sound buffer.
static bool isBackgroundSoundPlaying = false; // Flag to check if background sound is playing.

// Initialize OpenAL for sound processing.
void initOpenAL() {
    alutInit(nullptr, nullptr);
    if (alGetError() != AL_NO_ERROR) {
        printf("ERROR: alutInit() failed\n"); // Check for errors in initialization.
        return;
    }

    // Listener and buffer setup for OpenAL, including position, orientation, and gain.
    // Listener setup
    float listenerOrientation[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, listenerOrientation);
    alListenerf(AL_GAIN, 1.0f);

    // Buffer setup
    alBuffer[0] = alutCreateBufferFromFile("/home/alia/Documents/CityDefender/Sounds/BattleMetal-320bit(chosic.com).wav");
    alBuffer[1] = alutCreateBufferFromFile("/home/alia/Documents/CityDefender/Sounds/BattleMetal-320bit(chosic.com).wav");

    // Source setup
    alGenSources(2, alSource);
    for (int i = 0; i < 2; ++i) {
        alSourcei(alSource[i], AL_BUFFER, alBuffer[i]);
        alSourcef(alSource[i], AL_GAIN, (i == 0 ? 1.0f : 0.5f));
        alSourcef(alSource[i], AL_PITCH, 1.0f);
        alSourcei(alSource[i], AL_LOOPING, (i == 0 ? AL_FALSE : AL_TRUE));
    }

    isSoundInitialized = true;
}

// Function to toggle background sound playing state.
void toggleSound() {
    if (!isSoundInitialized) {
        initOpenAL();
    }

    if (isBackgroundSoundPlaying) {
        alSourcePause(alSource[1]);
    } else {
        alSourcePlay(alSource[1]);
    }

    isBackgroundSoundPlaying = !isBackgroundSoundPlaying; // Update the flag indicating the playing state.
}

// Initialize the shooting sound buffer.
void initShootSound() {
     // Load shooting sound from file and check for errors.
    shootSoundBuffer = alutCreateBufferFromFile("/home/alia/Documents/CityDefender/Sounds/blaster-2-81267.wav");
    if (shootSoundBuffer == AL_NONE) {
        printf("ERROR: Failed to load shoot sound buffer\n");
    }
}

// Play the shooting sound effect.
void playShootSound() {
    if (!isSoundInitialized) {
        initOpenAL();
        initShootSound();
    }

    ALuint shootSource;
    alGenSources(1, &shootSource);
    alSourcei(shootSource, AL_BUFFER, shootSoundBuffer);
    alSourcePlay(shootSource);

    if (alGetError() != AL_NO_ERROR) {
        printf("ERROR: Failed to play shooting sound\n");
    }
}

// Clean up and release OpenAL resources when done.
void cleanupOpenAL() {
    if (!isSoundInitialized) {
        return;
    }

    alSourceStopv(2, alSource);
    alDeleteSources(2, alSource);
    alDeleteBuffers(2, alBuffer);

    ALCcontext *context = alcGetCurrentContext();
    if (context) {
        ALCdevice *device = alcGetContextsDevice(context);
        if (device) {
            alcMakeContextCurrent(nullptr);
            alcDestroyContext(context);
            alcCloseDevice(device);
        }
    }

    isSoundInitialized = false;  // Reset the initialization flag.
}
// Callback function to handle keyboard events.
void keyCallback(unsigned char key, int, int) {
    if (key == 'S' || key == 's') {
        glData.showStatistics = !glData.showStatistics;
    }

    updateKeyPressTime();

    // This section was previously under the USE_OPENAL_SOUND directive
    if (key == 'M' || key == 'm') {
        toggleSound();    // Toggle sound on 'M' key press.
    }
}
