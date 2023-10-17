// REFERENCIAS LED y sensores
// https://soloarduino.blogspot.com/2015/08/sensor-de-distancia-usando-hc-sr04-y.html
// http://www.electronicapty.com/component/k2/item/5-sensor-ultrasonico-de-distancia-hc-sr04/5-sensor-ultrasonico-de-distancia-hc-sr04 
// https://techmake.com/blogs/tutoriales/empezando-con-arduino-3c-sensor-ultrasonico-hc-sr04 
// https://hetpro-store.com/TUTORIALES/sensor-hc-sr04/ 
// https://proveedoracano.com/blog/?p=558 
// https://forum.arduino.cc/t/dos-o-mas-sensores-de-ultrasonido-juntos/332113 

#define TRIG_PINFUERA 2
#define ECHO_PINFUERA 3
#define TRIG_PINDENTRO 4
#define ECHO_PINDENTRO 5

#define LED_PIN 13

int umbral = 30;

long duracionFuera, distanciaFuera;
long duracionDentro, distanciaDentro;

float factorConversion = 29.1;

long deltaTiempo = 5000;

long tiempoInicial = -1;

bool empezar = false;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PINFUERA, OUTPUT);
  pinMode(ECHO_PINFUERA, INPUT);
  pinMode(TRIG_PINDENTRO, OUTPUT);
  pinMode(ECHO_PINDENTRO, INPUT);
}

void loop() {

  // lectura fuera
  digitalWrite(TRIG_PINFUERA, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PINFUERA, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PINFUERA, LOW);

  duracionFuera = pulseIn(ECHO_PINFUERA, HIGH);
  distanciaFuera = (duracionFuera / 2) / factorConversion;

  // lectura dentro
  digitalWrite(TRIG_PINDENTRO, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PINDENTRO, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PINDENTRO, LOW);

  duracionDentro = pulseIn(ECHO_PINDENTRO, HIGH);
  distanciaDentro = (duracionDentro / 2) / factorConversion;

  // Verificar si el sensor se activo o no
  bool sensorFueraActivo = (distanciaFuera < umbral);
  bool sensorDentroActivo = (distanciaDentro < umbral); 

  // queremos detectar si primero se activa el de fuera, y luego el de adentro, con una diferencia de tiempo
  // sensar cuando el de fuera esta activo Y el de dentro NO esta activo
  if (sensorFueraActivo && !empezar) {
    Serial.println("saliendo");
    // aqui empezo la deteccion
    empezar = true;
    tiempoInicial = millis();
  }

  // si el evento empezo
  if (empezar) {
    Serial.println("saliendo");
    // y ha pasado menos tiempo del que queremos
    if (millis() - tiempoInicial < deltaTiempo) {
      // comprobar si ahora los sensores estan invertidos
      if (sensorDentroActivo) {
        Serial.println("alerta de intruso");
        empezar = false;
      }
    }
    // en otro caso
    else {
      // resetear
      empezar = false; 
    }
     if (sensorDentroActivo) {
    empezar = false;
    // enciende el led
    digitalWrite(13, HIGH);
    delay(5000);
    // apaga el led
    digitalWrite(13, LOW);
  }
  }

  delay(100);
}