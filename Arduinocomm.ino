#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // include the library for I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // initialize the LCD with I2C address 0x27, 16 columns and 2 rows

char t;

void setup() {
  pinMode(13, OUTPUT);   // left motors forward
  pinMode(12, OUTPUT);   // left motors reverse
  pinMode(11, OUTPUT);   // right motors forward
  pinMode(10, OUTPUT);   // right motors reverse
  pinMode(9, OUTPUT);    // led
  Serial.begin(9600);
  lcd.init();            // initialize the LCD
  lcd.backlight();       // turn on the backlight of the LCD
  lcd.setCursor(0, 0);   // set the cursor to the top left corner
  lcd.print("Arduino Car"); // print the name of the car on the LCD
}

void loop() {
  if (Serial.available()) {
    t = Serial.read();
    Serial.println(t);
    lcd.setCursor(0, 1); // set the cursor to the second row
    switch (t) {
      case 'F': // move forward
        lcd.print("Forward");
        digitalWrite(13, HIGH);
        digitalWrite(11, HIGH);
        break;
      case 'B': // move backward
        lcd.print("Backward");
        digitalWrite(12, HIGH);
        digitalWrite(10, HIGH);
        break;
      case 'L': // turn right (left side motors rotate in forward direction, right side motors don't rotate)
        lcd.print("Right");
        digitalWrite(11, HIGH);
        break;
      case 'R': // turn left (right side motors rotate in forward direction, left side motors don't rotate)
        lcd.print("Left");
        digitalWrite(13, HIGH);
        break;
      case 'W': // turn led on
        lcd.print("Led On");
        digitalWrite(9, HIGH);
        break;
      case 'w': // turn led off
        lcd.print("Led Off");
        digitalWrite(9, LOW);
        break;
      case 'S': // stop (all motors stop)
        lcd.print("Stop");
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        break;
    }
  }
  delay(100);
}