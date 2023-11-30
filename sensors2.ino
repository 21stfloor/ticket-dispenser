#include <Servo.h>

Servo tap_servo1;
Servo tap_servo2;

int sensor_pin1 = A0;  // Analog pin for the first sensor
int sensor_pin2 = A1;  // Digital pin for the second sensor
int sensor_pin3 = A2;  // Digital pin for the third sensor
int tap_servo_pin1 = 5;
int tap_servo_pin2 = 6;
int LED_PIN = 8;
int val1;
int val2;
int val3;
int activeServo = 0;

void setup() {
  pinMode(sensor_pin1, INPUT);
  pinMode(sensor_pin2, INPUT);
  pinMode(sensor_pin3, INPUT);
  pinMode(LED_PIN, OUTPUT);
  tap_servo1.attach(tap_servo_pin1);
  tap_servo2.attach(tap_servo_pin2);
  Serial.begin(9600);

  tap_servo1.write(0);
  tap_servo2.write(180);
}

void loop() {
  val2 = analogRead(sensor_pin2);
  val3 = analogRead(sensor_pin3);

  // Add a delay of 2 seconds for sensor_pin1 only if val2 and val3 are both less than or equal to 1
  // if (val2 <= 1 && val3 <= 1) {
  //   delay(2000); // 2 seconds
  // }

  // if(activeServo == 1){
    
  // }

  if(tap_servo1.read() == 0 && activeServo != 1){
    if (val2 > 1 || val3 > 1) {
      tap_servo2.write(0);//close
      activeServo = 2;
    } else{
      tap_servo2.write(180);
      activeServo = 0;
    }
  }

  if(tap_servo2.read() == 180 && activeServo != 2){
    
    if (val1 > 1) {
      tap_servo1.write(0);//close
      activeServo = 0;
    } else{
      
        
        tap_servo1.write(180);
        activeServo = 1;
      
    }
  }

  // Serial.print("active servo:");
  // Serial.println(activeServo);
  Serial.print("Servo1:");
  Serial.println(tap_servo1.read());
  Serial.println("");
  Serial.println("");
  Serial.print("Servo2:");
  Serial.println(tap_servo2.read());

  // Check if neither servo is moving and light the LED
  if (tap_servo1.read() == 0 && tap_servo2.read() == 180) {
    digitalWrite(LED_PIN, HIGH);  // Turn on the LED
  } else {
    digitalWrite(LED_PIN, LOW);  // Turn off the LED
  }

  delay(5000);
  if(activeServo != 2){
    
    val1 = analogRead(sensor_pin1);
  }
  // else{
  //   val1 = 0;
  // }
}
