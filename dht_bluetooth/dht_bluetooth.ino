#include <SoftwareSerial.h>
#include<DHT.h>
#include<DHT_U.h>

SoftwareSerial plantSerial(7, 8); //RX, TX
int PIN = 3; 
int TIME = 5000;
float TEMC;
float TEMF;
float HUM;

char plantChar;

DHT dht(PIN, DHT22);

void setup() {
  Serial.begin(9600);
  Serial.println("uwu");

  plantSerial.begin(9600);
  plantSerial.println("xD");

  dht.begin();

}

void loop() {
  while(plantSerial.available()) {
      plantChar = plantSerial.read();
      Serial.println(plantChar);

  TEMC = dht.readTemperature(false);
  TEMF = dht.readTemperature(true);
  HUM = dht.readHumidity();
  Serial.println("-----------------------------");
  Serial.print("Temperature: ");
  Serial.print(TEMC, 1);
  Serial.print("C ");
  Serial.print(TEMF, 1);
  Serial.println("F");
  Serial.print("Humidity: ");
  Serial.print(HUM, 1);
  Serial.println("%");
  delay(TIME);
    }

  while(Serial.available()) {
      plantChar = Serial.read();
      plantSerial.println(plantChar);

  TEMC = dht.readTemperature(false);
  TEMF = dht.readTemperature(true);
  HUM = dht.readHumidity();
  plantSerial.println("-----------------------------");
  plantSerial.print("Temperature: ");
  plantSerial.print(TEMC, 1);
  plantSerial.print("C ");
  plantSerial.print(TEMF, 1);
  plantSerial.println("F");
  plantSerial.print("Humidity: ");
  plantSerial.print(HUM, 1);
  plantSerial.println("%");
  delay(TIME);

    }



  
}
