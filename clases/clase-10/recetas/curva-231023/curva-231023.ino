// receta animar con curva
//     _   _
//   _/ \_/ \_  <--- curva sinusoidal (mas o menos)
//
// codigo para hacer cambios en valores segun el tiempo
// sirve para hacer fade-in fade-out y tintineo
//
// por AndresMartinM para el curso Taller UX de UDP
// primavera 2023

// IMPORTANTE AUN NO ESTA FUNCIONANDO

// pin del boton para iniciar la animacion
int btn = 8;

// variable que se usara como punto de partida de la animacion
long inicio = -1;
// duracion en milisegundos
int duracion = 5000;

int valorAnim = 0; // este valor vamos a animar

void setup() {
  Serial.begin(9600);
  pinMode(btn, INPUT);
}

void loop() {
  
  Serial.println(valorAnim);
  evento();
}

// necesito una funcion que me entregue valores entre x e y, y que los 'reproduzca' en un tiempo especifico
// evento
// empezar a contar
// reproducir la animacion
// cortar la animacion
// esperar evento

bool ocurriendo = false;

bool boton() {
  if (digitalRead(btn) == HIGH) {
    return true;
    Serial.println("vamos biem 0");
  } else {
    return false;
    Serial.println("vamos biem -1");
  }
}

void evento() {
  if (boton() && !ocurriendo) {
    inicio = millis();
    Serial.println("vamos biem");
    ocurriendo = true;
  } else if((millis() - inicio) < duracion){
    valorAnim = anim(duracion);
    Serial.println("vamos biem2");
  } else {
    ocurriendo = false;
    Serial.println("vamos biem3");
  }
}

int anim(int dur) {
  int time = millis() - inicio;
  int max = 128;
  int funcion = cubeIn(map(time, 0, dur, 0, max)); // aca ponemos la funcion matematica que vamos a usar, como duracion es un valor muy alto lo mapee dentro de la funcion
  return map(funcion, 0, cubeIn(max), 0, 512); // aca puse entre 0 y 512 pero pueden poner el rango que necesiten
}

// a continuacion las funciones matematicas usadas
int cubeIn(int t) {
  return (t * t * t);
}

int cubeOut(int t) {
  return 1 + (--t) * t * t;
}