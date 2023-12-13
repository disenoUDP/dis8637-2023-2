bool sensor() {

  bool presencia;
  long t;  // Tiempo que demora en llegar el eco
  long d;  // Distancia en centímetros

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);  // Enviamos un pulso de 10us
  digitalWrite(trigger, LOW);

  t = pulseIn(echo, HIGH);  // Obtenemos el ancho del pulso
  d = t / 59;               // Escalamos el tiempo a una distancia en cm

  // Agregar la nueva lectura y restar la lectura más antigua para el promedio móvil
  total = total - readings[indice];
  readings[indice] = d;
  total = total + readings[indice];
  indice = (indice + 1) % numReadings;


  // Calcular el promedio
  int averageDistance = total / numReadings;


  // Verificar si la distancia promedio es menor o igual a 30 cm y tomar una acción
  if (averageDistance <= 30) {
      presencia = true;
     if (!examen) {
    Serial.println("Presencia detectada");
     }
  } else {
   presencia = false;
       if (!examen) {
    Serial.println("No hay presencia");
       }
    
  }

  //delay(100);  // Hacemos una pausa de 100ms
  return presencia; 
}
