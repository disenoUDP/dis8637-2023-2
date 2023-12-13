void animacion01() {
  byte cero = 0;
  Serial.write(cero);
  for (int i = 0; i < NUMPIXELS; i++) { // Para cada píxel...
    pixels.setPixelColor(i, pixels.Color(0, 0, 250)); // Color azul (puedes cambiarlo si lo deseas)
    pixels.show();   // Mostrar los cambios en los pixeles.
    delay(DELAYVAL);
  }

  delay(500); // Pausa antes de la próxima animación

  pixels.show();  // Mostrar los cambios 

  Serial.write(1);
  for (int i = 0; i < NUMPIXELS; i++) { // Para cada píxel...
    pixels.setPixelColor(i, pixels.Color(250, 250, 0)); // Color azul (puedes cambiarlo si lo deseas)
    pixels.show();   // Mostrar los cambios en los pixeles.
    delay(DELAYVAL);
  }

  delay(500); // Pausa antes de la próxima animación

  pixels.show();  // Mostrar los cambios (todos los pixeles apagados)
  
  
  Serial.write(2);
  delay(500);
  for (int i = 0; i < NUMPIXELS; i++) { // Para cada píxel...
    pixels.setPixelColor(i, pixels.Color(0 + (i * 5), 0, 60 - (i * 2))); // Color verde con variación
    pixels.show();   // Mostrar los cambios en los pixeles
    delay(DELAYVAL*2);
  }
  delay(4000); // Pausa antes de la próxima animación

  Serial.write(3);
  for (int i = 0; i < NUMPIXELS; i++) { // Para cada píxel...
    pixels.setPixelColor(i, pixels.Color(0, 170, 250)); // Color azul (puedes cambiarlo si lo deseas)
    pixels.show();   // Mostrar los cambios en los pixeles.
    delay(DELAYVAL/2);
  }

  delay(500); // Pausa antes de la próxima animación

  pixels.show();  // Mostrar los cambios 
  Serial.write(4);
  apagarTodo() ;
   delay(5000);
}