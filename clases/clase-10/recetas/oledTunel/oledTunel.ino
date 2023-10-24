// ejemplo de uso de funciones matematicas para animar : TUNEL en OLED 128x64 px
//
// por AndresMartinM
// primavera 2023

#include <Wire.h>			// libreria para bus I2C
#include <Adafruit_GFX.h>		// libreria para pantallas graficas
#include <Adafruit_SSD1306.h>		// libreria para controlador SSD1306
 
#define ANCHO 128			// reemplaza ocurrencia de ANCHO por 128
#define ALTO 64				// reemplaza ocurrencia de ALTO por 64

#define OLED_RESET 4			// necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);	// crea objeto

void setup() {
  Serial.begin(9600);
  Wire.begin();					// inicializa bus I2C
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);	// inicializa pantalla con direccion 0x3C
}
 
void loop() {
  oled.clearDisplay();	
  for(int i=0; i < oled.height(); i++) {	// bucle desde 1 hasta alto de pantalla/2
    oled.drawCircle(oled.width()/2, 12, easeInCubic(i)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+8) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+16) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+24) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+32) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+40) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+48) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+56) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+2) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+10) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+18) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+26) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+34) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+42) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+50) % 64)/1024, WHITE);
    oled.drawCircle(oled.width()/2, 12, easeInCubic((i+58) % 64)/1024, WHITE);
    oled.display();
    delay(30);
    oled.clearDisplay();
  }
}
double easeInCubic( double t ) {
    return t * t * t;
}

double easeInOutCubic( double t ) {
    return t < 0.5 ? 4 * t * t * t : 1 + (--t) * (2 * (--t)) * (2 * t);
}