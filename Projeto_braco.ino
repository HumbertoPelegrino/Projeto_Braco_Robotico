/***********************************************************************************************************************************************
Project: Braço Robótico

Last update: 06 / 10 / 2025
***********************************************************************************************************************************************/

/*----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------*/
#include "display.h"
#include "controle.h"
#include "bluetooth.h"
/*----------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------*/

void setup(){
  Serial.begin(9600);

  // Bluetooth //
  
  
  // Display //
  lcd.init();
  lcd.backlight();
  lcd.clear();
  show_angle();
  
  // Servos -> Pinos //
  base.attach(servo_base_pin);
  elbow.attach(servo_elbow_pin);
  shoulder.attach(servo_shoulder_pin);
  claw.attach(servo_claw_pin);

  // Verifica PS2 //
  error = ps2x.config_gamepad(13, 11, 10, 12, true, true);

  // Posições iniciais //
  base.write(base_position);
  elbow.write(elbow_position);
  shoulder.write(shoulder_position);
  claw.write(claw_position);
}

void loop(){
  // Movimentação por controle //
  movement_PS2();
}
