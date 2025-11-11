#include "display.h"
#include "controle.h"
#include "bl_HC05.h"

void setup(){
  Serial.begin(9600);

  bl_setup();
  
  display_setup();
  
  control_setup();
}

void loop(){
  bl_cmd();
  
  movement_PS2();
}