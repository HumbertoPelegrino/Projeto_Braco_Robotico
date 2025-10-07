#ifndef CONTROLE_H
#define CONTROLE_H

#include <PS2X_lib.h>
#include <Servo.h>
#include "display.h"

#define servo_base_pin 9
#define servo_elbow_pin 8
#define servo_shoulder_pin 7
#define servo_claw_pin 6

Servo base, elbow, shoulder, claw;

PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;
byte select = 0;

const int angle_max = 170;
const int angle_min = 10;
int claw_open = 30;
int claw_close = 120;

int base_position = 90;
int elbow_position = 50;
int shoulder_position = 70;
int claw_position = 30;

int save_base = -1;
int save_elbow = -1;
int save_shoulder = -1;
int save_claw = -1;

void save_position();
void go_saveposition();

void movement_PS2(){
  if(error == 1) return;

  ps2x.read_gamepad(false, vibrate);

  bool updated = false;

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

  save_position();
  go_saveposition();

  if(updated && msg_empt == ""){
    show_angle();
  }

  if(msg_empt != "" && millis() > msg_time){
    msg_empt = "";
    show_angle();
  }
}

void save_position(){
  if(ps2x.Button(PSB_RED)){
    save_base = base_position;
    save_elbow = elbow_position;
    save_shoulder = shoulder_position;
    save_claw = claw_position;

    show_mess("Salvo", 2000);
  }
}

void go_saveposition(){
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
}

#endif