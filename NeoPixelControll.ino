#include <Adafruit_NeoPixel.h>
#include "strip_controller.h"
#include "segment_patterns.h"

#define PIN 8
#define LED_COUNT 48

Adafruit_NeoPixel led_strip = Adafruit_NeoPixel (LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

StripController strip_controller = StripController(led_strip);

// Array of pattern setting functions
typedef void (*fp)(StripController &strip_controller);
const int numPatterns = 7;
fp patterns[numPatterns];
const int switchDelay = 10000;

void setup() {
  // Set up the pattern setting functions array
  patterns[0] = patternSet1;
  patterns[1] = patternSet5;
  patterns[2] = patternSet3;
  patterns[3] = patternSet4;
  patterns[4] = patternSet6;
  patterns[5] = patternSet7;
  patterns[6] = patternSet8;

  led_strip.begin();
  led_strip.clear();
  delay(3000);  
}

void loop() {
  static int currPattern = 0;
  static unsigned long lastMillis = 0;

  if(millis() - lastMillis > switchDelay || lastMillis == 0)
  {
    patterns[currPattern](strip_controller);
    currPattern = (currPattern + 1) % numPatterns;
    lastMillis = millis();
  }
  
  strip_controller.show();
}

void patternSet1(StripController &strip_controller) {
  strip_controller.deleteSegments();
  strip_controller.addSegment(new CirclerSegment(12, 2, 10, 0, 255, 0, 0, false), 0);
  strip_controller.addSegment(new CirclerSegment(12, 4, 20, 0, 0, 255, 6, false), 12);
  strip_controller.addSegment(new CirclerSegment(12, 6, 30, 255, 0, 0, 0, false), 24);
  strip_controller.addSegment(new CirclerSegment(12, 8, 40, 120, 0, 120, 6, false), 36);
}

void patternSet5(StripController &strip_controller) {
  strip_controller.deleteSegments();
  strip_controller.addSegment(new CirclerSegment(12, 2, 10, 0, 255, 0, 0, true), 0);
  strip_controller.addSegment(new CirclerSegment(12, 4, 20, 0, 0, 255, 6, true), 12);
  strip_controller.addSegment(new CirclerSegment(12, 6, 30, 255, 0, 0, 0, true), 24);
  strip_controller.addSegment(new CirclerSegment(12, 8, 40, 120, 0, 120, 6, true), 36);
}

//void patternSet2(StripController &strip_controller) {
//  strip_controller.deleteSegments();
//  strip_controller.addSegment(new CirclerSegment(24, 3, 30, 0, 255, 0, 0, false), 0);
//  strip_controller.addSegment(new CirclerSegment(24, 3, 30, 0, 0, 255, 6, true), 0);
//  strip_controller.addSegment(new CirclerSegment(24, 3, 30, 255, 0, 0, 0, false), 24);
//  strip_controller.addSegment(new CirclerSegment(24, 3, 30, 120, 0, 120, 6, true), 24);  
//}

void patternSet3(StripController &strip_controller) {
  strip_controller.deleteSegments();
  
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 0, 255, 0, 0, false), 0);
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 255, 0, 0, 6, false), 0);

  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 0, 255, 0, 0, true), 12);
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 255, 0, 0, 6, true), 12);
  
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 125, 0, 125, 0, false), 24);
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 0, 125, 125, 6, false), 24);
  
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 125, 0, 125, 0, true), 36);
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 0, 125, 125, 6, true), 36);
}

void patternSet4(StripController &strip_controller) {
  strip_controller.deleteSegments();
  
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 0, 255, 0, 0, true), 0);
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 255, 0, 0, 6, true), 0);

  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 0, 255, 0, 0, false), 12);
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 255, 0, 0, 6, false), 12);
  
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 125, 0, 125, 0, true), 24);
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 0, 125, 125, 6, true), 24);
  
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 125, 0, 125, 0, false), 36);
  strip_controller.addSegment(new CirclerSegment(12, 3, 50, 0, 125, 125, 6, false), 36);
}

void patternSet6(StripController &strip_controller) {
  strip_controller.deleteSegments();
  strip_controller.addSegment(new RingSegment(48, 10, 10, 10), 0);
  strip_controller.addSegment(new CirclerSegment(12, 2, 20, 0, 255, 0, 0, true), 0);
  strip_controller.addSegment(new CirclerSegment(12, 2, 30, 0, 0, 255, 6, true), 12);
  strip_controller.addSegment(new CirclerSegment(12, 2, 40, 255, 0, 0, 0, true), 24);
  strip_controller.addSegment(new CirclerSegment(12, 2, 50, 120, 0, 120, 6, true), 36);
}

void patternSet7(StripController &strip_controller) {
  strip_controller.deleteSegments();
  strip_controller.addSegment(new RingSegment(48, 0, 10, 50), 0);
  strip_controller.addSegment(new CirclerSegment(12, 2, 20, 0, 255, 0, 0, false), 0);
  strip_controller.addSegment(new CirclerSegment(12, 2, 30, 0, 0, 255, 6, false), 12);
  strip_controller.addSegment(new CirclerSegment(12, 2, 40, 255, 0, 0, 0, false), 24);
  strip_controller.addSegment(new CirclerSegment(12, 2, 50, 120, 0, 120, 6, false), 36);
}

void patternSet8(StripController &strip_controller) {
  strip_controller.deleteSegments();
  strip_controller.addSegment(new CirclerSegment(12, 2, 40, 0, 255, 0, 0, false), 0);
  strip_controller.addSegment(new CirclerSegment(12, 2, 60, 0, 0, 255, 0, true), 0);
  strip_controller.addSegment(new CirclerSegment(12, 2, 60, 255, 0, 0, 6, false), 12);
  strip_controller.addSegment(new CirclerSegment(12, 2, 40, 120, 0, 120, 6, true), 12);
  strip_controller.addSegment(new CirclerSegment(12, 2, 40, 255, 0, 0, 0, false), 24);
  strip_controller.addSegment(new CirclerSegment(12, 2, 60, 0, 0, 255, 0, true), 24);
  strip_controller.addSegment(new CirclerSegment(12, 2, 60, 255, 0, 0, 6, false), 36);
  strip_controller.addSegment(new CirclerSegment(12, 2, 40, 120, 0, 120, 6, true), 36);
}
