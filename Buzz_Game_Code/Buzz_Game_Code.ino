#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); 

const int input1Pin = 2; 
const int input2Pin = 3; 
const int input3Pin = 4; 
const int ledPinR = 5;    
const int ledPinG = 6;
const int buzz = 9;


bool counting = false; 
unsigned long startTime; 

void setup() {
  pinMode(input1Pin, INPUT_PULLUP);
  pinMode(input2Pin, INPUT_PULLUP);
  pinMode(input3Pin, INPUT_PULLUP);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(buzz, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("DESIGN BY EEE LAB");
  lcd.setCursor(1, 1);
  lcd.print("UTTARA UNIVERSITY");
  lcd.setCursor(1, 3);
  lcd.print("DEPERTMENT OF EEE");
  delay(3000);
  lcd.clear();

  lcd.setCursor(2, 0);
  lcd.print("You can Start");
  lcd.setCursor(2, 1);
  lcd.print("Best Of Luck Sir");
}

void loop() {
  int input1State = digitalRead(input1Pin);
  int input2State = digitalRead(input2Pin);
  int input3State = digitalRead(input3Pin);

  if (input1State == HIGH && !counting) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Your Time Star");
    digitalWrite(ledPinG, HIGH);
      delay(500);
      digitalWrite(ledPinG, LOW);
    
    counting = true;
    startTime = millis(); 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Counting...");
    
  }

  if (counting) {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - startTime;
    lcd.setCursor(0, 1);
    lcd.print(elapsedTime);
    lcd.print(" ms");

    if (input3State == LOW && input2State == HIGH && input1State == HIGH) {
     
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("CONGRATULATIONS");
      lcd.setCursor(0, 1);
      lcd.print("YOU HAVE SUCCEEDED");
      lcd.setCursor(0, 2);
      lcd.print("Your Time: ");
      lcd.print(elapsedTime / 1000); 
      lcd.print(" sec");
      counting = false;
      digitalWrite(ledPinR, LOW); 
      digitalWrite(ledPinG, HIGH);
    int melody[] = {
    262, 262, 294, 262, 349, 330, 262, 262,
    294, 262, 392, 349, 262, 262, 523, 440,
    349, 330, 294, 466, 466, 440, 349, 392, 349
  };

  int noteDuration = 200;

  for (int i = 0; i < 24; i++) {
    // Play the note
    tone(buzz, melody[i], noteDuration);
    delay(noteDuration + 50); 
  }

    } else if (input2State == LOW && input3State == HIGH && input1State == HIGH) {
      
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("OFFS SORRY SIR");
      lcd.setCursor(4, 1);
      lcd.print("TRY AGAIN or");
      lcd.setCursor(0, 3);
      lcd.print("Give chance 2 Others");
      counting = false;
      digitalWrite(ledPinR, HIGH);
      digitalWrite(ledPinG, LOW);
      digitalWrite(buzz,HIGH);
      delay(20000); 
      digitalWrite(ledPinR, LOW); 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ptress Reset Button");
      lcd.setCursor(0, 1);
      lcd.print("to start again");
      delay(5000);
    }
  }
}
