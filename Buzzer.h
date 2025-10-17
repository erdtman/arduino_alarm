#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

// Structure to define a buzzer pattern
struct BuzzerPattern {
  unsigned int onDuration;   // Duration buzzer is on (milliseconds)
  unsigned int offDuration;  // Duration buzzer is off (milliseconds)
  int cycles;                // Number of on/off cycles (-1 for infinite)
};

/**
 * @brief Buzzer control library with pattern support
 * 
 * Provides basic on/off control and non-blocking pattern playback.
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

  /**
   * @brief Create a short blip sound (blocking)
   * @param duration Duration of the blip in milliseconds (default 100ms)
   */
  void blip(unsigned int duration = 100);

  /**
   * @brief Play a buzzer pattern (non-blocking)
   * @param pattern Pointer to the pattern to play
   */
  void playPattern(BuzzerPattern* pattern);

  /**
   * @brief Stop pattern playback
   */
  void stopPattern();

  /**
   * @brief Update function - must be called in main loop for patterns to work
   */
  void update();

  /**
   * @brief Create a beep pattern
   * @param onMs Duration buzzer is on (milliseconds)
   * @param offMs Duration buzzer is off (milliseconds)
   * @param cycles Number of beep cycles
   * @return BuzzerPattern structure
   */
  static BuzzerPattern createBeepPattern(unsigned int onMs, unsigned int offMs, int cycles);

private:
  uint8_t _pin;
  
  // Pattern playback state
  bool isPlayingPattern;
  BuzzerPattern* currentPattern;
  int currentCycle;
  bool isCurrentlyOn;
  unsigned long lastTransitionTime;
};

#endif // BUZZER_H

