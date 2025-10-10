#include "display.h"
#include "controle.h"
#include "bl_HC05.h"

void setup(){
  Serial.begin(9600);

  bl_connection();
  
  display_init();
  
  control_init();
}

void loop(){
  bl_print();
  
  movement_PS2();
}
