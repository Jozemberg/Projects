#include <Arduino.h>
#include <string.h>
#include "lcd_wrapper.h"
#include "mastermind.h"

bool is_enter_pressed(){
  if(analogRead(BTN_ENTER_PIN) == 0)return true;
  return false;  
}

void play_game(char* secret){
  Serial.println(secret);
  char* guess_code = (char*)calloc(4+1,sizeof(char));
  for(int i = 0; i < 4; i++){
    guess_code[i] = 48;  
  }
  char* tries_left = (char*)calloc(2+1,sizeof(char));
  int columns = 1, rows = 10;
  char* history[rows][columns];
  int peg_a = 0, peg_b = 0, hp = 10, i = 4, history_counter = 0, btn_one_calc = 0, history_index = 0;
  tries_left[0] = 49;
  tries_left[1] = 48;
  
  
  turn_off_leds();
  lcd_clear();
  lcd_set_cursor(1,0);
  lcd_print("Your guess: ");
  lcd_set_cursor(1,12);
  lcd_print(guess_code);
  lcd_set_cursor(0,0);
  lcd_print("Tries left: ");
  lcd_set_cursor(0,13);
  lcd_print(tries_left);
  
  while(peg_a != 4 && hp > 0){
    while(is_enter_pressed() == false){
      delay(100);
      if(digitalRead(BTN_1_PIN) == HIGH){
        while(digitalRead(BTN_1_PIN) == HIGH){
          delay(80);
          btn_one_calc++;
          if(btn_one_calc > 100)btn_one_calc = 11;
          if(btn_one_calc > 10){
            if(digitalRead(BTN_2_PIN) == HIGH)history_index--;
            while(digitalRead(BTN_2_PIN) == HIGH);
            if(digitalRead(BTN_3_PIN) == HIGH)history_index++;
            while(digitalRead(BTN_3_PIN) == HIGH);
            if(history_index < 0)history_index = history_counter - 1;
            if(history_index >= history_counter)history_index = 0; 
            render_history(secret, *history, history_index);
          }
        }
        lcd_clear();
        lcd_set_cursor(1,0);
        lcd_print("Your guess: ");
        lcd_set_cursor(1,12);
        lcd_print(guess_code);
        lcd_set_cursor(0,0);
        lcd_print("Tries left: ");
        lcd_set_cursor(0,13);
        lcd_print(tries_left);
        if(btn_one_calc <= 10)i = 0;
        btn_one_calc = 0;
      }
      
      if(digitalRead(BTN_2_PIN) == HIGH)i = 1;
      while(digitalRead(BTN_2_PIN) == HIGH);
      if(digitalRead(BTN_3_PIN) == HIGH)i = 2;
      while(digitalRead(BTN_3_PIN) == HIGH);
      if(digitalRead(BTN_4_PIN) == HIGH)i = 3;
      while(digitalRead(BTN_4_PIN) == HIGH);
      if(i < 4){
        guess_code[i] += 1;
        if(guess_code[i] > 57)guess_code[i] = 48;
        //lcd_clear();
        lcd_set_cursor(1,0);
        lcd_print("Your guess: ");
        lcd_set_cursor(1,12);
        lcd_print(guess_code);
        //delay(200);
      }
      i = 4;
      
    }
    while(is_enter_pressed() == true);
    
    get_score(secret, guess_code, &peg_a, &peg_b);
    render_leds(peg_a, peg_b);
    if(peg_a != 4){
      hp--;
      tries_left[0] = 48;
      tries_left[1] = 48 + hp;
      lcd_set_cursor(0,13);
      lcd_print(tries_left); 
    }
    strcpy(history[history_counter][0],guess_code);
    //Serial.println(history[history_counter][0]);
    history_counter++;
  }
  if(peg_a == 4){
    lcd_clear();
    lcd_set_cursor(0,1);
    lcd_print("Congratulations");
    lcd_set_cursor(1,4);
    lcd_print("YOU WON!");
    win_leds();
    delay(3000);
  }
  if(hp == 0){
    lcd_clear();
    lcd_set_cursor(0,0);
    lcd_print("NO LUCK YOU LOST");
    delay(3000);
  }
  free(guess_code);
  free(tries_left);
}



void render_history(char* secret, char** history, const int entry_nr){
  char* history_string = (char*)calloc(4+1,sizeof(char));
  int peg_a = 0, peg_b = 0;
  turn_off_leds();
  get_score(secret, &history[entry_nr][0], &peg_a, &peg_b);
  strcpy(history_string, history[entry_nr]);
  render_leds(peg_a,peg_b);
  lcd_set_cursor(0,0);
  lcd_clear();
  lcd_set_cursor(0,0);
  lcd_print("History: ");
  lcd_set_cursor(0,10);
  lcd_print(history_string);
  delay(100);
  free(history_string);
}
  
void get_score(const char* secret, const char* guess, int* peg_a, int* peg_b){
  *peg_a = 0;
  *peg_b = 0;
  for(int i = 0; i < 4; i++){
      if(secret[i] == guess[i])*peg_a = *peg_a + 1;
      
  }
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(secret[i] == guess[j])*peg_b = *peg_b + 1;
    }
  }
}

char* generate_code(bool repeat, int length){
  if(length < 1)return NULL;
  char* code = (char*)calloc(length+1,sizeof(char));
  int min, max, count = 0;
  min = 0;
  max = 10;
  if(repeat == true){
    while(length > count){
      code[count] = (char)(random(min, max) + 48);
      count++;
    }    
  }
  if(repeat == false){
    while(length > count){
      code[count] = (char)(random(min, max) + 48);
      count++;
    }
    for(int i = 0; i < length; i++){
      for(int j = 1+i; j < length; j++){
        while(code[i] == code[j])code[j] = (char)(random(min, max) + 48);
      }
    }    
  }
  return code;
  free(code);
}

void render_leds(const int peg_a, const int peg_b){
  turn_off_leds();
  if(peg_a > 0)digitalWrite(LED_RED_1,HIGH);
  if(peg_a > 1)digitalWrite(LED_RED_2,HIGH);
  if(peg_a > 2)digitalWrite(LED_RED_3,HIGH);
  if(peg_a > 3)digitalWrite(LED_RED_4,HIGH);

  if(peg_b > 0 && digitalRead(LED_RED_1) == LOW)digitalWrite(LED_BLUE_1,HIGH);
  if(peg_b > 1 && digitalRead(LED_RED_2) == LOW)digitalWrite(LED_BLUE_2,HIGH);
  if(peg_b > 2 && digitalRead(LED_RED_3) == LOW)digitalWrite(LED_BLUE_3,HIGH);
  if(peg_b > 3 && digitalRead(LED_RED_4) == LOW)digitalWrite(LED_BLUE_4,HIGH);
}

void turn_off_leds(){
  for(int i = 6; i <= 13; i++){
    digitalWrite(i, LOW);  
  }
}

void win_leds(){
  int count = 0;
  while(count != 5){
    for(int i = 6; i <= 13; i++){
      digitalWrite(i, HIGH); 
      delay(50); 
      digitalWrite(i, LOW); 
      delay(50); 
    }
    count++;
  }
  turn_off_leds();
}
