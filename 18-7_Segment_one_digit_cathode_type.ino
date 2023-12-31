#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define BUTTON_PIN1 2
#define BUTTON_PIN2 4
#define BUTTON_RESTART 7

int i = -3;
int j = 1;
int counter = 0;
int HighScore = 0;
int Speed = 400;
void setup()
{
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  pinMode(BUTTON_RESTART, INPUT_PULLUP);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("HS:");
  lcd.setCursor(3,0);
  lcd.print(HighScore);
}
 
 
void loop()
{
  if(HighScore < counter){
    HighScore = counter;
    lcd.setCursor(0,0);
    lcd.print("HS:");
    lcd.setCursor(3,0);
    lcd.print(HighScore);
  }
  lcd.setCursor(7,0);
  lcd.print(counter);
  lcd.setCursor(8+i-j,1);
  lcd.print(" ");
  lcd.setCursor(8+i,1);
  lcd.print("o");
  
  if (i > 8 || i < -9){
    endGame();
  }
  
  byte buttonState1 = digitalRead(BUTTON_PIN1);
  byte buttonState2 = digitalRead(BUTTON_PIN2);
  lcd.setCursor(15,1);
  if (buttonState1 == HIGH){
    lcd.print(" ");
  }
  else{
    lcd.print("|");
    if(i == 7){
      j = -j;
      counter++;
      Speed -= 5;
    }
    else{
      endGame();
    }
    Serial.println("R");
  }
  lcd.setCursor(0,1);
  if (buttonState2 == HIGH){
    lcd.print(" ");
  }
  else{
    lcd.print("|");
    if(i == -8){
      j = -j;
      counter++;
      Speed -= 5;
    }
    else{
      endGame();
    }
  }
  i = i + j;
  delay(Speed);
}
void endGame()
{
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("game over");
    lcd.setCursor(7,1);
    lcd.print(counter);
    byte buttonState3 = digitalRead(BUTTON_RESTART);
    while(buttonState3 == HIGH){
      buttonState3 = digitalRead(BUTTON_RESTART);
      if (buttonState3 == LOW){
        i=-1;
        j=1;
        counter=0;
      }
      delay(1000);
    }
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("HS:");
    lcd.setCursor(3,0);
    lcd.print(HighScore);
}
