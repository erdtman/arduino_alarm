#include "MotionSensor.h"

MotionSensor::MotionSensor(int pin) {
  _pin = pin;
  _lastMotionState = false;
  _motionStartCallback = nullptr;
}

void MotionSensor::begin() {
  pinMode(_pin, INPUT);
}

void MotionSensor::onMotionStart(void (*callback)()) {
  _motionStartCallback = callback;
}

void MotionSensor::update() {
  // Read current motion state
  bool motionDetected = digitalRead(_pin);
  
  // Check if motion state has changed from LOW to HIGH (motion started)
  if (motionDetected && !_lastMotionState) {
    // Call the callback if one has been set
    if (_motionStartCallback != nullptr) {
      _motionStartCallback();
    } else {
      Serial.println("WARNING: MotionSensor callback not set");
    }
  }
  
  // Update last motion state
  _lastMotionState = motionDetected;
}

