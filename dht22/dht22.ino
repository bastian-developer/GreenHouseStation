#include<DHT.h>
#include<DHT_U.h>

int PIN = 3; 
int TIME = 5000;
float TEMC;
float TEMF;
float HUM;

DHT dht(PIN, DHT22);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
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
