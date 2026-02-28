#include <PULSE.h>
PULSE pulse;

// Las constantes sirven para que sea mas facil editar el codigo
// Tiempos:
const int tiempo_rotacion_base = 5000;
const int tiempo_freno = 500;

// Angulos de los servos (Servo):
const int angulo_abierto_garra = 0; 
const int angulo_cerrado_garra = 30; 
const int angulo_bajada_brazo = 0; 
const int angulo_subida_brazo = 90; 

// Potencia de los motores (DC):
const int potencia_normal = 25; // Esta es la velocidad con la que gira la base
const int freno = 0;

// Funciones
void giroBase(){ // Giro en una direccion del brazo entero (Motor DC)
  pulse.setMotorPower(potencia_normal);
  delay(tiempo_rotacion_base);
  pulse.setMotorPower(freno);
  delay(tiempo_freno);
}

void giroBaseR(){ // Giro en la otra direccion del brazo entero (Motor DC)
  pulse.setMotorPower(-potencia_normal); // No hace falta editarlos
  delay(tiempo_rotacion_base);
  pulse.setMotorPower(freno);
  delay(tiempo_freno);
}

void bajadaBrazo(){ 
  pulse.setServoPosition(2,angulo_bajada_brazo);
  delay(tiempo_freno);
}

void subidaBrazo(){ 
  pulse.setServoPosition(2,angulo_subida_brazo);
  delay(tiempo_freno);
}

void aperturaGarra(){ 
  pulse.setServoPosition(3,angulo_abierto_garra);
  delay(tiempo_freno);
}

void cerradoGarra(){ 
  pulse.setServoPosition(3,angulo_cerrado_garra);
  delay(tiempo_freno);
}

// Aquí es donde el robot empieza a funcionar
void setup() {
  pulse.PulseBegin();
  pulse.setServoSpeed(2,20);
  pulse.setServoSpeed(3,20);
}

void loop() {
  aperturaGarra();
  bajadaBrazo();
  cerradoGarra();
  subidaBrazo();
  giroBase();
  bajadaBrazo();
  aperturaGarra();
  subidaBrazo();
  cerradoGarra();
  giroBaseR();

  delay(1500)
}
