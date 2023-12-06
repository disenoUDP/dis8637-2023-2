void inicializarNeoPixel(int brilloInicial) {
  // inicia la tira
  neoPixel.begin();
  // configura el brillo inicial
  // el rango es entre 0 - 255
  neoPixel.setBrightness(brilloInicial);
}

void definirColorNeoPixel(ColorRGB nuevoColor) {
  neoPixel.clear();
  neoPixel.fill(
    neoPixel.Color(
      nuevoColor.getR(),
      nuevoColor.getG(),
      nuevoColor.getB()));
  neoPixel.show();
}

// envolvente ADSR?
// de hecho creo que basta con ASR
void definirCurva(unsigned long tiempoPulso, float tiempoFade) {
}
