
/*Humidity sensor lib*/
#include <Adafruit_Sensor.h>
#include <DHT.h>
/*LCD Lib*/
#include <LiquidCrystal.h>

const int RS = 12, EN = 11, D4 = 2, D5 = 3, D6 = 4, D7 = 5;
const int MQ_2Pin =A0;
const int MQ_135Pin = A1; 
const int DHT11_PIN =13;
const int G_LED = 6;
const int R_LED1 = 7;
const int R_LED2 = 8;




int threshold = 250;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
DHT dht(DHT11_PIN,DHT11);



void setup() {
    lcd.begin(16, 2);
    dht.begin();
    pinMode(MQ_2Pin, INPUT_PULLUP);
    pinMode(MQ_135Pin, INPUT);
    pinMode(G_LED, OUTPUT);
    pinMode(R_LED1, OUTPUT);
    pinMode(R_LED2, OUTPUT);

    lcd.setCursor(6, 0);
    lcd.print("Hello");
    delay(500);

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Environment");
    lcd.setCursor(4, 1);
    lcd.print("Monitor");
    delay(500);
    lcd.clear();
    
}

void loop() {
int gas_135value = analogRead(MQ_135Pin);
int gas_2value = digitalRead(MQ_2Pin);
int temp=dht.readTemperature();
int hum=dht.readHumidity();

lcd.clear();
if(gas_2value==HIGH&&gas_135value>threshold)
{
  digitalWrite(R_LED2, HIGH);
  digitalWrite(R_LED1, HIGH);
  digitalWrite(G_LED, LOW);

  lcd.setCursor(0, 0);
  lcd.print("MQ2:Detect Gas");

  lcd.setCursor(0, 1);
  lcd.print("MQ135:Detect Gas");

  delay(500);
  
  
}
else if(gas_2value==HIGH&&gas_135value<threshold)
{
  
  digitalWrite(R_LED2, LOW);
  digitalWrite(R_LED1, HIGH);
  digitalWrite(G_LED, LOW);

  lcd.setCursor(0, 0);
  lcd.print("MQ-2 : Detected");

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.setCursor(5, 1);
  lcd.print(temp);

  lcd.setCursor(9, 1);
  lcd.print("Humi:");
  lcd.setCursor(14, 1);
  lcd.print(hum);

  delay(500);
  
  
  
}
else if(gas_2value==LOW&&gas_135value>threshold)
{
  digitalWrite(R_LED2, HIGH);
  digitalWrite(R_LED1, LOW);
  digitalWrite(G_LED, LOW);

  lcd.setCursor(0, 0);
  lcd.print("MQ-135 :Detected");

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.setCursor(5, 1);
  lcd.print(temp);

  lcd.setCursor(9, 1);
  lcd.print("Humi:");
  lcd.setCursor(14, 1);
  lcd.print(hum);

  delay(500);
  
  
  
}else {
  digitalWrite(R_LED2, LOW);
  digitalWrite(R_LED1, LOW);
  digitalWrite(G_LED, HIGH);

  lcd.setCursor(0, 0);
  lcd.print("MQ-2:G&&MQ135:G");

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.setCursor(5, 1);
  lcd.print(temp);

  lcd.setCursor(9, 1);
  lcd.print("Humi:");
  lcd.setCursor(14, 1);
  lcd.print(hum);

  delay(500);
    
}

}

