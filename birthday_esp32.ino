#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buzzerPin = 12; 
const int led1Pin = 14; 
const int led2Pin = 27; 

#define NUM_OF_NOTES 28
int NOTE_SEQ[NUM_OF_NOTES] = {
  NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_F5, NOTE_E5, PAUSE,
  NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_G5, NOTE_F5, PAUSE,
  NOTE_C5, NOTE_C5, NOTE_C6, NOTE_A5, NOTE_F5, NOTE_E5, NOTE_D5, PAUSE,
  NOTE_AS5, NOTE_AS5, NOTE_A5, NOTE_F5, NOTE_G5, NOTE_F5
};

int NOTE_LEN[NUM_OF_NOTES] = {
  4, 2, 8, 8, 8, 16, 50, // 50 millis for the first pause
  4, 2, 8, 8, 8, 16, 100, // 100 millis for the second pause
  4, 2, 8, 8, 8, 8, 16, 150, // 150 millis for the third pause
  4, 2, 8, 8, 8, 20
};

int TEMPO = 65;

void setup() {
  pinMode(buzzerPin, OUTPUT); 
  pinMode(led1Pin, OUTPUT); 
  pinMode(led2Pin, OUTPUT); 

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0); 
  lcd.print("Happy Birthday");
  lcd.setCursor(0, 1); 
  lcd.print("Arif <3");
}

void loop() {
  playHappyBirthday();
  delay(2000); // Delay before repeating the song
}

void playHappyBirthday() {
  for (int thisNote = 0; thisNote < NUM_OF_NOTES; thisNote++) {
    int noteDuration = NOTE_LEN[thisNote] * TEMPO;
    if (NOTE_SEQ[thisNote] != PAUSE) {
      tone(buzzerPin, NOTE_SEQ[thisNote]);
      if (thisNote % 2 == 0) {
        digitalWrite(led1Pin, HIGH);
        digitalWrite(led2Pin, LOW);
      } else {
        digitalWrite(led1Pin, LOW);
        digitalWrite(led2Pin, HIGH);
      }
      delay(noteDuration);
      noTone(buzzerPin);
    } else {
      delay(NOTE_LEN[thisNote]);
    }

    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    
    // Delay between notes following TEMPO variable's dictate
    delay(TEMPO);
  }
}
