import processing.serial.*;
import processing.sound.*;

Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port
SoundFile file;

String inString ="Primer inicio, sin data aun...";  // Input string from serial port
String[] audios={"audio01.wav", "audio02.wav", "audio03.wav", "audio04.wav", "audio05.wav"};


void setup()
{
  size(400, 200);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[0];
  printArray(Serial.list());
  myPort = new Serial(this, portName, 9600);
  fill(255);
  textSize(15);
}

void draw()
{
  background(0);
  if ( myPort.available() > 0) {  // If data is available,
    val = myPort.read();         // read it and store it in val
    println(val);
    

    if (val == 2) {
      int indice = int(random(5));
      inString =  str(val)  + " - Reproduciendo Audio0" + str(indice+1) + ".wav";
      print("audio0");
      println(indice);
      file = new SoundFile(this, audios[indice]);
      file.play();
    } else {
      inString = str(val)  + " -  esperando...";

    }
   
  }
   text("recibido: " + inString, 10, 50);
}
