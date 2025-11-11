#ifndef DISPLAY_H
#define DISPLAY_H

// descomentar se precisar achar o endereço do seu display
/*#include <Wire.h>
#define wire Wire

void I2C_setup(){
  WIRE.begin();

  //se for esp comenta
  while(!Serial){
    delay(10);
  }
}

void I2C_loop(){
  byte error, adds;

  for(adds = 1; adds < 127; adds ++){
    wire.beginTransmission();
    error = wire.endTransmission();

    if(error == 0){
      Serial.print("Endereço:");
      if(adds < 16){
        Serial.print("0");
        Serial.print(adds, HEX);
      }
    }
  }
}*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#include <LiquidCrystal_I2C.h> //lib do display

//configs do display
const uint8_t adds = 0x3F; //endereço I2C
const uint8_t cols = 19; //20 colunas
const uint8_t rows = 3; //4 linhas

// objeto p/ o display
LiquidCrystal_I2C lcd(adds, cols, rows);
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

//variaveis para o tempo e mensagem
unsigned long msg_time = 0;
String msg_empt = "";
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

//chamo essas variaveis do controle.h para o display.h
extern int base_position, elbow_position, shoulder_position, claw_position, claw_open, claw_close;
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

//funçao para mostrar os angulos dos servos
void show_angle(){
  lcd.clear();
  
  lcd.setCursor(0, 0); //defino a posiçao do cursor
  lcd.print("B:");
  lcd.print(base_position);
  
  lcd.setCursor(6, 0);
  lcd.print("E:");
  lcd.print(elbow_position);
  
  lcd.setCursor(12, 0);
  lcd.print("S:");
  lcd.print(shoulder_position);
  
  lcd.setCursor(0, 1);
  lcd.print("C:");
  if(claw_position == claw_open){
    lcd.print("Op");
  }else if(claw_position == claw_close){
    lcd.print("Cl");
  }
}
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

//configs iniciais do display
void display_setup(){
  lcd.init(); //liga o display
  lcd.backlight(); //iluminaçao do display
  lcd.clear(); //limpa o conteudo

  show_angle();
}
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

//funçao para o tempo de mostragem da mensagem
void show_mess(String msg, int time){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
  msg_empt = msg;
  msg_time = millis() + time;
}

#endif