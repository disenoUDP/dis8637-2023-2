// ejemplo_sensor
// dis8637
// 2023 septiembre 26

// constante de pin donde conectamos el sensor
const int sensorPin = A0;

// variable para almacenar lectura del sensor
int sensorValor = -1;

// variables para almacenar valores minimos y maximos
// partimos con un muy mal minimo, y un muy mal maximo
int valorMin = 10000;
int valorMax = 0;

void setup() {

  // iniciamos la comunicacion serial
  Serial.begin(9600);
}

void loop() {
  // leer sensor
  sensorValor = analogRead(sensorPin);
  
  // imprimir en consola el valor del sensor
  Serial.println("valor del sensor : " + String(sensorValor));

  // imprimir en consola los valores minimo y maximo
  Serial.println("menor : " +  String(valorMin) + "   mayor : " + String(valorMax));

  // pausa de 100 milisegundos
  delay(100);

  // actualizar valorMin
  if (sensorValor < valorMin){
    valorMin = sensorValor;
  }
  // actualizar valorMax
  if (sensorValor > valorMax){
    valorMax = sensorValor;
  }

}
