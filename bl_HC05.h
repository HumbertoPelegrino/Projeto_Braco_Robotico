#ifndef BL_HC05_H
#define BL_HC05_H

#include "controle.h"
extern bool updated = false;
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

//#include "display.h"
/*--------------------------------------------------------------------------------------------------------------------------------------------*/

#include <SoftwareSerial.h>
SoftwareSerial BT(3, 2); //RX, TX

char c; //variavel para receber os comandos do celular

void bl_setup() {
  BT.begin(9600); //comunicaçao do modulo
  Serial.println("Procurando Bluetooth ...");
}

void bl_cmd() {
  if (BT.available()) {
    c = BT.read();

    //para nao printar dois espaços
    if(c != '\r' && c != '\n'){
      Serial.print("Recebido: ");
      Serial.println(c);
    }

    if(c == 'L' && base_position < angle_max){
      base_position += 5;
      updated = true;
    }
    if(c == 'R' && base_position > angle_min){
      base_position -= 5;
      updated = true;
    }
    if(c == 'F' && elbow_position < angle_max){
      elbow_position += 5;
      updated = true;
    }
    if(c == 'B' && elbow_position > angle_min){
      elbow_position -= 5;
      updated = true;
    }
    if(c == 'U' && shoulder_position < angle_max){
      shoulder_position += 5;
      updated = true;
    }
    if(c == 'D' && shoulder_position > angle_min){
      shoulder_position -= 5;
      updated = true;
    }
    if(c == 'O'){
      claw_position = claw_open;
      updated = true;
    }
    if(c == 'C'){
      claw_position = claw_close;
      updated = true;
    }

    base.write(base_position);
    elbow.write(elbow_position);
    shoulder.write(shoulder_position);
    claw.write(claw_position);

    if(updated && msg_empt == ""){
    show_angle();
    }
  }

  //se precisar testar o bluetooth
  /*if (Serial.available() > 0) {
    BT.write(Serial.read());
  }*/
}

#endif