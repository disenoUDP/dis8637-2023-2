int message = 0;
// las variables están medidas en milisegundos,
unsigned long TASK_TIME = 60000; // prueba: 1 min
unsigned long BREAK_TIME = 30000; // prueba: 30 segs
unsigned long taskDelayStart = 0; // el tiempo de inicio del delay
unsigned long breakDelayStart = 0; // el tiempo de inicio del delay
bool taskDelayRunning = false; // funciona sólo en caso de espera del delay
bool breakDelayRunning = false; // funciona sólo en caso de espera del delay
bool taskLightOn = false; // mantiene el curso del estado de la luz

#define taskLampPin 13
#define breakLampPin 12
#define triggerPin 4

void setup() {
  pinMode(triggerPin, INPUT_PULLUP); // configuración del pin del interruptor con la resistencia pull-up interna
  pinMode(taskLampPin, OUTPUT);        
  digitalWrite(taskLampPin, LOW);
  pinMode(breakLampPin, OUTPUT);        
  digitalWrite(breakLampPin, LOW);

  // empieza la conexión serial wiii :)
  Serial.begin(9600);
}

void loop() {
  message = digitalRead(triggerPin);
  if (message == 0){ // si un ejercicio está en proceso
    if (!taskLightOn && !taskDelayRunning & !breakDelayRunning){ // si ni la luz ni el temporizador han comenzado aun
      taskDelayStart = millis(); // empieza el delay
      taskDelayRunning = true;   // empieza el temporizador :)!

      digitalWrite(taskLampPin, HIGH);         // la luz se enciende!!
      taskLightOn = true;
      Serial.println("Empieza la rutina :)!");
    }
      
    if (taskLightOn && taskDelayRunning && ((millis() - taskDelayStart) >= TASK_TIME)) { // este código se ejecuta cuando el ejercicio ha terminado :)!
      taskDelayStart += TASK_TIME; // esto previene salidas inesperadas :o
      taskDelayRunning = false;
      Serial.println("Suficiente trabajo por ahora :) hidratáte y tómate un descansito!!");
      digitalWrite(breakLampPin, HIGH);         // enciende la luz :) 
      digitalWrite(taskLampPin, LOW);          // apaga la luz zzz
      taskLightOn = false;

       breakDelayStart = millis(); // empieza el delay
       breakDelayRunning = true;
     }
    
    if (!taskLightOn && breakDelayRunning && ((millis() - breakDelayStart) >= BREAK_TIME)) { // este código se ejecuta cuando el tiempo de descanso ha terminado pipipi
      breakDelayStart += BREAK_TIME; // esto previene salidas inesperadas :o
      breakDelayRunning = false;
      Serial.println("terminó el descanso, volvamos a ejercitarnos!!");
      taskDelayRunning = true;
      taskDelayStart = millis(); // empieza el delay
    digitalWrite(breakLampPin, LOW);         // enciende la luz
      digitalWrite(taskLampPin, HIGH);         // enciende la luz
      taskLightOn = true;
    }
  }
      
    if (message == 1){ // si el ejercicio está completo, apágalo!!
      breakDelayRunning = false;
      taskDelayRunning = false;
      if (taskLightOn){
      Serial.println("Ejercicio terminado!!, date una ducha por favor :)");
      digitalWrite(taskLampPin, LOW);          // apaga la luz z z z
      digitalWrite(breakLampPin, LOW);  
      taskLightOn = false;
          
      }
     Serial.println("Esperando por una rutina :-)"); 
     }
}