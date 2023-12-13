#include "definicionesNeoPixel.h"
//""incluir archivos locales


const int trigger = 3;       // Pin digital 2 para el trigger del sensor
const int echo = 2;          // Pin digital 3 para el echo del sensor
const int numReadings = 10;  // Número de lecturas para el promedio móvil
int readings[numReadings];   // Arreglo para almacenar las lecturas
int indice = 0;               // indice actual en el arreglo
int total = 0;               // Suma de las lecturas


bool examen = true;

void setup() {
  Serial.begin(9600);  // Iniciamos la comunicación
  if (!examen) {
    Serial.println("configurarNeoPixel");
  }
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  apagarTodo();

  pinMode(trigger, OUTPUT);    // Pin como salida
  pinMode(echo, INPUT);        // Pin como entrada
  digitalWrite(trigger, LOW);  // Inicializamos el pin con 0
}

void loop() {

  if (sensor()) {
    animacion01();
    //animacion02();  // Si hay presencia, ejecuta la animación de neopíxeles
  }
  else {
     apagarTodo();
  }
  // Si no hay presencia, la animación se mantendrá apagada
}
