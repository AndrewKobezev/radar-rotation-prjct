#include <Arduino.h>

const int motorPin = 9;
const int buttonPin = 2;

int mode = 0;
bool lastButtonState = HIGH;

int pwmModeA = 80;   // примерно 6 RPM (подбирается)
int pwmModeB = 120;  // примерно 10 RPM

void setup() {

  pinMode(motorPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // настройка PWM 31 kHz (Timer1)
  TCCR1A = 0;
  TCCR1B = 0;

  TCCR1A |= (1 << COM1A1);
  TCCR1A |= (1 << WGM10);
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);

}

void loop() {

  bool buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {

    mode++;

    if (mode > 1) {
      mode = 0;
    }

    delay(200); // антидребезг
  }

  lastButtonState = buttonState;

  if (mode == 0) {
    OCR1A = pwmModeA;
  } else {
    OCR1A = pwmModeB;
  }

}