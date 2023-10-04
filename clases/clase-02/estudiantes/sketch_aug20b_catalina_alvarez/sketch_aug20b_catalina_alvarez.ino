void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 int ADC_SHARP=ADC0_promedio(20);
  if(ADC_SHARP>195)
  {
    digitalWrite(13, HIGH);
    Serial.print("Objeto Detectado:");
  }
  else
  {
    digitalWrite(13, LOW);
    Serial.print("Objeto ausente:");
  }
  
  Serial.println(ADC_SHARP);
  delay(100);
}

int ADC0_promedio(int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(A0);
  }  
  return(suma/n);
}
