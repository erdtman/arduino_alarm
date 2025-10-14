#ifndef MotionSensor_h
#define MotionSensor_h

#include "Arduino.h"

class MotionSensor {
  public:
    // Constructor takes the pin number
    MotionSensor(int pin);
    
    // Initialize the sensor (set pin mode)
    void begin();
    
    // Set callback function to be called when motion starts
    void onMotionStart(void (*callback)());
    
    // Call this from loop() to update sensor state and trigger callbacks
    void update();
    
  private:
    int _pin;
    bool _lastMotionState;
    void (*_motionStartCallback)();
};

#endif

