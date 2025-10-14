#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer {
public:
  // Callback function type
  typedef void (*TimerCallback)();
  
  // Constructor
  Timer();
  
  // Start the timer with a duration and callback
  void start(unsigned long durationMs, TimerCallback callback);
  
  // Stop/reset the timer
  void stop();
  
  // Update method - call this in loop()
  void update();
  
private:
  unsigned long startTime;
  unsigned long duration;
  bool running;
  bool expired;
  TimerCallback callback;
};

#endif

