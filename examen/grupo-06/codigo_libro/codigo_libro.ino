// incluir librería adafruit
// permite controlar neopixeles
#include <Adafruit_NeoPixel.h>

// incluir archivos .h
// con las definiciones de las clases ColorRGB y PulsoLuz
#include "ColorRGB.h"
#include "PulsoLuz.h"

// crear variables del tipo colorRGB
ColorRGB verde(102, 255, 102);
ColorRGB amarillo(255, 200, 0);
ColorRGB morado(178, 50, 255);
ColorRGB celeste(0, 100, 255);

// agrupar estas variables de color RGB
// que acabamos de crear en el arreglo colorTiempo
ColorRGB colorTiempo[] = {
  verde,
  amarillo,
  morado,
  celeste
};

// crear arreglo con los tiempos en que cambian los colores
// se miden en milisegundos
int tiempos[] = {
  5000,
  5000,
  5000,
  5000
};

// crear una instancia de la clase PulsoLuz
PulsoLuz miPulsito;

// este define permite distinguir entre examen y debug
#define examen true
// pin arduino conectado a la tira
#define ledPin 6
// numero de leds a ocupar
#define ledNum 20

// variables que constituyen a neopixel
Adafruit_NeoPixel neoPixel(ledNum, ledPin, NEO_GRB + NEO_KHZ800);

// variable digital
// inicia en falso
bool empezar = true;
// referencia
// https://www.arduino.cc/reference/en/language/variables/utilities/sizeof/
// numeroTiempos es el tamano del arreglo tiempos
// se obtiene dividiendo el tamano en bits de tiempo
// por el tamano en bits del tiempo en la posicion 0
int numeroTiempos = sizeof(tiempos) / sizeof(tiempos[0]);
// numero entero, largo, sin signo
unsigned long inicio = 0;
// pin donde se ubica sensor tilt
int pinTilt = 4;
// variable digital
// comienza en falso
bool tilt = false;
// pin donde se ubica sensor boton
//int botonInicio = 2;
// variable digital
// comienza en falso
bool estaLevantado = false;
// variable digital
// comienza en falso
bool final = false;
// numero entero largo sin signo
unsigned long ultimoTiempo = 0;
// numero entero largo sin signo para
// resetear millis
extern volatile unsigned long timer0_millis;

void setup() {
  // serie de sucesos que ocurren una sola vez

  // si examen es verdadero, entonces 
  //serialbegin
  if (examen) {
    Serial.begin(9600);
  }
  // funcion que inicializa neopixel e inserta brillo inicial
  inicializarNeoPixel(100);
  // establece tilt como input 
  // ingresa informacion
  pinMode(pinTilt, INPUT);
  // establece boton como input
  // ingresa informacion
  //pinMode(botonInicio, INPUT_PULLUP);

  // definir valores del PulsoLuz
  // parametros son duracion en milisegundos
  // porcentaje de fadeIn y porcentaje de fadeOut
  miPulsito.definirTiempos(2000, 0.5, 0.5);
}


void loop() {

  // serie de sucesos que ocurren desde el primero al 
  // ultimo repetidas veces

  // instancia llama a clase pulsoluz
  // funcion actualizarvalor del momentoactual
  // determina valores fade y pulso en el momentoactual
  miPulsito.actualizarValor();
  // el neopixel representa el valor del 
  // momentoactual en su brillo
  // forma las pulsaciones
  neoPixel.setBrightness(miPulsito.getValorActual());

  // si el boton de inicio
  // hace que el boolean empezar
  // sea verdadero, correr lo que esta adentro
  if (!empezar) {
    empezar = true;
    inicio = millis();
  }
  if (empezar) {
    // deltaTiempo es la resta entre tiempo actual
    // y el tiempo de inicio
    unsigned long deltaTiempo = millis() - inicio;

    // si final es verdadero y deltatiempo es mayor a 
    // tiempo3, el color que demuestra el neopixel
    // corresponde al colortiempo4
    if (final && deltaTiempo > tiempos[3]) {
      Serial.println("etapa final de 20 minutos");
      definirColorNeoPixel(colorTiempo[3]);
      // si deltatiempo es mayor a cierto tiempo
      // la el valor maximo ira disminuyendo
      // hasta ser max=min y los neopixeles no tengan brillo
      if (deltaTiempo > tiempos[3] + 2000) {
        miPulsito.achatarMaximo();
        Serial.println("se apaga");
      }
    
    // sino, si deltatiempo es mayor a tiempo0 y tiempo1
    // el color que demuestra el neopixel corresponde a 
    // colortiempo2
    } else if (deltaTiempo > tiempos[0] + tiempos[1]) {
      Serial.println("Levantame");

      // bool esta levantado es verdadero siendo
      // comparable al contrario de digitalread de pintilt
      estaLevantado = !digitalRead(pinTilt);
      // si estalevantado es verdadero
      // utlimotiempo ya no vale 0, sino millis
      // y bool final es verdadero
      if (estaLevantado) {
        ultimoTiempo = millis();
        final = true;
      }

      definirColorNeoPixel(colorTiempo[2]);

    // sino, si deltatiempo es mayor a tiempos0
    // el color que demuestra el neopixel corresponde
    // a tiemposcolor1
    } else if (deltaTiempo > tiempos[0]) {
      Serial.println("Segunda alarma");
      definirColorNeoPixel(colorTiempo[1]);
    
    // sino, el color que demuestra el neopixel
    // corresponde a colortiempo0
    } else if (!final){
      definirColorNeoPixel(colorTiempo[0]);
      Serial.println("iniciamos");
    } else {
      definirColorNeoPixel(colorTiempo[3]);
    }

    estaLevantado = !digitalRead(pinTilt);
    if (estaLevantado) {
      ultimoTiempo = millis();
      final = true;
    }
  }
}
