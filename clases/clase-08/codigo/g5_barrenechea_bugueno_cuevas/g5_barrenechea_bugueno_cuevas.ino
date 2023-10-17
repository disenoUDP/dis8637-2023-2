// sectorizar posicion con sensor ultrasónico

// definir numero de pins
const int trigPin = 9;
const int echoPin = 10;

// definir variables
long duracion;
double distancia;
double distanciaAnterior = 0;

// variables de valores minimo y maximo
// empezamos con valores muy errados
int valorMin = 10000;
int valorMax = 0;

//definimos sectores
float sector[4] = { 0, 0, 0, 0 };

int rangoIgnorar = 1500;

bool debug = true;

//requerimientos para neopixel

// Required for 16 MHz Adafruit Trinket
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
// Arduino pin that connects to NeoPixel
#define ledPin 6
// The number of LEDs (pixels) on NeoPixel
#define ledNum 60

Adafruit_NeoPixel neoPixel(ledNum, ledPin, NEO_GRB + NEO_KHZ800);

int pix;



void setup() {

  // iniciamos la comunicacion serial
  Serial.begin(9600);  // iniciailzamos la comunicacion

  // definimos funciones de los pines
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // INITIALIZE NeoPixel strip object (REQUIRED)
  neoPixel.begin();
  neoPixel.show();
  neoPixel.setBrightness(255);
}

void loop() {

  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
  neoPixel.clear();

  //actualizar valor de distancia
  int distanciaNueva = medirDistancia();
  // int distancia = medirDistancia();

  if(distanciaNueva < 2000){
    distancia = distanciaNueva;
  }
  else{ 
    (distancia = 1000); }

  // if (rangoApto(distanciaAnterior, distanciaNueva)) {
  //   distanciaAnterior = distancia;
  //   distancia = distanciaNueva;
  // }
  // actualizar valorMin
  if (distancia < valorMin) {
    valorMin = distancia;
  }
  // actualizar valorMax
  if (distancia > valorMax) {
    valorMax = distancia;
  }

  actualizarSector();


  // imprimir en consola el momento del sensor
  if (distancia <= sector[3]) {
    Serial.println("arriba");

    // put your main code here, to run repeatedly:

    // los pixeles van aumentando cada 1
    pix++;
    // hace más fluida la animación, es posibe crear un for o un if si se quiere
    pix %= ledNum;
    //color
    neoPixel.setPixelColor(pix, 0, 255, 0);
    // muestra la info de color y de brillo
    neoPixel.show();
    delay(30);
    //pixeles apagados
    neoPixel.setPixelColor(pix, 0, 0, 0);

    // como hago para hacer que no sea solo 1 pin el que se prende, sino 2, 3, 5 ??????
  }

  else if (distancia <= sector[2]) {
    Serial.println("medio");


    // turn on all pixels to red at the same time for two seconds
    for (int pixel = 0; pixel < ledNum; pixel++) {
      if (pixel % 2 == 0) {
        neoPixel.setPixelColor(pixel, neoPixel.Color(0, 255, 0));
        neoPixel.show();
      }
    }
    neoPixel.clear();
    delay(300);

    for (int pixl = 0; pixl < ledNum; pixl += 1) {
      if (pixl % 2 == 1) {
        neoPixel.setPixelColor(pixl, neoPixel.Color(0, 255, 0));
        neoPixel.show();
      }
    }
    neoPixel.clear();
    delay(300);
  } else if (distancia <= sector[1]) {
    Serial.println("bajo");


    // turn on all pixels to red at the same time for two seconds
    for (int pixel = 0; pixel < ledNum; pixel++) {
      if (pixel % 2 == 0) {
        neoPixel.setPixelColor(pixel, neoPixel.Color(0, 255, 0));
        neoPixel.show();
      }
    }
    neoPixel.clear();
    delay(700);

    for (int pixl = 0; pixl < ledNum; pixl += 1) {
      if (pixl % 2 == 1) {
        neoPixel.setPixelColor(pixl, neoPixel.Color(0, 255, 0));
        neoPixel.show();
      }
    }
    neoPixel.clear();
    delay(700);
  } else {
    Serial.println("sin presencia");

    // turn pixels to green one by one with delay between each pixel
    // for each pixel
    for (int pixel = 0; pixel < ledNum; pixel++) {
      // it only takes effect if pixels.show() is called
      neoPixel.setPixelColor(pixel, neoPixel.Color(0, 255, 0));
      // send the updated pixel colors to the NeoPixel hardware.
      neoPixel.show();

      // pause between each pixel
      delay(50);
    }
    // turn off all pixels for two seconds
    neoPixel.clear();
    /*for (int pixl = 0; pixl > ledNum; pixl++) {
    neoPixel.setPixelColor(pixl, neoPixel.Color(0, 255, 0));
    neoPixel.show();  // send the updated pixel colors to the NeoPixel hardware.
    delay(50);      // off time
  }*/
  }

  Serial.print("distancia: ");
  Serial.println(medirDistancia());

  // if (debug) {
  // delay(100);
  //}


  // Serial.print("Max ");
  // Serial.println(valorMax);
  // Serial.print("Min ");
  // Serial.println(valorMin);
}

double medirDistancia() {

  // Ultrasonic Sensor HC-SR04 and Arduino Tutorial
  // by Dejan Nedelkovski, www.HowToMechatronics.com

  long lduracion = 0;
  double ldistancia = 0;

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  lduracion = pulseIn(echoPin, HIGH);

  // Calculating the distance
  ldistancia = lduracion * 0.034 / 2;

  //aplicamos return
  return ldistancia;
}

void actualizarSector() {

  // dividimos el rango del sensor en 4 posibles posiciones
  for (int i = 0; i < 4; i++) {
    sector[i] = ((valorMin + valorMax) / 4) * (4 - i);
  }
}

// bool rangoApto(double antiguo, double nuevo) {
//   if (nuevo - antiguo >= rangoIgnorar) {
//     return false;
//   } else {
//     return true;
//   }
// }
