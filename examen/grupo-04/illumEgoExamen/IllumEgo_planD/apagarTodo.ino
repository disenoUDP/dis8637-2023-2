void apagarTodo() {

  for (int i = 0; i < NUMPIXELS; i++) {              // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));  //arregalr color
    pixels.show();                                   // Send the updated pixel colors to the hardware.
  }
}