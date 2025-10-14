#include "DigitMatrix.h"
#include "KeypadScanner.h"
#include "MotionSensor.h"
#include "Timer.h"
#include "AlarmStateMachine.h"
#include "Buzzer.h"

DigitMatrix digitMatrix;

// Define patterns (static to persist)
Pattern blinkPattern;
Pattern countdownPattern;

#define ROWS 4
#define COLS 3
#define PIR_PIN 9     // PIR motion sensor pin
#define BUZZER_PIN 10 // Optional buzzer for alarm sound

byte rowPins[ROWS] = {5, 4, 3, 2}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6};    // Connect to the column pinouts of the keypad

// Initialize KeypadScanner with pin arrays
KeypadScanner keypad(rowPins, ROWS, colPins, COLS);

// Initialize MotionSensor
MotionSensor motionSensor(PIR_PIN);

// Initialize Buzzer
Buzzer buzzer(BUZZER_PIN);

// Initialize Timer (single timer for all states)
Timer timer;

// Initialize AlarmStateMachine
AlarmStateMachine alarmSystem("1234", 10000);  // PIN: 1234, Delay: 10 seconds

// Forward declarations for callbacks
void onTimerExpired();
void onMotionDetected();
void onStartAlarmTimer(unsigned long duration);
void onStopAlarmTimer();
void onAlarmTriggered();
void onDisarmed();
void onArming();
void onEntryDelay();

// Timer callback function
void onTimerExpired() {
  alarmSystem.handleTimerExpired();
}

// Motion detection callback
void onMotionDetected() {
  alarmSystem.handleMotionDetected();
}

// Keypad callback
void handleKeyPress(char key) {
  digitMatrix.setChar(key);  // Show the key on display
  alarmSystem.handleKeyPress(key);
}

// Callback implementations for AlarmStateMachine
void onStartAlarmTimer(unsigned long duration) {
  timer.start(duration, onTimerExpired);
}

void onStopAlarmTimer() {
  timer.stop();
}

void onAlarmTriggered() {
  // Called once when alarm is triggered
  buzzer.on();
  digitMatrix.playPattern(&blinkPattern);
}

void onDisarmed() {
  // Called when alarm is disarmed
  buzzer.off();
  digitMatrix.stopPattern();
}

void onArming() {
  // Called when entering ARMING state
  digitMatrix.playPattern(&countdownPattern);
}

void onEntryDelay() {
  // Called when entering ENTRY_DELAY state
  digitMatrix.playPattern(&countdownPattern);
}

void setup() {
  Serial.begin(9600);
  buzzer.begin();

  // Initialize display patterns
  blinkPattern = DigitMatrix::createBlinkPattern(200);     // Fast blink for alarm
  countdownPattern = DigitMatrix::createCountdownPattern(1000);  // 1 second per digit

  digitMatrix.begin();
  keypad.begin();                               // Initialize keypad pins
  keypad.onKeyPress(handleKeyPress);            // Set keypad callback
  motionSensor.begin();                         // Initialize motion sensor pin
  motionSensor.onMotionStart(onMotionDetected); // Set motion detection callback

  // Initialize alarm state machine with callbacks
  alarmSystem.begin();
  alarmSystem.onTimerRequest(onStartAlarmTimer);
  alarmSystem.onStopTimer(onStopAlarmTimer);
  alarmSystem.onTriggered(onAlarmTriggered);
  alarmSystem.onDisarmed(onDisarmed);
  alarmSystem.onArming(onArming);
  alarmSystem.onEntryDelay(onEntryDelay);

  Serial.println("=== ALARM SYSTEM INITIALIZED ===");
  Serial.println("Default PIN: 1234 (change in code)");
  Serial.println("Press * to arm, # to submit PIN");
  Serial.println("================================");
}

void loop() {
  // Update timer (will call callback if timer expires)
  timer.update();

  // Update motion sensor (will call callback if motion starts)
  motionSensor.update();

  // Update keypad (will call callback if key is pressed)
  keypad.update();

  // Update alarm state machine (will call onAlarmTriggered if in TRIGGERED state)
  alarmSystem.update();

  // Update digit matrix (for non-blocking blink pattern)
  digitMatrix.update();

  // Small delay for stability
  delay(100);
}