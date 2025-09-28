/***********************************************************************************************************************************************
Project: Braço Robótico

Last update: 27/ 09/ 2025
***********************************************************************************************************************************************/

// configs para o display //
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define add 0x27
#define col 16
#define lin 2

LiquidCrystal_I2C lcd(add, col, lin);
/*----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------*/
// configs para os servos //
#include <Servo.h>

#define servo_base_pin 9
#define servo_elbow_pin 8
#define servo_shoulder_pin 7
#define servo_claw_pin 6

Servo base, elbow, shoulder, claw;
/*----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------*/
// configs para o controle (PS2) //
#include <PS2X_lib.h>

PS2X ps2x;

int error = 0;
byte type = 0;
byte vibrate = 0;
byte select = 0;
/*----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------*/
// limites dos servos //
const int angle_max = 170;
const int angle_min = 10;

const int claw_open = 30;
const int claw_close = 120;
/*----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------*/
// posição de início //
int base_position = 90;
int elbow_position = 50;
int shoulder_position = 70;
int claw_position = 30;
/*----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------*/
// variáveis para salvar a posição desejada //
int save_base = -1;
int save_elbow = -1;
int save_shoulder = -1;
int save_claw = -1;
/*----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------*/
// controle da exibição no display //
unsigned long msg_time = 0;
String msg_empt = "";
/*----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------*/

void show_angle(){
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("B:");
  lcd.print(base_position);
  
  lcd.setCursor(7, 0);
  lcd.print("E:");
  lcd.print(elbow_position);
  
  lcd.setCursor(0, 1);
  lcd.print("S:");
  lcd.print(shoulder_position);
  
  lcd.setCursor(7, 1);
  lcd.print("C:");
  if(claw_position == claw_open){
    lcd.print("Open");
  }else if(claw_position == claw_close){
    lcd.print("Close");
  }
}

void show_mess(String msg, int time){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
  msg_empt = msg;
  msg_time = millis() + time;
}

void setup(){
  // display //
  lcd.init();
  lcd.backlight();
  lcd.clear();
  show_angle();
  
  // Servos //
  base.attach(servo_base_pin);
  elbow.attach(servo_elbow_pin);
  shoulder.attach(servo_shoulder_pin);
  claw.attach(servo_claw_pin);

  // PS2 //
  error = ps2x.config_gamepad(13, 11, 10, 12, true, true);

  // início //
  base.write(base_position);
  elbow.write(elbow_position);
  shoulder.write(shoulder_position);
  claw.write(claw_position);
}

void loop(){
  if(error == 1) return;

  ps2x.read_gamepad(false, vibrate);

  // atualização do display //
  bool updated = false;

  // movimentação //
  if(ps2x.Button(PSB_PAD_LEFT) && base_position < angle_max){ 
  base_position++; 
  updated = true;
  }
  else if(ps2x.Button(PSB_PAD_RIGHT) && base_position > angle_min){ 
  base_position--; 
  updated = true;
  }

  if(ps2x.Button(PSB_GREEN) && elbow_position < angle_max){ 
  elbow_position++; 
  updated = true;
  }
  else if(ps2x.Button(PSB_BLUE) && elbow_position > angle_min){ 
  elbow_position--; 
  updated = true;
  }

  if(ps2x.Button(PSB_PAD_UP) && shoulder_position < angle_max){ 
  shoulder_position++; 
  updated = true;
  }
  else if(ps2x.Button(PSB_PAD_DOWN) && shoulder_position > angle_min){ 
  shoulder_position--; 
  updated = true;
  }

  if(ps2x.Button(PSB_R1)){
    claw_position = claw_open;
    updated = true;
  }
  if(ps2x.Button(PSB_R2)){
    claw_position = claw_close;
    updated = true;
  }

  base.write(base_position);
  elbow.write(elbow_position);
  shoulder.write(shoulder_position);
  claw.write(claw_position);

  // salvando posição desejada //
  if(ps2x.Button(PSB_RED)){
    save_base = base_position;
    save_elbow = elbow_position;
    save_shoulder = shoulder_position;
    save_claw = claw_position;

    show_mess("Salvo", 2000);
  }

  // indo para posição desejada //
  if(ps2x.Button(PSB_PINK)){
    if(save_base != -1 && save_elbow != -1 && save_shoulder != -1 && save_claw != -1){
      show_mess("Indo p/ destino", 1000);

      base_position = save_base;
      elbow_position = save_elbow;
      shoulder_position = save_shoulder;
      claw_position = save_claw;

      base.write(base_position);
      elbow.write(elbow_position);
      shoulder.write(shoulder_position);
      claw.write(claw_position);
    }
  }

  if(updated && msg_empt == ""){
    show_angle();
  }

  if(msg_empt != "" && millis() > msg_time){
    msg_empt = "";
    show_angle();
  }

} //end loop
