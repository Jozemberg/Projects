#include <Arduino.h>
#include "lcd_wrapper.h"
#include "mastermind.h"

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  lcd_init();
  for(int i = 6; i <= 13; i++){
    pinMode(i,OUTPUT);  
  }
  for(int i = 2; i <= 5; i++){
    pinMode(i,INPUT);  
  }
  pinMode(A0,INPUT);
  delay(2000);
  
}
  

void loop() {
  char* code = generate_code(false, 4);
  play_game(code);
  free(code);
}
