#include <LiquidCrystal.h>

#define pinSensorHumedad A0//define analog pin
#define VERSION 2
float sensorNoMap = 0;
int sensor = 0;

int pinLowAlarm = 12;//define digital pins
int pinHighAlarm = 13;

int E3 = 164.81;
int E4 = 329.63;
int C4 = 261.63;
int E5 = 659.25;

int aux = 0;

//Crear el objeto LCD con los números correspondientes (rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);
  pinMode(pinLowAlarm, OUTPUT);//define pin modes
  pinMode(pinHighAlarm, OUTPUT);

  Serial.println("Welcome to Humidity Sensor!");
  Serial.print(" An Arduino gardening system, that");
  #if VERSION == 1
  Serial.println(" prints the humidity of your soil through your Serial Monitor and");
  Serial.println(" has different warning signals.");
  Serial.println(" (Version 1)");
  #endif
  
  //To make the system more independant we use an external LCD to print data
  #if VERSION == 2
  Serial.println(" prints the humidity of your soil through your Serial Monitor and");
  Serial.println(" an LCD, and has different warning signals.");
  Serial.println(" (Version 2)");
  #endif
  
  //As a energy saving measure, we only print data if user requires it (see lcd.noDisplay() function)
  #if VERSION == 3
  Serial.println(" prints the humidity of your soil through your Serial Monitor and");
  Serial.println(" an LCD if you touch the Touch Sensor,");
  Serial.println(" and has different warning signals.");
  Serial.println(" (Version 3)");
  #endif

  #if VERSION == 4
   Serial.println(" prints the humidity of your soil through your Serial Monitor and");
  Serial.println(" an LCD if you touch the Touch Sensor,");
  Serial.println(" and has different warning signals,");
  Serial.println(" it also automatically waters your plants and could be solar powered!");
  Serial.println(" (Version 4)");
  #endif

 #if VERSION >= 2
  // Inicializar el LCD con el número de  columnas y filas del LCD
  lcd.begin(16, 2);
  // Escribimos el Mensaje en el LCD.
  lcd.print("    Welcome to Humidity Sensor!");
  for (int i=0; i<20; i++){
  lcd.scrollDisplayLeft();
  delay(300);
  }
  delay (2000);
  
  lcd.clear();
   
  lcd.print("Humidity value:");
  #endif
}

void loop() {
  sensorNoMap = analogRead(pinSensorHumedad);//Read the sensor
  sensor = map (sensorNoMap, 0, 1023, 0, 100);//Map to 0-100% humidity values
  
  //Define behaviour with different humidity values

  
  //EXTREMELY LOW HUMIDITY
  if (sensor <= 2) {
      if (aux != 1){
      aux = 1; //It only prints this the first time sensor <= 2% after being >2%
      lcd.setCursor(0, 0);
      lcd.print("  DANGER! Check sensor or soil");
      for (int i=0; i<30; i++){
          lcd.scrollDisplayLeft();
          delay(300);
      } 
      delay (2000);
      lcd.clear();
      lcd.print("Humidity value:");
      }
     digitalWrite(pinHighAlarm, HIGH);
      delay (250);
      digitalWrite(pinHighAlarm, LOW);
      delay (500);
  }

  //LOW HUMIDITY
    if (sensor > 2 && sensor < 50) {
      if (aux != 2){
        aux = 2; //It only prints this the first time sensor > 2% && sensor < 50% after being >50%
        lcd.setCursor(0, 0);
        lcd.print("   Time to water the plants!");
        for (int i=0; i<20; i++){
            lcd.scrollDisplayLeft();
            delay(300);
        } 
        delay (2000);
        lcd.clear();
        lcd.print("Humidity value:");
      }
      
      digitalWrite(pinLowAlarm, HIGH);
      delay (500);
      digitalWrite(pinLowAlarm, LOW);
      delay (1000);
    }

  //HIGH HUMIDITY
    if (sensor > 77){
      if (aux != 3){
        lcd.setCursor(0,0);
        lcd.print("   DANGER! Humidity too high");
        for (int i=0; i < 15 ; i++){
          lcd.scrollDisplayLeft();
          delay (300);
        }
        delay (2000);
        lcd.clear();
        lcd.print("Humidity value:");
        aux = 3;
      }
           
      digitalWrite(pinLowAlarm, HIGH);
      delay (500);
      digitalWrite(pinLowAlarm, LOW);
      delay (1000);
    }
    if (sensor > 50 && sensor < 77){
       if (aux != 0){
        lcd.setCursor(0,0);
        lcd.print("   Everything's alright now!");
        for (int i=0; i < 20 ; i++){
          lcd.scrollDisplayLeft();
          delay (300);
        }
        delay (2000);
        lcd.clear();
        lcd.print("Humidity value:");
      }
      aux = 0;//So that it prints the intial alarm messages
    }
    //VERSION >= 1//
    #if VERSION >= 1
    //Print Humidity Data on Computer
    Serial.print("Humidity value: "); 
    Serial.print(sensor); 
    Serial.println(" %");
    //VERSION >= 1//
     #endif
    
    //VERSION >= 2//
    #if VERSION >= 2
    // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
    lcd.setCursor(0, 1);
    // Escribimos el valor de la humedad en la segunda fila
    lcd.print(sensor);
    lcd.print(" %");
    //VERSION >= 2//
    #endif
  
    delay (5000);

    /*tone(pinHighAlarm, E3, 1000);
    tone(pinHighAlarm, E4, 1000);*/
  }
