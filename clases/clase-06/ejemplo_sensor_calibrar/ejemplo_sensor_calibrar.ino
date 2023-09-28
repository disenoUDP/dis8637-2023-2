// ejemplo_sensor_calibrar
// dis8637
// 2023 septiembre 26

// variable para entrar en modo debug o no
bool modoDebug = false;

const int sensorPin = A0;
int sensorValor = -1;

// variables para almacenar valores minimo y maximo
// inicializamos con valores muy errados
int valorMin = 10000;
int valorMax = 0;

// variable para almacenar valor a la mitad del rango
int valorMitad = (valorMin + valorMax) / 2;

void setup() {

  // iniciamos la comunicacion serial
  Serial.begin(9600);
}

void loop() {

  // actualizamos el valor del sensor
  sensorValor = analogRead(sensorPin);

  // actualizamos los valores minimo y maximo
  actualizarMinMax();

  // actualizamos el valor a la mitad del rango
  actualizarMitad();

  // damos un resultado
  darResultado();
}

// funcion para actualizar valor minimo y maximo
void actualizarMinMax() {

  // actualizar valorMin
  if (sensorValor < valorMin) {
    valorMin = sensorValor;
  }
  // actualizar valorMax
  if (sensorValor > valorMax) {
    valorMax = sensorValor;
  }
}

void actualizarMitad() {
  // actualizar el valor que esta a mitad del rango (umbral)
  valorMitad = (valorMin + valorMax) / 2;
}


void darResultado() {
  // si estamos en modo debug, imprimimos en consola
  if (modoDebug) {
    // decidimos si el valor actual es alto o bajo
    if (sensorValor >= valorMitad) {
      Serial.println("alto");
    } else {
      Serial.println("bajo");
    }
  }
  // si no estamos en modo consola, podemos por ejemplo prender una luz
  else {
    // prender luz segun resultado
  }
}
