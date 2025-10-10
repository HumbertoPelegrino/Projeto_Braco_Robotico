#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <SoftwareSerial.h>
SoftwareSerial BT(3, 2); //RX, TX

char c; //variavel para receber os comandos do celular

//açoes possiveis
enum Actions{
  Save,
  GoSav,
  BaseLef,
  BaseRig,
  ElbUp,
  ElbDow,
  ShoFow,
  ShoBac,
  ClaOp,
  ClaClo
};

Actions a;

void bl_connection() {
  BT.begin(9600); //comunicaçao do modulo
  Serial.println("Bluetooth ligado!");
}

void bl_print() {
  if (BT.available()) {
    c = BT.read();

    //para nao printar dois espaços
    if(c != '\r' && c != '\n'){
      Serial.print("Recebido: ");
      Serial.println(c);
      
      //fazendo as funçoes de acordo com o comando do celular
      switch(c){
        case 1: a = Save; break;
        case 2: a = GoSav; break;
        case 3: a = BaseLef; break;
        case 4: a = BaseRig; break;
        case 5: a = ElbUp; break;
        case 6: a = ElbDow; break;
        case 7: a = ShoFow; break;
        case 8: a = ShoBac; break;
        case 9: a = ClaOp; break;
        case 10: a = ClaClo; break;
      }
    }
  }

  //descomentar para testar o bluetooth
  /*if (Serial.available() > 0) {
    BT.write(Serial.read());
  }*/
}

#endif