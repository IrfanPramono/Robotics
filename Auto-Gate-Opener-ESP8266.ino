#include <ESP8266WiFi.h>
#include <Servo.h>

#define TRIG_PIN D5
#define ECHO_PIN D6
#define SERVO_PIN D7

Servo portalServo;

long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2; // Convert to cm
  return distance;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  portalServo.attach(SERVO_PIN);
  portalServo.write(0); // Portal awal tertutup
}

void loop() {
  long distance = readDistanceCM();
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < 20) {
    portalServo.write(90); // Buka portal
    delay(3000);            // Tunggu 3 detik
  } else {
    portalServo.write(0);  // Tutup portal
  }

  delay(500);
}
