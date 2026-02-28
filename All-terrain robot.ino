#include <PRIZM.h>
PRIZM prizm;

void setup() {
  prizm.PrizmBegin();

  Serial.begin(9600);
  prizm.setServoSpeed(5, 25);
  prizm.setServoSpeed(4, 20);
  prizm.setMotorInvert(1, 1);
}

void loop() {
  // Preparar: brazo arriba, garra abierta
  prizm.setServoPosition(5, 10);
  delay(2000);
  prizm.setServoPosition(4, 10);
  delay(2000);

  // Avanzar por 2 segundos inicial
  prizm.setMotorPowers(-26, -28);
  delay(3000);

  // Seguir avanzando MIENTRAS revisa constantemente
  int distancia;
  int iteracion;
  while(true) {
    distancia = prizm.readSonicSensorCM(5);
    Serial.println(distancia); 
    
    if(distancia > 0 && distancia <= 12) {
      iteracion++;
      
      // Necesita 3 lecturas consecutivas para confirmar
      if(iteracion >= 3) {
        break;
      }
    }
    else {
      iteracion = 0;  // Reinicia si no detecta
    }
    delay(25);  // Revisa cada 50ms
  }

  // Frenar (detectó la bola)
  prizm.setMotorPowers(0, 0);
  delay(1000);
  
  // Bajar brazo
  prizm.setServoPosition(5, 105);
  delay(3000);
  
  // Cerrar garra
  prizm.setServoPosition(4, 110);
  delay(2000);
  
  // Subir brazo
  prizm.setServoPosition(5, 10);
  delay(3000);
  
  // Avanzar hacia la base mientras busca línea
  prizm.setMotorPowers(21, 25);
  
  int lecturaLinea;
  int contador = 0;
  
  while(true) {
    
    lecturaLinea = prizm.readLineSensor(3);
    Serial.println(lecturaLinea); 
    // Solo cuenta si detecta línea
    if(lecturaLinea == 1) {
      contador++;
      
      // Necesita 3 lecturas consecutivas para confirmar
      if(contador >= 30) {
        break;
      }
    }
    else {
      contador = 0;  // Reinicia si no detecta
    }
    
    delay(100);
  }
  
  // Frenar en la base
  prizm.setMotorPowers(0, 0);
  delay(1000);
  
  // Soltar bola
  prizm.setServoPosition(4, 10);
  delay(2000);
  
}