#include "Buzzer.h"

Buzzer::Buzzer(uint8_t pin)
  : _pin(pin) {
}

void Buzzer::begin() {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);  // Start with buzzer off
}

void Buzzer::on() {
  digitalWrite(_pin, HIGH);
}

void Buzzer::off() {
  digitalWrite(_pin, LOW);
}

