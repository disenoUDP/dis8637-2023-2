# examen grupo-06

## integrantes

* arellano palomino, camila ignacia
* barrenechea castillo, jacinta
* cuevas calderón, matías

## descripción

Objeto que tiene como función crear una rutina que propicie un buen descanso e higienizar el sueño.

## imágenes

## código

### codigo_libro.ino

```cpp
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
```

### ColorRGB.cpp

```cpp
#include "Arduino.h"
#include "ColorRGB.h"

ColorRGB::ColorRGB(uint8_t r, uint8_t g, uint8_t b) {
  _r = r;
  _g = g;
  _b = b;
}

uint8_t ColorRGB::getR() {
  return _r;
}

uint8_t ColorRGB::getG() {
  return _g;
}

uint8_t ColorRGB::getB() {
  return _b;
}
```

### ColorRGB.h

```cpp
#ifndef ColorRGB_H
#define ColorRGB_H

#include "Arduino.h"

class ColorRGB {
public:
  ColorRGB(uint8_t r, uint8_t g, uint8_t b);
  uint8_t getR();
  uint8_t getG();
  uint8_t getB();
private:
  uint8_t _r;
  uint8_t _g;
  uint8_t _b;
};

#endif
```

### luces.ino

```cpp
void inicializarNeoPixel(int brilloInicial) {
  // inicia la tira
  neoPixel.begin();
  // configura el brillo inicial
  // el rango es entre 0 - 255
  neoPixel.setBrightness(brilloInicial);
}

void definirColorNeoPixel(ColorRGB nuevoColor) {
  neoPixel.clear();
  neoPixel.fill(
    neoPixel.Color(
      nuevoColor.getR(),
      nuevoColor.getG(),
      nuevoColor.getB()));
  neoPixel.show();
}

// envolvente ADSR?
// de hecho creo que basta con ASR
void definirCurva(unsigned long tiempoPulso, float tiempoFade) {
}
```

### PulsoLuz.cpp

```cpp
#include "Arduino.h"
#include "PulsoLuz.h"

// definir lo que hace el constructor
PulsoLuz::PulsoLuz() {
  _valorMin = 0;
  _valorMax = 255;
  _valorActual = _valorMin;
  _tiempoInicio = millis();
  _momentoAchatado = millis();
}

// tiempoPulso define cuanto tiempo dura el evento entre prender y apagar
// tiempoFade es un porcentaje de cuanto de ese tiempo total
// se ocupa en el fadeIn y en el fadeOut
// entonces tiempoPulso es el 100% del tiempo
// si hay un tiempo que es tiempoPrendido
// entonces tiempoPulso = tiempoFade + tiempoPrendido + tiempoFade
// resumiendo, tiempoPulso = tiempoPrendido + 2 * tiempoFade
void PulsoLuz::definirTiempos(unsigned long tiempoDuracion, float fadeIn, float fadeOut) {
  _tiempoDuracion = tiempoDuracion;
  _porcentajeFadeIn = fadeIn;
  _porcentajeFadeOut = fadeOut;
  // _tiempoFadeIn = _tiempoDuracion * _porcentajeFadeIn;
  // _tiempoFadeOut = _tiempoDuracion * _porcentajeFadeOut;
  _momentoFadeIn = _tiempoDuracion * _porcentajeFadeIn;
  _momentoFadeOut = _tiempoDuracion * (float(1.0) - _porcentajeFadeOut);
}

void PulsoLuz::actualizarValor() {

  // usar funcion modulo (%) para encontrar
  // el resto de la division entre millis() y _tiempoDuracion
  unsigned long momentoActual = millis() % _tiempoDuracion;

  // si estamos en un momento entre 0 y _tiempoFadeIn
  if (momentoActual < _momentoFadeIn) {
    _valorActual = _valorMax * (float(momentoActual) / float(_momentoFadeIn));
  }
  // si estamos en un momento entre 0 y _tiempoFadeOut
  else if (momentoActual > _momentoFadeOut) {
    _valorActual = _valorMax * (1.0 - float(momentoActual - _momentoFadeOut) / float(_momentoFadeOut));
    // _valorActual = _valorMax * (float(momentoActual -) / float(_tiempoDuracion - _tiempoFadeOut));
  } else {
    _valorActual = _valorMax;
  }
}

void PulsoLuz::achatarMaximo(){
  if (millis() - _momentoAchatado > 400){
    _valorMax = _valorMax - 1;
    _momentoAchatado = millis();
  }

  if (_valorMax < _valorMin) {
    _valorMax = _valorMin;
  }
}

int PulsoLuz::getValorActual() {
  return _valorActual;
}

unsigned long PulsoLuz::getMomentoFadeIn() {
  return _momentoFadeIn;
}

unsigned long PulsoLuz::getMomentoFadeOut() {
  return _momentoFadeOut;
}
```

### PulsoLuz.h

```cpp
#ifndef PulsoLuz_H
#define PulsoLuz_H

#include "Arduino.h"

// declarar la clase PulsoLuz
// que va a tener metodos (funciones)
// y va a tener parametros (variables)
// y algunas van a ser publicas que podemos interactuar
// y otras son privadas, que son de uso interno
class PulsoLuz {
public:
  // declarar constructor de la clase PulsoLuz
  // que necesita dos valores, min y max
  PulsoLuz();
  void definirTiempos(unsigned long tiempoDuracion, float fadeIn, float fadeOut);
  void actualizarValor();
  // declarar funcion para obtener valor actual
  // es tipo int porque retorna un numero entero
  int getValorActual();
  unsigned long getMomentoFadeIn();
  unsigned long getMomentoFadeOut();
  void achatarMaximo();


private:
  int _valorMin;
  int _valorMax;
  int _valorActual;
  float _porcentajeFadeIn;
  float _porcentajeFadeOut;
  unsigned long _tiempoFadeIn;
  unsigned long _tiempoFadeOut;
  unsigned long _tiempoDuracion;
  unsigned long _tiempoInicio;
  unsigned long _momentoFadeIn;
  unsigned long _momentoFadeOut;
  unsigned long _momentoAchatado;
};

#endif
```
