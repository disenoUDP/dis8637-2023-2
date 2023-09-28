// ejemplo umbral sensor

// constante de conexion del sensor
const int sensorPin = A0;

// variable para valor actual del sensor
int sensorValor = -1;

// variables de valores minimo y maximo
// empezamos con valores muy errados
int valorMin = 10000;
int valorMax = 0;

// valor a la mitad entre minimo y maximo
int valorMitad = (valorMin + valorMax)/2;

void setup() {

  // iniciamos la comunicacion serial
  Serial.begin(9600);
}

void loop() {

  // actualizar lectura del sensor
  sensorValor = analogRead(sensorPin);
  
  // actualizar valorMin
  if (sensorValor < valorMin){
    valorMin = sensorValor;
  }
  // actualizar valorMax
  if (sensorValor > valorMax){
    valorMax = sensorValor;
  }

  // actualizar el valor que esta a mitad del rango (umbral)
  valorMitad = (valorMin + valorMax)/2;

  // imprimir en consola si el valor es alto o bajo
  if (sensorValor >= valorMitad){
    Serial.println("alto");
  }else {
    Serial.println("bajo");
  }

}
