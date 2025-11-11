#ifndef CONTROLE_H
#define CONTROLE_H

#include "display.h" // chamo essa lib para mostrar os angulos
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#include <PS2X_lib.h> //lib do controle PS2
//configs para o controle
PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;
byte select = 0;
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#include <Servo.h> // lib dos servos motores

//objeto para cada servo
Servo base, elbow, shoulder, claw;
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

// definindo os pinos
#define servo_base_pin 9
#define servo_elbow_pin 8
#define servo_shoulder_pin 7
#define servo_claw_pin 6

//limitando os angulos dos servos
const uint8_t angle_max = 170;
const uint8_t angle_min = 10;
int claw_open = 30;
int claw_close = 120;

//posiçoes de cada servo
int base_position = 90;
int elbow_position = 70;
int shoulder_position = 15;
int claw_position = claw_open;

//variaveis para armazenar as posiçoes salvas
int save_base1 = -1, save_elbow1 = -1, save_shoulder1 = -1, save_claw1 = -1;
int save_base2 = -2, save_elbow2 = -2, save_shoulder2 = -2, save_claw2 = -2;
int save_base3 = -3, save_elbow3 = -3, save_shoulder3 = -3, save_claw3 = -3;

void save_position1();
void go_saveposition1();

void save_position2();
void go_saveposition2();

void save_position3();
void go_saveposition3();

void control_setup(){
  base.attach(servo_base_pin);
  elbow.attach(servo_elbow_pin);
  shoulder.attach(servo_shoulder_pin);
  claw.attach(servo_claw_pin);

  error = ps2x.config_gamepad(13, 11, 10, 12, true, true);

  base.write(base_position);
  elbow.write(elbow_position);
  shoulder.write(shoulder_position);
  claw.write(claw_position);
}

//movimentaçao
void movement_PS2(){
  if(error == 1) return; //retorna se o controle nao funcionar

  ps2x.read_gamepad(false, vibrate); //vibraçao do controle

  bool updated = false; //variavel para atualizar os estados dos servo

  //if (msg_empt != "") return; //teste do problema com a velocidade depois da

  //base
  if(ps2x.Button(PSB_PAD_LEFT) && base_position < angle_max){ 
  base_position++; //indo de grau em grau
  updated = true;
  }
  else if(ps2x.Button(PSB_PAD_RIGHT) && base_position > angle_min){ 
  base_position--; 
  updated = true;
  }

  //cotovelos
  if(ps2x.Button(PSB_GREEN) && elbow_position < angle_max){ 
  elbow_position++; 
  updated = true;
  }
  else if(ps2x.Button(PSB_BLUE) && elbow_position > angle_min){ 
  elbow_position--; 
  updated = true;
  }

  //ombros
  if(ps2x.Button(PSB_PAD_UP) && shoulder_position < angle_max){ 
  shoulder_position++; 
  updated = true;
  }
  else if(ps2x.Button(PSB_PAD_DOWN) && shoulder_position > angle_min){ 
  shoulder_position--; 
  updated = true;
  }

  //garra
  if(ps2x.ButtonPressed(PSB_R1)){
    claw_position = claw_open;
    updated = true;
  }
  if(ps2x.ButtonPressed(PSB_R2)){
    claw_position = claw_close;
    updated = true;
  }

  //definindo as posiçoes
  base.write(base_position);
  elbow.write(elbow_position);
  shoulder.write(shoulder_position);
  claw.write(claw_position);

  save_position1();
  go_saveposition1();

  save_position2();
  go_saveposition2();
  
  save_position3();
  go_saveposition3();

  //se atualiza e nao tem mensagem entao fica mostrando os novos angulos
  if(updated && msg_empt == ""){
    show_angle();
  }

  //depois que o millis passar o tempo determinado, volta a mostrar os angulos
  if(msg_empt != "" && millis() > msg_time){
    msg_empt = "";
    show_angle();
  }
}

//funçao para salvar as posiçoes
void save_position1(){
  if(ps2x.ButtonPressed(PSB_RED)){
    save_base1 = base_position;
    save_elbow1 = elbow_position;
    save_shoulder1 = shoulder_position;
    save_claw1 = claw_position;

    show_mess("Salvo1", 2000);

    delay(1000);
  }
}

void save_position2(){
  if(ps2x.ButtonPressed(PSB_L1)){
    save_base2 = base_position;
    save_elbow2 = elbow_position;
    save_shoulder2 = shoulder_position;
    save_claw2 = claw_position;

    show_mess("Salvo2", 2000);

    delay(1000);
  }
}

void save_position3(){
  if(ps2x.ButtonPressed(PSB_L3)){
    save_base3 = base_position;
    save_elbow3 = elbow_position;
    save_shoulder3 = shoulder_position;
    save_claw3 = claw_position;

    show_mess("Salvo3", 2000);

    delay(1000);
  }
}

//funçao para ir pra posiçao salva
void go_saveposition1(){
  if(ps2x.ButtonPressed(PSB_PINK)){
    if(save_base1 != -1 && save_elbow1 != -1 && save_shoulder1 != -1 && save_claw1 != -1){
      show_mess("Indo p/ destino1", 1000);

      base_position = save_base1;
      elbow_position = save_elbow1;
      shoulder_position = save_shoulder1;
      claw_position = save_claw1;

      base.write(base_position);
      elbow.write(elbow_position);
      shoulder.write(shoulder_position);
      claw.write(claw_position);

      delay(1000);
    }
  }
}

void go_saveposition2(){
  if(ps2x.ButtonPressed(PSB_L2)){
    if(save_base1 != -2 && save_elbow1 != -2 && save_shoulder1 != -2 && save_claw1 != -2){
      show_mess("Indo p/ destino2", 1000);

      base_position = save_base2;
      elbow_position = save_elbow2;
      shoulder_position = save_shoulder2;
      claw_position = save_claw2;

      base.write(base_position);
      elbow.write(elbow_position);
      shoulder.write(shoulder_position);
      claw.write(claw_position);

      delay(1000);
    }
  }
}

void go_saveposition3(){
  if(ps2x.ButtonPressed(PSB_R3)){
    if(save_base1 != -3 && save_elbow1 != -3 && save_shoulder1 != -3 && save_claw1 != -3){
      show_mess("Indo p/ destino3", 1000);

      base_position = save_base3;
      elbow_position = save_elbow3;
      shoulder_position = save_shoulder3;
      claw_position = save_claw3;

      base.write(base_position);
      elbow.write(elbow_position);
      shoulder.write(shoulder_position);
      claw.write(claw_position);

      delay(1000);
    }
  }
}

#endif