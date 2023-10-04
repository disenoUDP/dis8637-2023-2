#define trig 7  // emisor de la señal

#define echo 6  // receptor de la señal

#define buzzer 12  //zumbador

void setup() {
  // sólo se activa al iniciarse el programa. (definimos entradas y salidas)
  Serial.begin(9600);
  pinMode(trig, OUTPUT);  //emisor

  pinMode(echo, INPUT);  //receptor

  pinMode(buzzer, OUTPUT);  //emisor
}

void loop() {
  // Bucle. (se repite indefinidamente despues de iniciar el programa)

  long duration, distance;  //duration y distance (variables numéricas extensas)

  digitalWrite(trig, LOW);  //2 microsegundos en apagado

  delay(2);

  digitalWrite(trig, HIGH);  //se mandamos un pulso de 5 microsegundos

  delay(5);

  digitalWrite(trig, LOW);  //se apaga

  duration = pulseIn(echo, HIGH);  //se mide el tiempo que la señal tarda en volver al sensor en microsegundos

  distance = (duration / 2) * 0.0343;  //la distancia es el tiempo por la velocidad del sonido (343 m/s = 0.0343 cm/microseg)
  Serial.println(distance);
   //si la distancia es menor de un metro y medio
  if (distance < 10) {
    tone(buzzer, 1000);  //suena el zumbador con una frecuencia de 1000Hz
    delay(5000);  //durante 5 segundos
  } else          //de lo contrario
  {
    noTone(buzzer);  //no suena
  }
}
