PRODUCT_ID(9438);
PRODUCT_VERSION(1);

#include <neopixel.h>

#define PIXEL_COUNT 24
#define PIXEL_PIN D3
#define PIXEL_TYPE WS2812B

#define SPEAKER_PIN D2

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

// Prototypes for local build, ok to leave in for Build IDE
void rainbow(uint8_t wait);
void colorAll(uint32_t c, uint8_t wait);
uint32_t Wheel(byte WheelPos);

void setup() {

  // Init speaker...
  pinMode(SPEAKER_PIN, OUTPUT);

  // Init Neopixels...
  strip.begin();
  strip.show();
  
  // Startup procedure...
  playScore();

  // Subscribe will listen for the event sabres_score and, when it finds it, will run the function scoreHandler()...
  Particle.subscribe("sabres_score", scoreHandler);

}

void scoreHandler(const char *event, const char *data) {
    
  /*
  Particle.subscribe handlers are void functions, which means they don't return anything.
  They take two variables-- the name of your event, and any data that goes along with your event.
  In this case, the event will be "buddy_unique_event_name" and the data will be "intact" or "broken"

  Since the input here is a char, we can't do
     data=="intact"
    or
     data=="broken"

  chars just don't play that way. Instead we're going to strcmp(), which compares two chars.
  If they are the same, strcmp will return 0.
  */
  
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

// Set all pixels in the strip to a solid color, then wait (ms)
void colorAll(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}