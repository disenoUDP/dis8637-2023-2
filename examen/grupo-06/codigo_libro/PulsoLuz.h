#ifndef PulsoLuz_H
#define PulsoLuz_H

#include "Arduino.h"

// declarar la clase PulsoLuz
// que va a tener metodos (funciones)
// y va a tener parametros (variables)
// y algunas van a ser publicas que podemos interactuar
// y otras son privadas, que son de uso interno
class PulsoLuz {
public:
  // declarar constructor de la clase PulsoLuz
  // que necesita dos valores, min y max
  PulsoLuz();
  void definirTiempos(unsigned long tiempoDuracion, float fadeIn, float fadeOut);
  void actualizarValor();
  // declarar funcion para obtener valor actual
  // es tipo int porque retorna un numero entero
  int getValorActual();
  unsigned long getMomentoFadeIn();
  unsigned long getMomentoFadeOut();
  void achatarMaximo();


private:
  int _valorMin;
  int _valorMax;
  int _valorActual;
  float _porcentajeFadeIn;
  float _porcentajeFadeOut;
  unsigned long _tiempoFadeIn;
  unsigned long _tiempoFadeOut;
  unsigned long _tiempoDuracion;
  unsigned long _tiempoInicio;
  unsigned long _momentoFadeIn;
  unsigned long _momentoFadeOut;
  unsigned long _momentoAchatado;
};

#endif