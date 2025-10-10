#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h> //lib do I2C
#include <LiquidCrystal_I2C.h> //lib do display
#include "bl_HC05.h" //lib p/ o bluetooth

//chamo essas variaveis do controle.h para o display.h
extern int base_position, elbow_position, shoulder_position, claw_position, claw_open, claw_close;

//configs do display
const uint8_t adds = 0x27, cols = 16, rows = 2; 

//objeto p/ o display
LiquidCrystal_I2C lcd(adds, cols, rows);

//variaveis para o tempo e mensagem
unsigned long msg_time = 0;
String msg_empt = "";

void show_angle(); //prototipando a funçao show_angle para usar em display_init()

//configs iniciais do display
void display_init(){
  lcd.init(); //liga o display
  lcd.backlight(); //iluminaçao do display
  lcd.clear(); //limpa o conteudo

  show_angle();
}

//funçao para mostrar os angulos dos servos
void show_angle(){
  lcd.clear();
  
  lcd.setCursor(0, 0); //defino a posiçao do cursor
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
}

//funçao para o tempo de mostragem da mensagem
void show_mess(String msg, int time){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
  msg_empt = msg;
  msg_time = millis() + time;
}

#endif