#include <Adafruit_Sensor.h>
#include <DHT.h>

#include <LiquidCrystal.h>



LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define MQ_2Pin A0
const int MQ_135Pin = A1; 
int threshold = 250;

#define DHT11_PIN 13
DHT dht(DHT11_PIN,DHT11);



void setup() {
    lcd.begin(16, 2);
    dht.begin();
    pinMode(MQ_2Pin, INPUT_PULLUP);
    pinMode(MQ_135Pin, INPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);

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
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);

  lcd.setCursor(0, 0);
  lcd.print("MQ2:Detect Gas");

  lcd.setCursor(0, 1);
  lcd.print("MQ135:Detect Gas");

  delay(500);
  
  
}
else if(gas_2value==HIGH&&gas_135value<threshold)
{
  
  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);

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
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);

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
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);

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

