#include <PULSE.h>
PULSE pulse;

// Las constantes sirven para que sea mas facil editar el codigo
// Tiempos:
const int tiempo_freno = 1000; // Tiempo que el robot esta quieto esperando siguiente comando.
const int tiempo_cruce = 4500; // Tiempo que el robot dura en cruzar el puente. EDITAAAAAR!!!!!!!!!!!!!
const int tiempo_doblar = 1100; // Tiempo que dura el robot en doblar 90 grados. Este tiempo hay que cambiarlo bastante, depende de la bateria!!!!!!!!!!!! EDITAAAAAR!!!!!!!!!!!!!
const int tiempo_doblarderecha = 1275; //(1300 150) con bateria media bateria (1400) ULTIMA (1375)
const int tiempo_giro = 2350; // Tiempo que dura el robot en girar 180 grados. (2300 150) con bateria media bateria (2300) ULTIMA (2350)
const int tiempo_avanzar = 4500; // Tiempo que dura el robot avanzando en linea recta sin cruzar el puente y sin detectar nada. EDITAAAAAR!!!!!!!!!!!!!
const int tiempo_horquillas = 500; // Tiempo que dura el robot en insertar y sacar las horquillas y volver a su posicion original. Todo este es el mismo porque se debe mantener la posicion del robot siempre igual para que no se descalibre. EDITAAAAAR!!!!!!!!!!!!!

// Angulos de las horquillas (Servo):
const int angulo_horquillas_horizontales = 61; // Hay que probar los angulos, a ver con cual se obtiene la inclinacion que necesitamos para que las horquillas entren en la ranura del puente. EDITAAAAAR!!!!!!!!!!!!!
const int angulo_horquillas_verticales = 145; // Hay que probar los angulos, a ver con cual se obtiene la inclinacion que necesitamos para que las horquillas queden vertical completamente. EDITAAAAAR!!!!!!!!!!!!!

// Potencia de los motores DC:
const int potencia_normal = 50; // Esta es la velocidad con la que van a girar las ruedas, es la que hemos usado siempre.
const int potencia_lenta = 25; // Esta es la velocidad con la que van a girar las ruedas mientras el robot busca el hueco para colocar el puente, es importante que sea baja.
const int freno = 0; // Potencia nula.

// Estas son funciones para que sea más fácil editar todo, hay muchas cosas repetitivas entonces para que el código no se vea tan grande también se hizo esto.
void detectarLinea() {
  while (pulse.readLineSensor(2) == 0) {
    pulse.setRedLED(LOW);
    pulse.setYellowLED(HIGH);
    pulse.setMotorPowers(potencia_normal,potencia_normal);
    delay(50);
  }
  pulse.setRedLED(HIGH);
  pulse.setYellowLED(LOW);
  pulse.setMotorPowers(freno,freno);
}

void doblarIzquierda(){ // El robot hace un giro de 90 grados a la izquierda (Hay que revisar en que direccion gira y si no cambiar signos jajaja).
  // Doblar
  pulse.setMotorPowers(-potencia_normal, potencia_normal); // Estos signos!!!
  delay(tiempo_doblar);
  // Freno para avanzar
  pulse.setMotorPowers(freno,freno);
  delay(tiempo_freno);
}

void doblarDerecha(){ // El robot hace un giro de 90 grados a la derecha (Hay que revisar en que direccion gira y si no cambiar signos jajaja) (Opuesto al anterior).
  // Doblar
  pulse.setMotorPowers(potencia_normal,-potencia_normal); // Estos signos!!!
  delay(tiempo_doblarderecha);
  // Freno para avanzar
  pulse.setMotorPowers(freno,freno);
  delay(tiempo_freno);
}

void giro180(){ // El robot hace un giro de 180 grados.
  // Doblar
  pulse.setMotorPowers(-potencia_normal,potencia_normal); // No hace falta editarlos
  delay(tiempo_giro);
  // Freno para avanzar
  pulse.setMotorPowers(freno,freno);
  delay(tiempo_freno);
}

void avanzar(){ // Esta es la parte donde avanza en linea recta pero no en el puente.
  // Avanzar en línea recta 
  pulse.setMotorPowers(potencia_normal,potencia_normal);
  delay(tiempo_avanzar);
  // Freno para doblar
  pulse.setMotorPowers(freno,freno);
  delay(tiempo_freno);
}

void cruzarPuente(){ // Esta es la parte donde avanza en linea recta cruzando el puente.
  // Cruzar río
  pulse.setMotorPowers(potencia_normal,potencia_normal);
  delay(tiempo_cruce);
  // Frenar por un tiempo
  pulse.setMotorPowers(freno,freno);
  delay(tiempo_freno);
}

void colocarPuente(){ // En esta seccion baja el puente y hace los ajustes necearios para seguir avanzando.
  // Primer bajado del puente
  pulse.setServoPosition(3,angulo_horquillas_horizontales);
  delay(tiempo_freno);
  // Reversa para sacar las paletas
  pulse.setMotorPowers(-potencia_normal,-potencia_normal);
  delay(tiempo_horquillas);
  // Frenar por un tiempo
  pulse.setMotorPowers(freno,freno);
  delay(tiempo_freno);
  // Primera subida del levantacargas
  pulse.setServoPosition(3,angulo_horquillas_verticales);
  delay(tiempo_freno);
  // Avanzar a posicion original
  pulse.setMotorPowers(potencia_normal,potencia_normal);
  delay(tiempo_horquillas);
  // Frenar por un tiempo
  pulse.setMotorPowers(freno,freno);
  delay(tiempo_freno);
}

void levantarPuente(){ // En esta seccion se levanta el puente y hace los ajustes necesarios como giros y asi para seguir avanzando.
  giro180();
 // Reversa para sacar las paletas
  pulse.setMotorPowers(-potencia_normal,-potencia_normal);
  delay(tiempo_horquillas);
  // Frenar por un tiempo
  pulse.setMotorPowers(freno,freno);
  delay(tiempo_freno);
  // Bajado para preparar levantamiento del puente
  pulse.setServoPosition(3,angulo_horquillas_horizontales);
  delay(tiempo_freno);
  // Avanzar para insertar las paletas
  detectarLinea();
  // Primera levantada del puente
  pulse.setServoPosition(3,angulo_horquillas_verticales);
  delay(tiempo_freno);
  // Reversa para volver a posicion
  pulse.setMotorPowers(-potencia_normal,-potencia_normal);
  delay(tiempo_horquillas);
  // Frenar por un tiempo
  pulse.setMotorPowers(freno,freno);
  delay(tiempo_freno);
}

// Aquí es donde el robot empieza a funcionar
void setup() {
  pulse.PulseBegin();
  pulse.setServoSpeed(3,25);
  pulse.setMotorInvert(1,1);
}

void loop() {

  detectarLinea();
  
  doblarIzquierda();

  cruzarPuente();

  detectarLinea();

  levantarPuente();

  doblarDerecha();

  detectarLinea();

  doblarIzquierda();

  detectarLinea();

  colocarPuente();

  cruzarPuente();

  detectarLinea();

  pulse.PulseEnd();
}
