#include <DHT.h> // Librería Dht11
// Aquí definimos las variables que vamos a utilizar
#define DHTTYPE DHT11 // Estamos definiendo que utilizaremos el Dht11
#define DHTPIN 4 // Se define el Pin que utilizaremos
// De la línea 6 - 8 se definirá los Pin del RGB
#define pinR 7 
#define pinG 6
#define pinB 5

DHT dht(DHTPIN, DHTTYPE); // Se inicializa el sensor DHT.

void setup() { // Es todo lo previo que se necesita para que funcione
// De la línea 14 - 16 se define los Pin RGB en donde sale la electricidad
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);

  Serial.begin(9600); // Se utiliza para que funcionen todos los dispositivos por ej: LED, Dht11 y arduino en la misma frecuencia
  dht.begin(); // Se utiliza para iniciar el Dht11

}

void loop() { // Esto quiere decir que está en bucle actualizando la temperatura y humedad cada 250 milisegundos
  delay(250); // Es una función que hace que el procesador espere
  float humidity = dht.readHumidity(); // Lee la humedad
  float temperature = dht.readTemperature(); // Lee la temperatura en grados Celsius

  if(isnan(humidity) || isnan(temperature)) { // isnan = No es un número que se vuelve verdadero cuando no es un número
    Serial.println("ERROR EN EL SENSOR"); // Consulta si hay fallo y vuelve a leer si lo hay.
  // Línea 31 y 32 Sirve para escribir un valor (o poner en un estado) un pin digital
    digitalWrite(pinR,255); 
    digitalWrite(pinG,0);
    return;
  }
  // Información de Temperatura y Humedad en el Serial Monitor.
  Serial.print ("Humidity: ");
  Serial.print (humidity);
  Serial.print ("% Temperature:");
  Serial.print (temperature);
  Serial.println("°C");
  digitalWrite(pinG,255);
  digitalWrite(pinR,0);
  delay(250);

}