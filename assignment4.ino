#include <Wire.h>              
#include <LiquidCrystal_I2C.h> 
#include <Keypad.h>            

LiquidCrystal_I2C lcd(0x27, 16, 2); 
const byte ROWS = 4; 
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

const int ledPin = 13; 
int blinkCount = 0; 

void setup() {
  lcd.begin(); 
  lcd.backlight(); 
  pinMode(ledPin, OUTPUT); 
  randomSeed(analogRead(0)); 
  blinkRandom(); 

void loop() {
  char key = keypad.getKey(); 
  if (key == '#') { 
    lcd.clear(); 
    lcd.setCursor(0, 0); 
    lcd.print("Please Wait..."); 
    lcd.setCursor(0, 1); 
    
    delay(1000); 
    if (blinkCount == getNumber()) { 
      lcd.clear(); 
      lcd.setCursor(0, 0); 
      lcd.print("Correct!"); 
    } else { 
      lcd.clear(); 
      lcd.setCursor(0, 0); 
      lcd.print("Incorrect!"); 
    }
    delay(1000); 
    blinkRandom(); 
  }
}
int getNumber() {
  int number = 0; 
  char key = keypad.getKey(); 
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Enter number:"); 
  while (key != '#') { 
    if (key >= '0' && key <= '9') { 
      number = number * 10 + (key - '0');
      lcd.setCursor(0, 1); 
      lcd.print("                "); 
      lcd.setCursor(0, 1); 
      lcd.print(number); 
    key = keypad.getKey(); 
  }
  return number; 
}


void blinkRandom() {
  blinkCount = random(1, 15); 
  for (int i = 0; i < blinkCount; i++) { 
    digitalWrite(ledPin, HIGH); 
    delay(250); 
    digitalWrite(ledPin, LOW); 
    delay(250); 
  }
}
