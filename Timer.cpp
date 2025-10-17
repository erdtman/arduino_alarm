#include "Timer.h"

Timer::Timer() 
  : startTime(0), 
    duration(0), 
    running(false), 
    expired(false), 
    callback(nullptr) {
}

void Timer::onExpired(TimerCallback callback) {
  this->callback = callback;
}

void Timer::start(unsigned long durationMs) {
  startTime = millis();
  duration = durationMs;
  running = true;
  expired = false;
}

void Timer::stop() {
  running = false;
  expired = false;
  startTime = 0;
  duration = 0;
}

void Timer::update() {
  if (!running || expired) {
    return;
  }
  
  // Check if timer has expired
  if ((millis() - startTime) >= duration) {
    running = false;
    expired = true;
    if (callback != nullptr) {
      callback();
    } else {
      Serial.println("WARNING: Timer callback not set");
    }
  }
}

