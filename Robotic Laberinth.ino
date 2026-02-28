#include <PRIZM.h>
PRIZM prizm;

void setup(){
  prizm.PrizmBegin();
  prizm.setMotorInvert(1,1);
}

void loop() {
  if(prizm.readSonicSensorCM(4) > 45){
    prizm.setMotorPowers(39,35);
  }
  else{
    prizm.setMotorPowers(0,0);
    delay(500);
    prizm.setMotorPowers(-39,35);
    delay(475);
    prizm.setMotorPowers(0,0);
    delay(500);
    if(prizm.readSonicSensorCM(4) > 45) {
      prizm.setMotorPowers(39,35);
    }
    else{
      prizm.setMotorPowers(39,-35);
      delay(475);
      prizm.setMotorPowers(0,0);
      delay(500);
      prizm.setMotorPowers(39,-35);
      delay(550);
    }
  } 
}