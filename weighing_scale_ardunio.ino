#include <HX711_ADC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h> // Include the Servo library

HX711_ADC LoadCell(A0, A1); // dt pin 6, pin 7;
LiquidCrystal_I2C lcd(0x27, 20, 4);
const uint8_t TICKET_IN_PIN = A2;
const uint8_t BUTTON_PIN = 8; // Digital pin for the push button

Servo servo; // Create a servo object

boolean isDispensing = false; // Variable to track ticket dispensing status

void setup() {
  LoadCell.begin();
  LoadCell.start(2000);
  LoadCell.setCalFactor(999.0);
  lcd.init();
  lcd.backlight();
  pinMode(TICKET_IN_PIN, INPUT); // Set TICKET_IN_PIN as an output
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set BUTTON_PIN as input with pull-up resistor
  servo.attach(9); // Attach the servo to digital pin 9
  servo.write(0); // Initialize the servo to 0 degrees (leftmost position)
}

void loop() {
  LoadCell.update();
  float i = LoadCell.getData();
  
  lcd.setCursor(5, 1);
  lcd.print("Weight[g]:");
  lcd.setCursor(5, 2);
  lcd.print(i);

  int ticketCount = i / 10; // Calculate tickets based on 10g per 1 ticket

  // Print the Ticket Count on the LCD
  lcd.setCursor(3, 3);
  lcd.print("Ticket Count: " + String(ticketCount) + "  ");

  if (digitalRead(BUTTON_PIN) == LOW && !isDispensing && ticketCount > 0) {
    lcd.setCursor(0, 0);
    lcd.print("Taking the trash");
    // Turn the servo to 45 degrees (right position)
    servo.write(45);
    delay(2000); // Adjust this delay to allow time for the servo to reach the desired position
    // Turn the servo back to the initial position (0 degrees)
    servo.write(0);
    delay(2000); // Adjust this delay to allow time for the servo to reach the initial position

    lcd.setCursor(0, 0);
    lcd.print("Dispensing tickets");
    while (ticketCount > 0) {
      isDispensing = true;
      analogWrite(TICKET_IN_PIN, 0);
      delay(300);
      analogWrite(TICKET_IN_PIN, 255);
      ticketCount--;
      delay(300);
    }

    
    lcd.setCursor(0, 0);
    lcd.print("                    ");
    isDispensing = false; // Reset the dispensing status
  }
}
