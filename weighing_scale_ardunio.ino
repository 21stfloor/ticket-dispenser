#include <HX711_ADC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

HX711_ADC LoadCell(A0, A1); // dt pin 6, pin 7;
LiquidCrystal_I2C lcd(0x27, 20, 4);
const uint8_t TICKET_IN_PIN = A2;

void setup()
{
  LoadCell.begin();
  LoadCell.start(2000);
  LoadCell.setCalFactor(999.0);
  lcd.init();
  lcd.backlight();
  pinMode(TICKET_IN_PIN, INPUT);
}

void loop()
{
  LoadCell.update();
  float i = LoadCell.getData();
  lcd.setCursor(5, 1);
  lcd.print("Weight[g]:");
  lcd.setCursor(5, 2);
  lcd.print(i);

  int ticketCount = i / 10; // Calculate tickets based on 10g per 1 ticket

  // Print the Ticket Count on the LCD
  lcd.setCursor(5, 3);
  lcd.print("Ticket Count: " + String(ticketCount));

  if(ticketCount > 0){
    analogWrite(TICKET_IN_PIN, 0);
    delay(300 * ticketCount);
    analogWrite(TICKET_IN_PIN, 255);
    delay(5000);
}

