#include <Servo.h>

Servo gateServo;

// Ultrasonic sensor pins
const int trigPin = 6;
const int echoPin = 7;

// Servo pin
const int servoPin = 9;

// Distance threshold (in cm)
const int thresholdDistance = 20;   // Gate opens when car is within 20 cm

void setup() {
  gateServo.attach(servoPin);
  gateServo.write(0);  // Gate initially closed position
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  long duration, distance;

  // Triggering ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reading echo time
  duration = pulseIn(echoPin, HIGH);

  // Convert to distance (in cm)
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // If car is close → open gate
  if (distance > 0 && distance <= thresholdDistance) {
    gateServo.write(90);   // Open gate
    delay(3000);           // Keep gate open for 3 sec
  } 
  else {
    gateServo.write(0);    // Close gate
  }
delay(200);

}
