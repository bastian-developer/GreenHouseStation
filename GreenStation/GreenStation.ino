#include <SoftwareSerial.h>
#include<DHT.h>


SoftwareSerial plantSerial(7, 8); //RX, TX

char plantChar;
char serialChar;

int dht22Pin = 3;

int moisture_signal = A0;


DHT dht(dht22Pin, DHT22);

void setup() {
  Serial.begin(9600);
  Serial.println("uwu");

  plantSerial.begin(9600);
  plantSerial.println("xD");

}

void loop() {

  int moisture;

  float temp, hum;


  moisture = analogRead(moisture_signal);

  dht.read(dht22Pin);
  temp = dht.readTemperature();
  hum = dht.readHumidity();

  Serial.println("--------------------");
  plantSerial.println("--------------------");

  Serial.println("T: " + String(temp) + "°C");
  plantSerial.println("T: " + String(temp) + "°C");

  Serial.println("H: " + String(hum) + "%");
  plantSerial.println("H: " + String(hum) + "%");

  Serial.println("M: " + String(moisture));
  plantSerial.println("M: " + String(moisture));
  

  delay(5000);

}
