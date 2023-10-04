#define sensor A0 
//Aca conectamos el sensor de humedad en el arduino en el pin A0
int humedad = 0;
//aca la configuraciones de valores
int luz = OUTPUT;
// luz como salida de información

void setup()
//aca empiezan las configuraciones de inicio para que pueda funcionar el arduino
{
    pinMode(7,OUTPUT);
    //en el pin 7 del arduino conectamos la luz como salida de información
    Serial.begin(9600);
    //esto es super mega necesario, esta en todas las configuraciones es para que comience y funcione
}

void loop(){
//aca vamos a configurar lo que va a suceder repetitivamente
    int humedad = map(analogRead(sensor), 0, 1023, 0, 100);
    //se hace un mapeo de la lectura del sensor a porcentual
    Serial.print("Humedad: ");
     //el sensor de humedad lo va a leer
    Serial.print(humedad);
     //se va a mostrar la palabra humedad en el serial monitor
    Serial.println("%");

if(humedad>=45)
 //si la humedad es mayor o igual a 45% 
{
  digitalWrite(7,LOW);
    //si es mayor a 45% va a estar apagada la luz
}
else 
   //de lo contrario 
{
   digitalWrite(7,HIGH);
    //si es menor a 460 la luz va a estar prendida 
}
    delay(100);
    //esto va a suceder en un tiempo de 1 seg y se va a mostrar la información en serial monitor
}