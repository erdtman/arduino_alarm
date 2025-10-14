#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

/**
 * @brief Simple buzzer control library
 * 
 * Provides basic on/off control for a buzzer connected to a digital pin.
 */
class Buzzer
{
public:
  /**
   * @brief Construct a new Buzzer object
   * @param pin The digital pin number connected to the buzzer
   */
  Buzzer(uint8_t pin);

  /**
   * @brief Initialize the buzzer pin
   * Must be called in setup() before using the buzzer
   */
  void begin();

  /**
   * @brief Turn the buzzer on
   */
  void on();

  /**
   * @brief Turn the buzzer off
   */
  void off();

private:
  uint8_t _pin;
};

#endif // BUZZER_H

