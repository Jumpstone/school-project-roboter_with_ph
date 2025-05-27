#include <Servo.h>

Servo myServo;  // Servo-Objekt erstellen
const int servoPin = 10; // Pin des Servos
const int rightPhotoResistor = A4; // Pin des rechten Photowiderstands
const int leftPhotoResistor = A5; // Pin des linken Photowiderstands

void setup() {
  myServo.attach(servoPin); // Servo mit Pin verbinden
  myServo.write(45); // Startwinkel auf 45 Grad setzen (neue "0 Grad"-Position)
  pinMode(leftPhotoResistor, INPUT);
  pinMode(rightPhotoResistor, INPUT);
  
  Serial.begin(9600); // Seriellen Monitor starten
}

void loop() {
  int leftValue = analogRead(leftPhotoResistor); // Linken Sensor auslesen
  int rightValue = analogRead(rightPhotoResistor); // Rechten Sensor auslesen
  
  int difference = leftValue - rightValue; // Unterschied berechnen

  // Servo bewegen basierend auf der Differenz
  static int currentAngle = 45; // Startposition auf 45 Grad setzen (neue "0 Grad"-Position)
  int adjustment = map(difference, -1023, 1023, -45, 45); // Unterschied in Bewegung umwandeln (max. 45 Grad nach links und rechts)
  currentAngle = constrain(currentAngle + adjustment, 0, 90); // Winkel begrenzen (0-90 Grad)
  
  myServo.write(currentAngle); // Servo bewegen

  // Daten im seriellen Monitor ausgeben
  Serial.print("Left Value: ");
  Serial.print(leftValue);  
  Serial.print(" | Right Value: ");
  Serial.print(rightValue);
  Serial.print(" | Difference: ");
  Serial.print(difference);
  Serial.print(" | Servo Angle: ");
  Serial.println(currentAngle);

  delay(50); // Kurze Verzögerung für Stabilität
}
