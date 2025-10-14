#include "KeypadScanner.h"

// Define the keypad layout
const char KeypadScanner::keys[4][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

// Constructor
KeypadScanner::KeypadScanner(byte* rowPinsArray, byte rowCount, 
                             byte* colPinsArray, byte colCount) {
    rowPins = rowPinsArray;
    rows = rowCount;
    colPins = colPinsArray;
    cols = colCount;
    callback = nullptr;
    lastKey = '\0';
}

// Initialize pin modes
void KeypadScanner::begin() {
    // Set all row pins to INPUT
    for (int i = 0; i < rows; i++) {
        pinMode(rowPins[i], INPUT);
    }
    
    // Set all column pins to INPUT
    for (int i = 0; i < cols; i++) {
        pinMode(colPins[i], INPUT);
    }
}

// Check if two pins are connected
boolean KeypadScanner::areConnected(byte outPin, byte inPin) {
    // Set output pin to OUTPUT mode
    pinMode(outPin, OUTPUT);
    pinMode(inPin, INPUT_PULLUP);
    
    // Test 1: Drive output pin LOW and check if input pin reads LOW
    digitalWrite(outPin, LOW);
    delayMicroseconds(10); // Small delay for signal to stabilize
    boolean test1 = (digitalRead(inPin) == LOW);
    
    // Test 2: Drive output pin HIGH and check if input pin reads HIGH
    digitalWrite(outPin, HIGH);
    delayMicroseconds(10);
    boolean test2 = (digitalRead(inPin) == HIGH);
    
    // Reset both pins back to INPUT mode
    pinMode(outPin, INPUT);
    pinMode(inPin, INPUT);
    
    // Both tests must pass for pins to be connected
    return (test1 && test2);
}

// Set the callback function for key press events
void KeypadScanner::onKeyPress(KeyPressCallback cb) {
    callback = cb;
}

// Internal scan method - scans the keypad matrix and finds the first connection
// Returns the character from the keys matrix if a connection is found
// Returns '\0' (null character) if no connection is found
char KeypadScanner::scan() {
    // Loop through each row
    for (int row = 0; row < rows; row++) {
        // Loop through each column
        for (int col = 0; col < cols; col++) {
            // Use areConnected to test if the row and column pins are connected
            // (pinMode setup and cleanup is handled inside areConnected)
            if (areConnected(rowPins[row], colPins[col])) {
                // Return the character from the keys matrix
                return keys[row][col];
            }
        }
    }
    
    // No connection found, return null character
    return '\0';
}

// Update method - call this regularly in loop()
// Detects key presses and calls the callback once per press
void KeypadScanner::update() {
    char currentKey = scan();
    
    // Check if we have a new key press (transition from no key to a key)
    if (currentKey != '\0' && currentKey != lastKey) {
        // New key pressed, call the callback
        if (callback != nullptr) {
            callback(currentKey);
        }
    }
    
    // Update the last key state
    lastKey = currentKey;
}

