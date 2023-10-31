// receta animar con curva
//     _   _
//   _/ \_/ \_  <--- curva sinusoidal (mas o menos)
//
// codigo para hacer cambios en valores segun el tiempo
// sirve para hacer fade-in fade-out y tintineo
//
// abran el serial plotter para visualizar valorAnim
//
// por AndresMartinM para el curso Taller UX de UDP
// primavera 2023


// pin del boton para iniciar la animacion
int btn = 8;

// variable que se usara como punto de partida de la animacion
long inicio = -1;
// duracion en milisegundos
int duracion = 1000;
bool direccion = false;

int valorAnim = 0;   // este valor vamos a animar

bool ocurriendo = false;

void setup() {
  Serial.begin(9600);
  pinMode(btn, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  //Serial.print(millis()-inicio);
  Serial.println(valorAnim);

  evento();

  analogWrite(3, valorAnim);

}

// necesito una funcion que me entregue valores entre x e y, y que los 'reproduzca' en un tiempo especifico
// evento
// empezar a contar
// reproducir la animacion
// cortar la animacion
// esperar evento

// funcion booleana que nos dice si el boton esta presionado o no (no contiene debounce)
bool boton(int b) {
  if (digitalRead(b) == HIGH) {
    return true;
  } else {
    return false;
  }
}

// dentro de la funcion evento se decide que etapa del 
void evento() {
  if (boton(btn) && !ocurriendo) {
    inicio = millis();
    ocurriendo = true;
    if (direccion) {
      direccion = false;
    } else {
      direccion = true;
    }
  } else if ((millis() - inicio) < duracion && ocurriendo) {
    valorAnim = animQuad(duracion, direccion); // aca ponemos cual animacion usaremos
  } else {
    ocurriendo = false;
  }
  if(!ocurriendo){
    if (direccion){
      valorAnim = 255;
    } else {
      valorAnim = 0;
    }
  }
}

// funcion para la jacinta, de pulsaciones por minuto a tiempo
int corazon(int ppm){
return 60000 / ppm;
}

int animLine(int dur, bool dir) {
  int time = millis() - inicio;
  int max = 255;
  int funcion;
  if (dir) {
    funcion = lineIn(map(time, 1, dur, 0, max));
  } else {
    funcion = lineIn(map(time, 1, dur, max, 0));
  }
  return funcion;
}
int animQuad(int dur, bool dir) {
  int time = millis() - inicio;
  int max = 32;
  int funcion = quadIn(map(time, 0, dur, 0, max));  // aca ponemos la funcion matematica que vamos a usar, como duracion es un valor muy alto lo mapee dentro de la funcion
  if (dir) {
    return map(funcion, quadIn(1), quadIn(max), 0, 255);  // aca puse entre 0 y 255 pero pueden poner el rango que necesiten
  } else {
    return map(funcion, quadIn(1), quadIn(max), 255, 0);  // aca puse entre 0 y 255 pero pueden poner el rango que necesiten
  }
}
// por la pendiente tan alta de la curva el arduino casi no se la puede (cuidado)
int animCube(int dur, bool dir) {
  int time = millis() - inicio;
  int max = 12;
  int funcion = cubeIn(map(time, 0, dur, 0, max));  // aca ponemos la funcion matematica que vamos a usar, como duracion es un valor muy alto lo mapee dentro de la funcion
  if (dir) {
    return map(funcion, cubeIn(1), cubeIn(max), 0, 255);  // aca puse entre 0 y 255 pero pueden poner el rango que necesiten
  } else {
    return map(funcion, cubeIn(1), cubeIn(max), 255, 0);  // aca puse entre 0 y 255 pero pueden poner el rango que necesiten
  }
}

// a continuacion las funciones matematicas usadas
int lineIn(int t) {
  return t;
}
int quadIn(int t) {
  return (t * t);
}
int cubeIn(int t) {
  return (t * t * t);
}

