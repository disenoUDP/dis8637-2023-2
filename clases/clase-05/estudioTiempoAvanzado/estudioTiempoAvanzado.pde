// segundo estudio de tiempo 2023-09-12

// interaccion inicial -click-
// empezar a contar
// comportamiento uno
// contar de nuevo?
// comportamiento dos
// esperar nueva interaccion

boolean empezar = false;
int tiempoInicial = 0;

void setup() {
  // size(pixelesAncho, pixelesAlto)
  size(200, 200);
}

void draw() {
  background(255);

  if (empezar) {
    if (millis() - tiempoInicial < 5000) {
      background(0);
    } else if (millis() - tiempoInicial < 10000) {
      background(0, 255, 0);
    } else {
      empezar = false;
    }
    fill(255, 0, 0);
    text("funcionando",100,100);
  }
}

void mousePressed() {
  empezar = true;
  tiempoInicial = millis();
  println(tiempoInicial);
}
