#ifndef DIGITMATRIX_H
#define DIGITMATRIX_H

#include "Arduino.h"
#include "Arduino_LED_Matrix.h"

// Structure to define a pattern
struct Pattern {
    byte** frames;        // Array of pointers to frame data
    int frameCount;       // Number of frames in the pattern
    bool loops;           // Whether pattern loops or stops at end
    int intervalMs;       // Time between frames in milliseconds
};

class DigitMatrix {
private:
    ArduinoLEDMatrix matrix;
    static byte digit0[8][12];
    static byte digit1[8][12];
    static byte digit2[8][12];
    static byte digit3[8][12];
    static byte digit4[8][12];
    static byte digit5[8][12];
    static byte digit6[8][12];
    static byte digit7[8][12];
    static byte digit8[8][12];
    static byte digit9[8][12];
    static byte digitStar[8][12];
    static byte digitHash[8][12];
    static byte* digits[10];
    static byte clearPattern[8][12];
    static byte onPattern[8][12];
    
    // Pattern playback state
    bool isPlayingPattern;
    Pattern* currentPattern;
    int currentFrameIndex;
    unsigned long lastFrameTime;

public:
    DigitMatrix();
    void begin();
    void setDigit(int digit);
    void setChar(char c);
    void clear();
    void playPattern(Pattern* pattern);
    void stopPattern();
    void update();
    
    // Helper method to create patterns
    static Pattern createBlinkPattern(int intervalMs = 200);
    static Pattern createCountdownPattern(int intervalMs = 1000);
};

#endif
