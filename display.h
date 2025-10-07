#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define add 0x27
#define col 16
#define lin 2

LiquidCrystal_I2C lcd(add, col, lin);

unsigned long msg_time = 0;
String msg_empt = "";

extern int base_position, elbow_position, shoulder_position, claw_position, claw_open, claw_close;

void show_angle(){
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("B:");
  lcd.print(base_position);
  
  lcd.setCursor(6, 0);
  lcd.print("E:");
  lcd.print(elbow_position);
  
  lcd.setCursor(0, 1);
  lcd.print("S:");
  lcd.print(shoulder_position);
  
  lcd.setCursor(12, 0);
  lcd.print("C:");
  if(claw_position == claw_open){
    lcd.print("Op");
  }else if(claw_position == claw_close){
    lcd.print("Cl");
  }

  lcd.setCursor(6, 1);
  lcd.print("M:");
}

void show_mess(String msg, int time){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
  msg_empt = msg;
  msg_time = millis() + time;
}

#endif