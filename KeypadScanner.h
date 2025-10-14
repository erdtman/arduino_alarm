#ifndef KEYPADSCANNER_H
#define KEYPADSCANNER_H

#include "Arduino.h"

// Callback function type for key press events
typedef void (*KeyPressCallback)(char key);

class KeypadScanner {
private:
    byte rows;
    byte cols;
    byte* rowPins;
    byte* colPins;
    
    // Keypad layout
    static const char keys[4][3];
    
    // Callback and state tracking
    KeyPressCallback callback;
    char lastKey;  // Track last pressed key to detect new presses
    
    boolean areConnected(byte outPin, byte inPin);
    char scan();  // Internal scan method

public:
    KeypadScanner(byte* rowPinsArray, byte rowCount, 
                  byte* colPinsArray, byte colCount);
    void begin();
    void update();  // Call this regularly to check for key presses
    void onKeyPress(KeyPressCallback cb);  // Set the callback function
};

#endif

