#include "AlarmStateMachine.h"

AlarmStateMachine::AlarmStateMachine(const String &pin, unsigned long delayMs)
    : correctPin(pin),
      delayPeriod(delayMs),
      currentState(DISARMED),
      enteredPin(""),
      timerRequestCallback(nullptr),
      stopTimerCallback(nullptr),
      triggeredCallback(nullptr),
      disarmedCallback(nullptr),
      armingCallback(nullptr),
      entryDelayCallback(nullptr) {
    //Constructor 
}

void AlarmStateMachine::begin() {
    currentState = DISARMED;
    enteredPin = "";
    Serial.println("=== ALARM STATE MACHINE INITIALIZED ===");
    printStatus();
}

void AlarmStateMachine::changeState(AlarmState newState) {
    currentState = newState;

    // Call appropriate callbacks when transitioning to states
    if (newState == DISARMED && disarmedCallback) {
        disarmedCallback();
    } else if (newState == ARMING && armingCallback) {
        armingCallback();
    } else if (newState == ENTRY_DELAY && entryDelayCallback) {
        entryDelayCallback();
    } else if (newState == TRIGGERED && triggeredCallback) {
        triggeredCallback();
    }
}

void AlarmStateMachine::startTimer() {
    if (timerRequestCallback != nullptr) {
        timerRequestCallback(delayPeriod);
    }
}

void AlarmStateMachine::stopTimer() {
    if (stopTimerCallback != nullptr) {
        stopTimerCallback();
    }
}

void AlarmStateMachine::clearPin() {
    enteredPin = "";
}

void AlarmStateMachine::handleKeyPress(char key) {
    Serial.print("Key pressed: ");
    Serial.println(key);

    switch (currentState) {
        case DISARMED:
            if (key == '*') {
                // Star key - attempt to arm system
                changeState(ARMING);
                startTimer();
                clearPin();
                Serial.println("Arming system... Exit now (10 sec)");
                printStatus();
            }
            break;
            
        case ARMING:
            // No key handling during arming
            break;
            
        case ARMED:
        case ENTRY_DELAY:
        case TRIGGERED:
            if (key == '#') {
                // Hash key - submit PIN to disarm
                if (isPinCorrect()) {
                    Serial.println("Correct PIN! Disarmed.");
                    changeState(DISARMED);
                    clearPin();
                    printStatus();
                } else {
                    Serial.println("Wrong PIN! Alarm stays armed.");
                    clearPin();
                }
            } else {
                // Any other key adds to PIN
                enteredPin += key;
                Serial.print("PIN entered so far: ");
                Serial.println(enteredPin);
            }
            break;
    }
}

void AlarmStateMachine::handleMotionDetected() {
    if (currentState == ARMED) {
        Serial.println("Motion detected! Entry delay started.");
        changeState(ENTRY_DELAY);
        startTimer();
        printStatus();
    }
}

void AlarmStateMachine::handleTimerExpired() {
    if (currentState == ARMING) {
        // Arming delay complete - transition to ARMED
        changeState(ARMED);
        clearPin();
        Serial.println("System ARMED! Monitoring for motion...");
        printStatus();
    } else if (currentState == ENTRY_DELAY) {
        // Entry delay expired - trigger alarm
        changeState(TRIGGERED);
        Serial.println("ALARM TRIGGERED!!!");
        printStatus();
    }
}

void AlarmStateMachine::update() {
    // Update method can be used for continuous state behaviors if needed
    // Currently no continuous behaviors required
}

void AlarmStateMachine::printStatus() const {
    switch (currentState) {
    case DISARMED:
        Serial.println("Status: DISARMED - Press * to arm");
        break;
    case ARMING:
        Serial.println("Status: ARMING - Exit in 10 seconds");
        break;
    case ARMED:
        Serial.println("Status: ARMED - Monitoring...");
        break;
    case ENTRY_DELAY:
        Serial.println("Status: ENTRY DELAY - Enter PIN!");
        break;
    case TRIGGERED:
        Serial.println("Status: TRIGGERED - ALARM!");
        break;
    }

    Serial.print("  PIN Entry: ");
    Serial.println(enteredPin.length() > 0 ? String(enteredPin.length()) + " digits entered" : "none");
}
