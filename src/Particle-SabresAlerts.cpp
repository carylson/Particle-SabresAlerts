#include "application.h"
#line 1 "/Users/carylson/Documents/Particle/Particle-SabresAlerts/src/Particle-SabresAlerts.ino"
void setup();
void scoreHandler(const char *event, const char *data);
void playScore();
void playMelody();
#line 1 "/Users/carylson/Documents/Particle/Particle-SabresAlerts/src/Particle-SabresAlerts.ino"
PRODUCT_ID(9438);
PRODUCT_VERSION(1.1);

#include <neopixel.h>

#define PIXEL_COUNT 24
#define PIXEL_PIN D3
#define PIXEL_TYPE WS2812B

#define SPEAKER_PIN D2

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

#include "utils/Neopixel.ino"

void setup() {

  // Init speaker...
  pinMode(SPEAKER_PIN, OUTPUT);

  // Init Neopixels...
  strip.begin();
  strip.show();
  
  // Startup procedure...
  playScore();

  Particle.subscribe("sabres_score", scoreHandler);

}

void scoreHandler(const char *event, const char *data) {
  
  playScore();
  
}

void playScore() {
  colorAll(strip, strip.Color(255, 255, 255), 0);
  playMelody();
  rainbow(strip, 5);
  rainbow(strip, 5);
  rainbow(strip, 5);
  rainbow(strip, 5);
  rainbow(strip, 5);
  strip.clear();
  strip.show();
}

void playMelody() {
    tone(SPEAKER_PIN, 523); //C
    delay(150);
    tone(SPEAKER_PIN, 659); //E
    delay(150);
    tone(SPEAKER_PIN, 784); //G
    delay(150);
    tone(SPEAKER_PIN, 880); //A
    delay(300);
    tone(SPEAKER_PIN, 659); //E
    delay(150);
    tone(SPEAKER_PIN, 880); //A
    delay(600);
    noTone(SPEAKER_PIN);
}