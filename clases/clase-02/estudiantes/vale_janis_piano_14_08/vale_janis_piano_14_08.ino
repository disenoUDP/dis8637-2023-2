#include <Tone.h>       // Biblioteca "Tone" de Brett Hagman para generar las frecuencias de las notas musicales

#define BUZZER_PIN 4
#define SENSOR_PIN A0
#define LED_PIN_RED 5
#define LED_PIN_GREEN 7

Tone tone1;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);

  tone1.begin(BUZZER_PIN);

  Serial.begin(9600); 
}

void loop() {
  int rawValue = analogRead(SENSOR_PIN);

  float distanceInInches = map(rawValue, 0, 100, 0, 100);     // float ---> Representación de números reales. map ---> "mapear" como en el plano cartesiano
  // map(valor, rango de entrada y salida min, rango de entrada y salida max,) creo q se puede borrar

  int note;
  bool shouldLightRedLED = false;       // Variable positiva o negativa
  bool shouldLightGreenLED = false;

  if (distanceInInches >= 0 && distanceInInches <= 10) {
    note = 262;  // Do | C
    shouldLightRedLED = true;
  } else if (distanceInInches >= 11 && distanceInInches <= 21) {
    note = 294;  // Re | D
    shouldLightGreenLED = true;
  } else if (distanceInInches >= 22 && distanceInInches <= 32) {
    note = 330;  // Mi | E
    shouldLightRedLED = true;
  } else if (distanceInInches >= 33 && distanceInInches <= 43) {
    note = 349;  // Fa | F
    shouldLightGreenLED = true;
  } else if (distanceInInches >= 44 && distanceInInches <= 54) {
    note = 392;  // Sol | G
    shouldLightRedLED = true;
  } else if (distanceInInches >= 55 && distanceInInches <= 65) {
    note = 440;  // La | A
    shouldLightGreenLED = true;
  } else if (distanceInInches >= 66 && distanceInInches <= 76) {
    note = 494;  // Si | B
    shouldLightRedLED = true;
  } else {
    note = 0;
  }

  // Encender o apagar el LED rojo según la nota tocada
  if (shouldLightRedLED) {
    digitalWrite(LED_PIN_RED, HIGH);       // Encender el LED rojo
  } else {
    digitalWrite(LED_PIN_RED, LOW);       // Apagar el LED rojo
  }

  // Encender o apagar el LED verde según la nota tocada
  if (shouldLightGreenLED) {
    digitalWrite(LED_PIN_GREEN, HIGH);        // Encender el LED verde
  } else {
    digitalWrite(LED_PIN_GREEN, LOW);        // Apagar el LED verde
  }

  if (note != 0) {
    switch (note) {
      case 262:
        Serial.println("Do");
        break;
      case 294:
        Serial.println("Re");
        break;
      case 330:
        Serial.println("Mi");
        break;
      case 349:
        Serial.println("Fa");
        break;
      case 392:
        Serial.println("Sol");
        break;
      case 440:
        Serial.println("La");
        break;
      case 494:
        Serial.println("Si");
        break;
      default:
        Serial.println("No se tocó ninguna nota");
    }

    
    tone1.play(note);
    delay(2000);
    tone1.stop();
  }

  delay(1000);
}
