#include "Buzzer.h"

Buzzer::Buzzer(uint8_t pin)
  : _pin(pin),
    isPlayingPattern(false),
    currentPattern(nullptr),
    currentCycle(0),
    isCurrentlyOn(false),
    lastTransitionTime(0) {
}

void Buzzer::begin() {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);  // Start with buzzer off
}

void Buzzer::on() {
  // Stop any playing pattern when manually turning on
  isPlayingPattern = false;
  digitalWrite(_pin, HIGH);
}

void Buzzer::off() {
  // Stop any playing pattern when manually turning off
  isPlayingPattern = false;
  digitalWrite(_pin, LOW);
}

void Buzzer::blip(unsigned int duration) {
  // Stop any playing pattern when blipping
  isPlayingPattern = false;
  digitalWrite(_pin, HIGH);
  delay(duration);
  digitalWrite(_pin, LOW);
}

void Buzzer::playPattern(BuzzerPattern* pattern) {
  if (pattern == nullptr) {
    Serial.println("Error: Cannot play null buzzer pattern");
    return;
  }
  
  Serial.print("Buzzer::playPattern - On: ");
  Serial.print(pattern->onDuration);
  Serial.print("ms, Off: ");
  Serial.print(pattern->offDuration);
  Serial.print("ms, Cycles: ");
  Serial.println(pattern->cycles);
  
  isPlayingPattern = true;
  currentPattern = pattern;
  currentCycle = 0;
  isCurrentlyOn = true;
  lastTransitionTime = millis();
  
  // Turn buzzer on for the first cycle
  digitalWrite(_pin, HIGH);
}

void Buzzer::stopPattern() {
  if (!isPlayingPattern) {
    return;
  }
  
  isPlayingPattern = false;
  currentPattern = nullptr;
  digitalWrite(_pin, LOW);
  Serial.println("Buzzer pattern stopped");
}

void Buzzer::update() {
  if (!isPlayingPattern || currentPattern == nullptr) {
    return;
  }
  
  unsigned long currentTime = millis();
  unsigned long elapsed = currentTime - lastTransitionTime;
  
  // Check if it's time to transition
  unsigned int duration = isCurrentlyOn ? currentPattern->onDuration : currentPattern->offDuration;
  
  if (elapsed < duration) {
    return; // Not time to transition yet
  }
  
  // Time to transition
  lastTransitionTime = currentTime;
  
  if (isCurrentlyOn) {
    // Turn off
    digitalWrite(_pin, LOW);
    isCurrentlyOn = false;
    Serial.print("Buzzer OFF - Cycle ");
    Serial.print(currentCycle + 1);
    Serial.print("/");
    Serial.println(currentPattern->cycles == -1 ? "INF" : String(currentPattern->cycles));
  } else {
    // Turn on for next cycle
    currentCycle++;
    
    // Check if we've completed all cycles
    if (currentPattern->cycles != -1 && currentCycle >= currentPattern->cycles) {
      // Pattern complete
      isPlayingPattern = false;
      currentPattern = nullptr;
      Serial.println("Buzzer pattern finished!");
      return;
    }
    
    digitalWrite(_pin, HIGH);
    isCurrentlyOn = true;
    Serial.print("Buzzer ON - Cycle ");
    Serial.print(currentCycle + 1);
    Serial.print("/");
    Serial.println(currentPattern->cycles == -1 ? "INF" : String(currentPattern->cycles));
  }
}

BuzzerPattern Buzzer::createBeepPattern(unsigned int onMs, unsigned int offMs, int cycles) {
  BuzzerPattern pattern;
  pattern.onDuration = onMs;
  pattern.offDuration = offMs;
  pattern.cycles = cycles;
  return pattern;
}

