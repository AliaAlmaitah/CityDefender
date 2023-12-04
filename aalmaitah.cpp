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

//sound
/*
    #ifdef USE_OPENAL_SOUND
    if (key == 'M' || key == 'm') {
        toggleSound();
    }
    #endif
}

#ifdef USE_OPENAL_SOUND
static bool soundInitialized = false;
static ALuint alSource[2];
static ALuint alBuffer[2];
static ALuint shootSoundBuffer;

void initOpenAL() {
    alutInit(0, NULL);
    if (alGetError() != AL_NO_ERROR) {
        printf("ERROR: alutInit()\n");
        return;
    }

    // Listener setup
    float vec[6] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, vec);
    alListenerf(AL_GAIN, 1.0f);

    // Buffer setup
    alBuffer[0] = alutCreateBufferFromFile("/home/alia/Documents/CityDefender/Sounds/BattleMetal-320bit(chosic.com).wav");
    alBuffer[1] = alutCreateBufferFromFile("/home/alia/Documents/CityDefender/Sounds/BattleMetal-320bit(chosic.com).wav");

    // Source setup
    alGenSources(2, alSource);
    alSourcei(alSource[0], AL_BUFFER, alBuffer[0]);
    alSourcei(alSource[1], AL_BUFFER, alBuffer[1]);

    // Set up source properties
    alSourcef(alSource[0], AL_GAIN, 1.0f);
    alSourcef(alSource[0], AL_PITCH, 1.0f);
    alSourcei(alSource[0], AL_LOOPING, AL_FALSE);

    alSourcef(alSource[1], AL_GAIN, 0.5f);
    alSourcef(alSource[1], AL_PITCH, 1.0f);
    alSourcei(alSource[1], AL_LOOPING, AL_TRUE);

    soundInitialized = true;
}

void toggleSound() {
    if (!soundInitialized) {
        initOpenAL();
    }

    static bool soundPlaying = false;

    if (soundPlaying) {
        // Stop sound
        alSourceStop(alSource[1]);
    } else {
        // Play sound
        alSourcePlay(alSource[1]);
    }

    soundPlaying = !soundPlaying;
}

void initshootSound() {
    shootSoundBuffer = alutCreateBufferFromFile("/home/alia/Documents/CityDefender/Sounds/blaster-2-81267.wav");
}

void playshootSound() {
    if (!soundInitialized) {
        initOpenAL();
        initshootSound();
    }

    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, shootSoundBuffer);
    alSourcePlay(source);
}
#endif // USE_OPENAL_SOUND

#ifdef USE_OPENAL_SOUND
void cleanupOpenAL() {
    if (!soundInitialized) {
        return;
    }

    // Stop playing and delete sources
    alSourceStopv(2, alSource); // Stop playing all sources
    alDeleteSources(2, alSource);

    // Delete buffers
    alDeleteBuffers(2, alBuffer);

    // Get current context
    ALCcontext *Context = alcGetCurrentContext();
    if (Context != NULL) {
        // Get the device used by that context
        ALCdevice *Device = alcGetContextsDevice(Context);
        if (Device != NULL) {
            // Disable context
            alcMakeContextCurrent(NULL);
            // Release context
            alcDestroyContext(Context);
            // Close the device
            alcCloseDevice(Device);
        }
    }

    soundInitialized = false;
}
#endif // USE_OPENAL_SOUND
*/

