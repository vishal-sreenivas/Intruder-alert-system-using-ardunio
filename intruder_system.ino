#include <Servo.h>
#include <DHT.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define DHT_PIN 2
#define DHT_TYPE DHT11
#define BUZZER 6
#define LED 7
#define SERVO_PIN 5

DHT dht(DHT_PIN, DHT_TYPE);
Servo servo;

void setup() {
    Serial.begin(9600);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(LED, OUTPUT);
    servo.attach(SERVO_PIN);
    servo.write(0);  // Initial position

    dht.begin();
}

void loop() {
    long duration;
    int distance;

    // Trigger Ultrasonic Sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance < 20) { // Intruder detected within 20cm
        digitalWrite(BUZZER, HIGH);
        digitalWrite(LED, HIGH);
        servo.write(90);  // Move servo to 90 degrees (simulate door closing)
        Serial.println("Intruder Alert!");
        delay(1000);
    } else {
        digitalWrite(BUZZER, LOW);
        digitalWrite(LED, LOW);
        servo.write(0);  // Reset servo to initial position
    }

    delay(500);
}
