#ifndef ALARMSTATEMACHINE_H
#define ALARMSTATEMACHINE_H

#include <Arduino.h>
#include "Timer.h"

// Alarm System States
enum AlarmState {
  DISARMED,    // Alarm is off
  ARMING,      // 10 sec countdown to arm
  ARMED,       // Alarm is active, monitoring motion
  ENTRY_DELAY, // Motion detected, 10 sec to enter PIN
  TRIGGERED    // Alarm triggered, blinking alert
};

// Forward declarations for callback types
typedef void (*TriggeredCallback)();  // Called on every loop while TRIGGERED
typedef void (*DisarmedCallback)();   // Called when transitioning to DISARMED
typedef void (*ArmingCallback)();     // Called when transitioning to ARMING
typedef void (*EntryDelayCallback)(); // Called when transitioning to ENTRY_DELAY

class AlarmStateMachine {
public:
  // Constructor
  AlarmStateMachine(const String &pin, unsigned long delayMs = 10000);

  // Initialization
  void begin();

  // Event handlers
  void handleKeyPress(char key);
  void handleMotionDetected();

  // Update method - call this in loop()
  void update();

  // Callback setters
  void onTriggered(TriggeredCallback callback) { triggeredCallback = callback; }
  void onDisarmed(DisarmedCallback callback) { disarmedCallback = callback; }
  void onArming(ArmingCallback callback) { armingCallback = callback; }
  void onEntryDelay(EntryDelayCallback callback) { entryDelayCallback = callback; }

private:
  // State variables
  AlarmState currentState;
  String enteredPin;
  String correctPin;
  unsigned long delayPeriod;

  // Internal timer
  Timer timer;

  // Callbacks
  TriggeredCallback triggeredCallback;
  DisarmedCallback disarmedCallback;
  ArmingCallback armingCallback;
  EntryDelayCallback entryDelayCallback;

  // Helper methods
  void changeState(AlarmState newState);
  void startTimer();
  void stopTimer();
  void clearPin();
  void onTimerExpired();
  bool isPinCorrect() const { return enteredPin == correctPin; }
  void printStatus() const;
};

#endif

