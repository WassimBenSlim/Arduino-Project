#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "rgb_lcd.h"
#include <NewPing.h>

rgb_lcd lcd;

#define DHTPIN A0
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const int lcdAddr = 0x27; // I2C address for the lcd

const int echoPin = 10; 
const int triggerPin = 9; 
NewPing sonar(triggerPin, echoPin);

int studentCount = 0;
int totalStudents = 10; 

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  pinMode(7,OUTPUT);
  dht.begin();
}

void loop() {
  // mouvement detection
  if (sonar.ping_cm() < 10) { 
    incrementStudentCount();
    digitalWrite(7,HIGH);
    delay(1000);
    digitalWrite(7,LOW);
}

  // temp reading
  float temperature = dht.readTemperature();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Etudiants: ");
  lcd.print(studentCount);
  lcd.setCursor(0, 1);
  lcd.print("Temperature: ");
  lcd.print(temperature);
  lcd.print(" C");

  delay(1000); 
}

void incrementStudentCount() {
  if (studentCount < totalStudents) {
    studentCount++;
  }

  float attendancePercentage = (float)studentCount / totalStudents * 100;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Etudiants: ");
  lcd.print(studentCount);
  lcd.print("/");
  lcd.print(totalStudents);
  lcd.setCursor(0, 1);
  lcd.print("Presence: ");
  lcd.print(attendancePercentage);
  lcd.print("%");

  delay(1000); 
}