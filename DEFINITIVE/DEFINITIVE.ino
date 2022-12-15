//Import Libraries
#include <SoftwareSerial.h>
#include<DHT.h>
#include<DHT_U.h>

//Definition of each musical note
#define NOTE_B0  31  
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//Pin Declaration
int pinHW103A = A0;
int pinDHT22 = 3;
int pinRelay2 = 4;
int pinRelay1 = 5;
int pinBluetoothRX = 7;
int pinBluetoothTX = 8;
int pinWaterPump = 11;
int pinPasiveBuzzer = 13;

//Bluetooth Instance
SoftwareSerial plantSerial(pinBluetoothRX, pinBluetoothTX);

//DHT-22 Instance
DHT dht(pinDHT22, DHT22);

//Program Variables
char incomingValue;
float moisture;
float temperature;
float humidity;
int _moisture;
int _temperature;
int _humidity;

//Melodies
int turnOffMelody[] = {   
  NOTE_A4
};
int turnOffNoteLenght[] = {    
  8
};

int turnOnMelody[] = {   
  NOTE_A4, NOTE_E5
};
int turnOnNoteLenght[] = {    
  8, 8
};

int wakeUpMelody[] = {   
  NOTE_E5, NOTE_C5, NOTE_E5, NOTE_C5 
};
int wakeUpNoteLenght[] = {    
  8, 8, 8, 8
};




void setup() 
{

  //Serial Communication
  Serial.begin(9600);
  Serial.println("Hello Terminal");

  //Bluetooth Communication
  plantSerial.begin(9600);
  plantSerial.println("Hello App");

  //DHT-22 Sensor Started
  dht.begin();

  //Pin Modes
  pinMode(pinWaterPump, OUTPUT);
  pinMode(pinPasiveBuzzer, OUTPUT);
  pinMode(pinRelay1, OUTPUT);
  pinMode(pinRelay2, OUTPUT);

  //Starting Melody
  playWakeUpMusic();
}

void loop() {

  while(plantSerial.available())
  { 
    incomingValue = plantSerial.read();
    
    switch (incomingValue)
    {
      case '1':
        turnOnRelay1();
        playTurnOffSound();
        break;
      case '2':
        turnOnRelay2();
        playTurnOffSound();
        break;
      case '3':
        turnOffRelay1();
        playTurnOnSound();
        break;
      case '4':
        turnOffRelay2();
        playTurnOnSound();
        break;
      case '5':
        turnOnWaterPump();
        playTurnOnSound();
        break;
      case '6':
        turnOffWaterPump();
        playTurnOffSound();
        break;
      case '7':
        _readMoisture();
        break;
      case '8':
        _readTemperature();
        break;
      case '9':
        _readHumidity();
        break;
    }
  }
  
}

//HW-103A Sensor
void _readMoisture() 
{
  moisture = analogRead(pinHW103A);
  moisture = 100 - ((moisture * 100) / 1024);
  _moisture = round(moisture);
  plantSerial.println("M" + String(_moisture));
  delay(500);
}

//DHT-22 Sensor
void _readTemperature() 
{
  temperature = dht.readTemperature();
  _temperature = round(temperature);
  plantSerial.println("T" + String(_temperature));
  delay(500);
}
void _readHumidity() 
{
  humidity = dht.readHumidity();
  _humidity = round(humidity);
  plantSerial.println("H" + String(_humidity));
  delay(500);
}

//Relay 1
void turnOnRelay1()
{
  digitalWrite(pinRelay1, HIGH);
}
void turnOffRelay1()
{
  digitalWrite(pinRelay1, LOW);
}

//Relay 2
void turnOnRelay2()
{
  digitalWrite(pinRelay2, HIGH);
}
void turnOffRelay2()
{
  digitalWrite(pinRelay2, LOW);
}

//Water Pump
void turnOnWaterPump()
{
  digitalWrite(pinWaterPump, HIGH);
}
void turnOffWaterPump()
{
  digitalWrite(pinWaterPump, LOW);
}

//Music
void playWakeUpMusic() {
  for (int i = 0; i < 4; i++) {     // note quantity
    int lenght = 1500 / wakeUpNoteLenght[i];    // note lenght in miliseconds
    tone(pinPasiveBuzzer, wakeUpMelody[i], lenght);  // executes tone with lenght
    int pause = lenght * 1.30;      
    delay(pause);         
    noTone(pinPasiveBuzzer);        // stop the buzzer
  }
}

void playTurnOnSound() {
  for (int i = 0; i < 2; i++) {     // note quantity
    int lenght = 1500 / turnOnNoteLenght[i];    // note lenght in miliseconds
    tone(pinPasiveBuzzer, turnOnMelody[i], lenght);  // executes tone with lenght
    int pause = lenght * 1.30;      
    delay(pause);         
    noTone(pinPasiveBuzzer);        // stop the buzzer
  }
}

void playTurnOffSound() {
  for (int i = 0; i < 1; i++) {     // note quantity
    int lenght = 1500 / turnOffNoteLenght[i];    // note lenght in miliseconds
    tone(pinPasiveBuzzer, turnOffMelody[i], lenght);  // executes tone with lenght
    int pause = lenght * 1.30;      
    delay(pause);         
    noTone(pinPasiveBuzzer);        // stop the buzzer
  }
}
