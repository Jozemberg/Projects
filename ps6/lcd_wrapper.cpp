#include <Arduino.h>
#include "lcd_wrapper.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
void lcd_init(){
  lcd.init();              
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Welcome to LOGIK");
  lcd.setCursor(0,1);
  lcd.print("Guess the number");
}

void lcd_clear(){
  lcd.clear();
}


void lcd_set_cursor(int y, int x){
  lcd.setCursor(x,y);
}


void lcd_print(char* text){
    lcd.print(text);
    //Serial.println("78");
}


void lcd_print_at(int y, int x, char* text){
    lcd_set_cursor(y, x);
    lcd_print(text);
}
