// ejemplo_sensor_promediar
// dis8637
// 2023 septiembre 26

bool modoDebug = false;

const int sensorPin = A0;
int sensorValor = -1;

// crear arreglo (array) de enteros
// en este caso son 10
int valores[10];

// variable para almacenar la cantidad de valores
int valoresNum;

// variable para almacenar el promedio
int promedio = -1;

void setup() {

  // calcular el numero de valores
  // en este caso es 10
  // podriamos haber escrito = 10, pero aqui lo calculamos
  // para que podamos cambiar el valor en la declaracion del arreglo
  // y esto se propague en el resto del codigo
  valoresNum = sizeof(valores) / sizeof(valores[0]);

  // valores iniciales para luego calcular el promedio
  // elegimos -1 para demostrar que aun no hemos leido
  for (int i = 0; i < valoresNum; i++) {
    valores[i] = -1;
  }

  // iniciamos la comunicacion serial
  Serial.begin(9600);
}

void loop() {

  // actualizar valor sensor
  sensorValor = analogRead(sensorPin);

  // mover valores al pasado
  // recorrer desde ultimo hasta primero
  for (int i = valoresNum - 1; i > 0; i--) {
      // reemplazar valor en i por el de i-1
      valores[i] = valores[i - 1];
  }

  // actualizar el valor en posicion 0
  valores[0] = sensorValor;

  // calcular el promedio
  promedio = calcularPromedio();

  // imprimir el promedio en consola
  Serial.println(promedio)
}

// calcular promedio
// esta funcion es int, no es void
// esto significa que tiene un retorno de tipo int
int calcularPromedio() {

  // crear variable para acumular todos los valores
  int acumulador = 0;

  // sumarle al acumulador todos los valores
  for (int i = 0; i < valoresNum; i++) {
    acumulador = acumulador + valores[i];
  }
  
  // retorna el valor del promedio
  return acumulador / valoresNum;
}
