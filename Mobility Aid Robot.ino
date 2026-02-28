#include <PRIZM.h>
PRIZM prizm;

void setup() {
  prizm.PrizmBegin();

  Serial.begin(9600);
  prizm.setMotorInvert(1,1); 
  prizm.setServoSpeed(5,15);
  prizm.setServoSpeed(4,15);

  prizm.setServoPosition(5, 0);   // Servo 5 abierto
  prizm.setServoPosition(4, 180); // Servo 4 abierto
  delay(2000);
}

void loop() {
  // Cerrar garras al inicio
  prizm.setServoPosition(5, 130);
  while(abs(prizm.readServoPosition(5) - 130) > 5) {
    delay(50);
  }
  prizm.setServoPosition(4, 80);
  delay(2000);
  
  Serial.print("Distancia inicial: ");
  Serial.println(prizm.readSonicSensorCM(3));

  // Seguir recto hasta detectar obstáculo
  while(prizm.readSonicSensorCM(3) > 10) {
    int sensorFrente = prizm.readLineSensor(5);
    
    Serial.print("Frente: "); 
    Serial.print(sensorFrente); 
    
    if(sensorFrente == 0) {
      // NO line detected - keep going straight
      prizm.setMotorPowers(11, 12);
      prizm.setRedLED(LOW);
    }
    else {
      // Front sensor DETECTS black line (1) - STOP and rotate 90°
      prizm.setMotorPowers(0, 0);
      prizm.setRedLED(HIGH);
      delay(500);
      
      Serial.println("Linea detectada! Iniciando giro...");
      
      prizm.setMotorPowers(10, -10);
      delay(4000);
      
      
      // 5 lecturas consecutivas confirmadas - giro completo!
      Serial.println("Giro de 90 grados confirmado!");
      prizm.setMotorPowers(0, 0);
      delay(500);
      
      // Avanzar un poco después del giro
      prizm.setMotorPowers(11, 12);
      delay(5000);
      prizm.setMotorPowers(0, 0);
    }
    
    delay(50);  // Pequeña pausa
  }
  
  // Obstáculo detectado - detener
  Serial.println("Obstaculo detectado!");
  prizm.setMotorPowers(0, 0);
  delay(500);
  
  // Abrir garras
  prizm.setServoPosition(4, 180);
  while(abs(prizm.readServoPosition(4) - 180) > 5) {
    delay(50);
  }
  prizm.setServoPosition(5, 0);
  delay(2000);
  
  Serial.println("Ciclo completado. Esperando...");
  delay(5000);
}