// receta potenciometro
//    _
//  ( O )   <--- potenciometro
//  | | |
// 5v A gnd
//
// patita central a entrada analogica
// las otras 2 a 5v y gnd (una y una)
//
// por AndresMartinM para el curso Taller UX de UDP
// primavera 2023

int pinPerilla = A0;

void setup() {
  Serial.begin(9600);
}

// aca en el loop hay un ejemplo de posibles usos de las funciones que cree a continuacion
void loop() {
  //Serial.println(porDebajo(potenciometroMap(debounce(potenciometro(pinPerilla)), 0 , 100), 50));
  //Serial.println(potenciometroMap(debounce(potenciometro(pinPerilla)), 0 , 100));
  Serial.println(debounce(potenciometro(pinPerilla)));
}

// esta funcion nos entrega el valor de la entrada anlogica
int potenciometro(int pin) {
  return analogRead(pinPerilla);
}

// esta funcion nos entrega el valor de la entrada analogica mapeada (es decir entre un minimo y maximo)
int potenciometroMap(int pin, int min, int max) {
  return map(potenciometro(pin), 0, 1023, min, max);
}

// lo siguiente nos sirve para aplanar el rebote del valor obtenido
int valorAnterior = -5;  // ojo esta variable tiene que ser una por cada perilla
int margen = 5;

int debounce(int valor) {
  if (valor + margen < valorAnterior || valor - margen > valorAnterior) {
    valorAnterior = valor;
  }
  return valorAnterior;
}

// esta funcion nos sirve para saber si el valor esta por encima de un umbral o si es equivalente
bool porEncima(int valor, int umbral) {
  if (valor >= umbral) {
    return true;
  } else {
    return false;
  }
}
// y esta otra nos sirve para saber si esta por debajo
bool porDebajo(int valor, int umbral){
 if (valor < umbral) {
    return true;
  } else {
    return false;
  }
}
