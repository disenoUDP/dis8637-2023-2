void animacion02() {
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 0, 250));
    pixels.show();  // Send the updated pixel colors to the hardware.
  }
    Serial.println("2");


  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(195 + (i * 2), 0, 60 - (i * 2)));

    pixels.show();  // Send the updated pixel colors to the hardware.

    //delay(DELAYVAL / (i + 1));  // Pause before next pass through loop
    delay(DELAYVAL);  // Pause before next pass through loop

  }
  delay(5000);//delay de la anomacion final 
}