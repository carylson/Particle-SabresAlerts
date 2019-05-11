PRODUCT_ID(9448);
PRODUCT_VERSION(2);

#include <neopixel.h>

#define PIXEL_COUNT 24
#define PIXEL_PIN D3
#define PIXEL_TYPE WS2812B
#define SPEAKER_PIN D2

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

void setup() {

  pinMode(SPEAKER_PIN, OUTPUT);

  strip.begin();
  strip.show();
  
  playScore();

  Particle.subscribe("lightning_score", scoreHandler, MY_DEVICES);

}

void scoreHandler(const char *event, const char *data) {
  
  playScore();
  
}

void playScore() {

  colorAll(strip.Color(255, 255, 255), 0);
  
  playMelody();
  
  rainbow(5);
  rainbow(5);
  rainbow(5);
  rainbow(5);
  rainbow(5);
  
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

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

// Set all pixels in the strip to rainbow, then wait (ms)
void rainbow(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Set all pixels in the strip to a solid color, then wait (ms)
void colorAll(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}