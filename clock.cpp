#include <Arduino.h>

int hour = 0;
int minutes = 0;
unsigned long now = 0;
int hour_L = 0;
int hour_R = 0;
int minutes_L = 0;
int minutes_R = 0;

// Pines de los pulsadores
int hour_button = 2; // Pin del botón de horas
int minute_button = 3; // Pin del botón de minutos

// Variables para el estado de los pulsadores
int hour_button_pressed = LOW;
int minute_button_pressed = LOW;
int last_hour_button_state = HIGH;
int last_minute_button_state = HIGH;

// Pines para los dígitos
int D1 = 5;
int D2 = 4;
int D3 = 3;
int D4 = 2;

// Pines para los segmentos
int A = 6;
int B = 7;
int C = 8;
int D = 9;
int E = 10;
int F = 11;
int G = 12;
int DOT = 13;

void readButton() {
  int hour_button_state = digitalRead(hour_button);
  int minute_button_state = digitalRead(minute_button);
  hour_button_pressed = (hour_button_state == LOW) && (last_hour_button_state == HIGH);
  minute_button_pressed = (minute_button_state == LOW) && (last_minute_button_state == HIGH);
  last_hour_button_state = hour_button_state;
  last_minute_button_state = minute_button_state;
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);

  pinMode(hour_button, INPUT);
  pinMode(minute_button, INPUT);
}

void loop() {
  readButton();
  // Set hours
  if (hour_button_pressed == HIGH) {
    if (hour < 23) {
      hour++;
    } else {
      hour = 0;
    }
    delay(200);
  }

  // Set minutes
  if (minute_button_pressed == HIGH) {
    if (minutes < 60) {
      minutes++;
    }
    if (minutes == 60 && hour < 23) {
      hour++;
      minutes = 0;
    }
    if (minutes == 60 && hour >= 23) {
      hour = 0;
      minutes = 0;
    }
    delay(200);
  }

  // Increase time each minute
  if (millis() > now + 60000) { // cada minuto
    now = millis();
    if (minutes < 60) {
      minutes++;
    }
    if (minutes == 60 && hour < 23) {
      hour++;
      minutes = 0;
    }
    if (minutes == 60 && hour >= 23) {
      hour = 0;
      minutes = 0;
    }
  }
  printTime();
}
