#include "Arduino.h"
#include "PulsoLuz.h"

// definir lo que hace el constructor
PulsoLuz::PulsoLuz() {
  _valorMin = 0;
  _valorMax = 255;
  _valorActual = _valorMin;
  _tiempoInicio = millis();
  _momentoAchatado = millis();
}

// tiempoPulso define cuanto tiempo dura el evento entre prender y apagar
// tiempoFade es un porcentaje de cuanto de ese tiempo total
// se ocupa en el fadeIn y en el fadeOut
// entonces tiempoPulso es el 100% del tiempo
// si hay un tiempo que es tiempoPrendido
// entonces tiempoPulso = tiempoFade + tiempoPrendido + tiempoFade
// resumiendo, tiempoPulso = tiempoPrendido + 2 * tiempoFade
void PulsoLuz::definirTiempos(unsigned long tiempoDuracion, float fadeIn, float fadeOut) {
  _tiempoDuracion = tiempoDuracion;
  _porcentajeFadeIn = fadeIn;
  _porcentajeFadeOut = fadeOut;
  // _tiempoFadeIn = _tiempoDuracion * _porcentajeFadeIn;
  // _tiempoFadeOut = _tiempoDuracion * _porcentajeFadeOut;
  _momentoFadeIn = _tiempoDuracion * _porcentajeFadeIn;
  _momentoFadeOut = _tiempoDuracion * (float(1.0) - _porcentajeFadeOut);
}

void PulsoLuz::actualizarValor() {

  // usar funcion modulo (%) para encontrar
  // el resto de la division entre millis() y _tiempoDuracion
  unsigned long momentoActual = millis() % _tiempoDuracion;

  // si estamos en un momento entre 0 y _tiempoFadeIn
  if (momentoActual < _momentoFadeIn) {
    _valorActual = _valorMax * (float(momentoActual) / float(_momentoFadeIn));
  }
  // si estamos en un momento entre 0 y _tiempoFadeOut
  else if (momentoActual > _momentoFadeOut) {
    _valorActual = _valorMax * (1.0 - float(momentoActual - _momentoFadeOut) / float(_momentoFadeOut));
    // _valorActual = _valorMax * (float(momentoActual -) / float(_tiempoDuracion - _tiempoFadeOut));
  } else {
    _valorActual = _valorMax;
  }
}

void PulsoLuz::achatarMaximo(){
  if (millis() - _momentoAchatado > 400){
    _valorMax = _valorMax - 1;
    _momentoAchatado = millis();
  }

  if (_valorMax < _valorMin) {
    _valorMax = _valorMin;
  }
}

int PulsoLuz::getValorActual() {
  return _valorActual;
}

unsigned long PulsoLuz::getMomentoFadeIn() {
  return _momentoFadeIn;
}

unsigned long PulsoLuz::getMomentoFadeOut() {
  return _momentoFadeOut;
}