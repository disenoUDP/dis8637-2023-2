#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

// Definir constantes
#define ANCHO_PANTALLA 128 // ancho pantalla OLED
#define ALTO_PANTALLA 64    // alto pantalla OLED

// Objeto de la clase Adafruit_SSD1306
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

// Sensores Sharp #1 y #2
const int sensorPin1 = A0; // Pin analógico para Sharp #1
const int sensorPin2 = A1; // Pin analógico para Sharp #2

// Variables para los valores actuales de los sensores
int sensorValor1 = -1;
int sensorValor2 = -1;

// Variables para los valores mínimos y máximos de cada sensor
int valorMin1 = 10000;
int valorMax1 = 0;
int valorMin2 = 10000;
int valorMax2 = 0;

// Valores umbrales para cada sensor (a mitad del rango)
int valorMitad1;
int valorMitad2;

// Variable para la disponibilidad
int disponibilidad = -1;

void setup() {
  // Iniciamos la comunicación serial
  Serial.begin(9600);
  
  // Iniciar pantalla OLED en la dirección 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("No se encuentra la pantalla OLED");
    while (true);
  }

  // Limpiar buffer
  display.clearDisplay();

  // Tamaño del texto
  display.setTextSize(1);
  // Color del texto
  display.setTextColor(SSD1306_WHITE);
  // Posición del texto
  display.setCursor(10, 32);
  // Activar página de código 437
  display.cp437(true);

  // Inicializar la disponibilidad como "Desconocida"
  disponibilidad = -1;
}

void loop() {
  // Actualizar lecturas de los sensores
  sensorValor1 = analogRead(sensorPin1);
  sensorValor2 = analogRead(sensorPin2);

  // Actualizar valorMin y valorMax para el sensor #1
  if (sensorValor1 < valorMin1) {
    valorMin1 = sensorValor1;
  }
  if (sensorValor1 > valorMax1) {
    valorMax1 = sensorValor1;
  }

  // Actualizar valorMin y valorMax para el sensor #2
  if (sensorValor2 < valorMin2) {
    valorMin2 = sensorValor2;
  }
  if (sensorValor2 > valorMax2) {
    valorMax2 = sensorValor2;
  }

  // Calcular los valores umbrales para cada sensor
  valorMitad1 = (valorMin1 + valorMax1) / 2;
  valorMitad2 = (valorMin2 + valorMax2) / 2;

  // Determinar la disponibilidad
  if (sensorValor1 >= valorMitad1 && sensorValor2 >= valorMitad2) {
    disponibilidad = 0; // Ambos sensores detectan presencia
  } else if (sensorValor1 >= valorMitad1 || sensorValor2 >= valorMitad2) {
    disponibilidad = 1; // Al menos un sensor detecta presencia
  } else {
    disponibilidad = 2; // Ambos sensores no detectan presencia
  }

  // Mostrar la disponibilidad en la pantalla OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10, 32);

  switch (disponibilidad) {
    case 0:
      display.println("0 Disponible");
      break;
    case 1:
      display.println("1 Disponible");
      break;
    case 2:
      display.println("2 Disponibles");
      break;
    default:
      display.println("Desconocido");
      break;
  }

  // Enviar a pantalla
  display.display();
  
  // Retraso de 1 segundo (1000 milisegundos)
  delay(1000);
}
