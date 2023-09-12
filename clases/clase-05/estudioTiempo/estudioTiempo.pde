// primer estudio de tiempo 2023-09-12
//
// int : ... -1 , 0 , 1 , 2 .... (enteros)
// float : 0.0001 .... 0.99999 , 1 (decilmales)

float ancho = 200;
float alto = 50;
int segundos;
float duracion;

void setup() {
  // creo una ventana -size(ancho, alto)- y la pinto
  size(400,400);
  background(255);
  
  // indico que vamos a dibujar sin borde
  noStroke();
}

void draw() {
  // pinto fondo blanco -background(rgb o greyscale)-
  background(255);
  
  // calculo los segundos ocurridos en base a los milisegundos -millis()-
  segundos = millis() / 1000;
  println(segundos);
  
  cicloColor(4);
  
  dibujarRectangulos(6);
  
}

void cicloColor(int ciclo) {
  // condiciono -if(condicion){} else {}- el color de relleno -fill(rgb o greyscale)- segun el tiempo -segundos-
  if (segundos % ciclo == 0){
    fill(255, 50, 10);
  } else {
    fill(0);
  }
}
void dibujarRectangulos(int cuantos) {
  for (int i = 0; i < cuantos; i++){
    // dibujo el rectangulo -rect(x, y, ancho, alto, radioBorde)-
    rect(100, 60*i, ancho, alto, 20);
  }
}
