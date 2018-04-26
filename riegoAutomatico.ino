

void setup() {
  Serial.begin(9600);
  Serial.println ("Iniciando el riego automatico...");
  delay (5000);
  pinMode (LED_BUILTIN, OUTPUT);
  pinMode (6, OUTPUT);//Bomaba de agua
  pinMode (9, OUTPUT);//Zumbador o led
  pinMode (A0, INPUT);//Sensor de humedad
}

void loop() {
  int hum = analogRead(A0);
  int humPercentage;
  humPercentage = map(hum, 0, 1023, 0, 100);
  Serial.println (humPercentage);
  delay(100);


  //Riego
  if (humPercentage > 10 && humPercentage < 60) {
    Serial.println ("Regando las plantas");
    delay(100);
    digitalWrite (LED_BUILTIN, HIGH);
    digitalWrite (6, HIGH);//El pin de la bomba de agua se enciende
    digitalWrite (9, LOW);

  }
  //ERROR 1: Sensor mal colocado
  else if (humPercentage == 0) {
    Serial.println ("ERROR 1: Sensor mal colocado");
    delay(100);
    digitalWrite (LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite (LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite (6, LOW);//El pin de la bomba de agua queda apagado
    digitalWrite (9, HIGH);
    delay(1000);
    digitalWrite (9, LOW);
    delay(1000);//El zumbador se enciende


  }
  //ERROR 2: Fallo en la bomba
  else if (humPercentage >= 95) {
    Serial.println ("ERROR 2: Fallo en la bomba");
    delay(100);
    digitalWrite (LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite (LED_BUILTIN, LOW);
    delay(100);
    digitalWrite (6, LOW);//El pin de la bomba de agua queda apagado
    digitalWrite (9, HIGH);//El zumbador se enciende

  }
  //Plantas regadas
  else if (humPercentage >= 60 || humPercentage < 95) {
    Serial.println ("Plantas regadas");
    delay(100);
    digitalWrite (LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite (LED_BUILTIN, LOW);
    delay(3000);
    digitalWrite (6, LOW);//El pin de la bomba de agua queda apagado
    digitalWrite (9, LOW);


  }
}
