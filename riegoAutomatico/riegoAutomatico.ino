int i;
int hum = analogRead(A0);
int humPercentage;
void setup() {
  Serial.begin(9600);
  Serial.println ("Iniciando el riego automatico...");
  delay (5000);

}

void loop() {
  humPercentage = map(hum, 0, 1023, 0, 100);
  Serial.println (humPercentage);
  delay(5000);

  //Riego
  if (humPercentage > 0 && humPercentage < 70) {
    digitalWrite (6, HIGH);//El pin de la bomba de agua se enciende
    Serial.println ("Regando las plantas");
    digitalWrite (13, HIGH);
  }
  //ERROR 1: Sensor mal colocado (fuera de la maceta, fallo de la bomba, etc.)
  else if (humPercentage = 0) {
    Serial.println ("ERROR 1: Sensor mal colocado");
    digitalWrite (6, LOW);//El pin de la bomba de agua queda apagado
    digitalWrite (13, HIGH);
    delay(1000);
    digitalWrite (13, LOW);
    delay(1000);
  }
  //Plantas regadas
  else if (humPercentage >= 70) {
    digitalWrite (6, LOW);//El pin de la bomba de agua queda apagado
    Serial.println ("Plantas regadas");
    delay(5000);
    digitalWrite (13, HIGH);
    delay(5000);
  }
}
