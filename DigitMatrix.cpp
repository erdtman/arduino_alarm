#include "DigitMatrix.h"

// Define the digit patterns
byte DigitMatrix::digit0[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte DigitMatrix::digit1[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte DigitMatrix::digit2[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte DigitMatrix::digit3[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte DigitMatrix::digit4[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte DigitMatrix::digit5[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte DigitMatrix::digit6[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte DigitMatrix::digit7[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte DigitMatrix::digit8[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte DigitMatrix::digit9[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte DigitMatrix::digitStar[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte DigitMatrix::digitHash[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte DigitMatrix::clearPattern[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte DigitMatrix::onPattern[8][12] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

// Array of pointers to digit frames
byte* DigitMatrix::digits[10] = {
  (byte*)digit0, (byte*)digit1, (byte*)digit2, (byte*)digit3, (byte*)digit4,
  (byte*)digit5, (byte*)digit6, (byte*)digit7, (byte*)digit8, (byte*)digit9
};

// Constructor
DigitMatrix::DigitMatrix() : isPlayingPattern(false), currentPattern(nullptr), currentFrameIndex(0), lastFrameTime(0) {
}

// Initialize the matrix
void DigitMatrix::begin() {
    matrix.begin();
}

// Set and display a digit on the matrix
void DigitMatrix::setDigit(int digit) {
    if (digit >= 0 && digit <= 9) {
        switch(digit) {
            case 0: matrix.renderBitmap(digit0, 8, 12); break;
            case 1: matrix.renderBitmap(digit1, 8, 12); break;
            case 2: matrix.renderBitmap(digit2, 8, 12); break;
            case 3: matrix.renderBitmap(digit3, 8, 12); break;
            case 4: matrix.renderBitmap(digit4, 8, 12); break;
            case 5: matrix.renderBitmap(digit5, 8, 12); break;
            case 6: matrix.renderBitmap(digit6, 8, 12); break;
            case 7: matrix.renderBitmap(digit7, 8, 12); break;
            case 8: matrix.renderBitmap(digit8, 8, 12); break;
            case 9: matrix.renderBitmap(digit9, 8, 12); break;
        }
    }
}

// Set and display a character on the matrix
void DigitMatrix::setChar(char c) {
    if (c >= '0' && c <= '9') {
        setDigit(c - '0');
    } else if (c == '*') {
        matrix.renderBitmap(digitStar, 8, 12);
    } else if (c == '#') {
        matrix.renderBitmap(digitHash, 8, 12);
    }
}

// Clear the display
void DigitMatrix::clear() {
    matrix.renderBitmap(clearPattern, 8, 12);
}

// Play a pattern
void DigitMatrix::playPattern(Pattern* pattern) {
    if (pattern == nullptr) {
        Serial.println("Error: Cannot play null pattern");
        return;
    }
    
    Serial.print("DigitMatrix::playPattern called - Frames: ");
    Serial.print(pattern->frameCount);
    Serial.print(", Loops: ");
    Serial.print(pattern->loops ? "Yes" : "No");
    Serial.print(", Interval: ");
    Serial.print(pattern->intervalMs);
    Serial.println("ms");
    
    isPlayingPattern = true;
    currentPattern = pattern;
    currentFrameIndex = 0;
    lastFrameTime = millis();
    
    // Display the first frame immediately
    if (pattern->frameCount > 0) {
        matrix.loadPixels(pattern->frames[0], 8 * 12);
        Serial.println("First frame displayed");
    }
}

// Stop pattern playback
void DigitMatrix::stopPattern() {
    isPlayingPattern = false;
    currentPattern = nullptr;
    clear();
    Serial.println("Pattern stopped");
}

// Create a blink pattern (alternates between full and empty)
Pattern DigitMatrix::createBlinkPattern(int intervalMs) {
    static byte* blinkFrames[2];
    blinkFrames[0] = (byte*)onPattern;
    blinkFrames[1] = (byte*)clearPattern;
    
    Pattern pattern;
    pattern.frames = blinkFrames;
    pattern.frameCount = 2;
    pattern.loops = true;
    pattern.intervalMs = intervalMs;
    
    return pattern;
}

// Create a countdown pattern (9 to 0, then clear, no loop)
Pattern DigitMatrix::createCountdownPattern(int intervalMs) {
    static byte* countdownFrames[11];
    countdownFrames[0] = (byte*)digit9;
    countdownFrames[1] = (byte*)digit8;
    countdownFrames[2] = (byte*)digit7;
    countdownFrames[3] = (byte*)digit6;
    countdownFrames[4] = (byte*)digit5;
    countdownFrames[5] = (byte*)digit4;
    countdownFrames[6] = (byte*)digit3;
    countdownFrames[7] = (byte*)digit2;
    countdownFrames[8] = (byte*)digit1;
    countdownFrames[9] = (byte*)digit0;
    countdownFrames[10] = (byte*)clearPattern;
    
    Pattern pattern;
    pattern.frames = countdownFrames;
    pattern.frameCount = 11;
    pattern.loops = false;
    pattern.intervalMs = intervalMs;
    
    return pattern;
}

// Update function - call this in the main loop
void DigitMatrix::update() {
    if (!isPlayingPattern || currentPattern == nullptr) {
        return;
    }
    
    unsigned long currentTime = millis();
    
    // Check if it's time to advance to the next frame
    if (currentTime - lastFrameTime < currentPattern->intervalMs) {
        return;
    }
    
    lastFrameTime = currentTime;
    
    // Move to next frame
    currentFrameIndex++;
    
    if (currentFrameIndex >= currentPattern->frameCount && !currentPattern->loops) {
        // Stop at the last frame
        currentFrameIndex = currentPattern->frameCount - 1;
        isPlayingPattern = false;
        Serial.println("Pattern finished!");
        return;
    }

    // Check if we've reached the end of the pattern
    if (currentFrameIndex >= currentPattern->frameCount) {
        // Loop back to the beginning
        currentFrameIndex = 0;
        Serial.println("Pattern looping...");
    }  
    
    // Display the current frame
    Serial.print("Displaying frame ");
    Serial.print(currentFrameIndex);
    Serial.print(" of ");
    Serial.println(currentPattern->frameCount);
    
    matrix.loadPixels(currentPattern->frames[currentFrameIndex], 8 * 12);
}
