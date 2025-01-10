#include "alert.h"
#include <Arduino.h>

const int buzPin = 15;
enum class tones {
  NOTE_C4 = 262,
  NOTE_D4 = 294,
  NOTE_E4 = 330,
  NOTE_F4 = 349,
  NOTE_G4 = 392,
  NOTE_A4 = 440,
  NOTE_B4 = 494,
  NOTE_C5 = 523
};

const tones melody[8] = {
  tones::NOTE_C4, tones::NOTE_D4, tones::NOTE_E4, tones::NOTE_F4,
  tones::NOTE_G4, tones::NOTE_A4, tones::NOTE_B4, tones::NOTE_C5
};
const int noteDurations[8] = {4, 4, 4, 4, 4, 4, 4, 4}; // Quarter notes


void initBuzzer() {
  pinMode(buzPin, OUTPUT);
}

void buzzerStart() {
      for (int i = 0; i < 8; i++) {
        int noteDuration = 1000 / noteDurations[i];
        tone(buzPin, static_cast<int>(melody[i]), noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(buzPin);
      }
    }

void buzzerStop() {
  noTone(buzPin);
}