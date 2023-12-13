// importar biblioteca Processing Sound
import processing.sound.*;

// crear lista para los nombres de los archivos
StringList nombresArchivos = new StringList();

// crear String para la extension usada
String extension = ".mp3";

// crear lista para los sonidos
ArrayList<SoundFile> sonidos = new ArrayList<SoundFile>();

int sonidoActual = 0;
float[] volumenActual = {1,1,1,1};


// arreglos con variables para cada sonido
boolean[] presionando = {false, false, false, false};
//long[] tiemposoltadoTecla = {-1, -1, -1, -1};


void setup() {

  // configurar lienzo
  size(640, 360);

  // fondo blanco del lienzo
  background(255);

  // agregar nombres de archivos
  nombresArchivos.append("pastizal");
  nombresArchivos.append("hoja");
  nombresArchivos.append("pastos");
  nombresArchivos.append("piedra");


  // recorrer los nombres de los archivos

  for (int i = 0; i < nombresArchivos.size(); i++) {
    // cargar los sonidos
    sonidos.add(new SoundFile(this, nombresArchivos.get(i) + extension));
  }
}

void draw() {
  // Ajustar el volumen según la cantidad de teclas presionadas
  //float volumenActual = (audioActual != 0) ? 0.5 : 1.0;

  // establecer el voumen de todos los sonidos
  for (int i = 0; i < sonidos.size(); i++) {
    // cargar los sonidos
    sonidos.get(i).amp(volumenActual[i]);
  }

  // tocar segun la superficie
  for (int i = 0; i < sonidos.size(); i++) {
    if (i == sonidoActual && !sonidos.get(i).isPlaying()) {
      sonidos.get(i).play();
    }
  }
  // para apagar los sonidos
  for (int i = 0; i < sonidos.size(); i++) {
    // si han pasado 5 segundos desde que solte la tecla y no la he vuelto a tocar
    if (!presionando[i] && volumenActual[i]>0) {
      // aca ponemos el numero para bajar el volumen
      volumenActual[i] -= 0.008;
    }
  }
}

// funcion llamada cuando se presiona una tecla
void keyPressed() {
  if (key == CODED) {
    if (keyCode == UP) {
      volumenActual[0] = 1;
      presionando[0] = true;
      sonidoActual = 0;
    } else if (keyCode == DOWN) {
      volumenActual[1] = 1;
      presionando[1] = true;
      sonidoActual = 1;
    } else if (keyCode == RIGHT) {
      volumenActual[2] = 1;
      presionando[2] = true;
      sonidoActual = 2;
    } else if (keyCode == LEFT) {
      volumenActual[3] = 1;
      presionando[3] = true;
      sonidoActual = 3;
    } else {
      sonidoActual = -1;
    }
  }
}

// apaga el sonido que le digamos
void apagarSonido(int n) {
  sonidos.get(n).stop();
}

// funcion llamada cuando se suelta una tecla
void keyReleased() {
  if (key == CODED) {
    if (keyCode == UP) {
      presionando[0] = false;
      //tiemposoltadoTecla[0] = millis();
    } else if (keyCode == DOWN) {
      presionando[1] = false;
      //tiemposoltadoTecla[1] = millis();
    } else if (keyCode == RIGHT) {
      presionando[2] = false;
      //tiemposoltadoTecla[2] = millis();
    } else if (keyCode == LEFT) {
      presionando[3] = false;
      //tiemposoltadoTecla[3] = millis();
    }
  }
}
