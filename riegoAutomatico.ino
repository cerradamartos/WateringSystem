int i;
int hum = analogRead(A0);
int humPercentage;
void setup() {
  Serial.begin(9600);
  Serial.println ("Iniciando el riego automatico...");
  delay (5000);
  pinMode (LED_BUILTIN, OUTPUT);
}

void loop() {
  humPercentage = map(hum, 0, 1023, 0, 100);
  Serial.println (humPercentage);
  delay(100);
  //Riego
  if (humPercentage > 0 && humPercentage < 70) {
    Serial.println ("Regando las plantas");
    delay(100);
    digitalWrite (LED_BUILTIN, HIGH);
    digitalWrite (6, HIGH);//El pin de la bomba de agua se enciende
  }
  //ERROR 1: Sensor mal colocado (fuera de la maceta, fallo de la bomba, etc.)
  else if (humPercentage == 0) {
    Serial.println ("ERROR 1: Sensor mal colocado");
    delay(100);
    digitalWrite (LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite (LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite (6, LOW);//El pin de la bomba de agua queda apagado
  }
  //Plantas regadas
  else if (humPercentage >= 70) {
    Serial.println ("Plantas regadas");
    delay(100);
    digitalWrite (LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite (LED_BUILTIN, LOW);
    delay(3000);
    digitalWrite (6, LOW);//El pin de la bomba de agua queda apagado
  }




}
