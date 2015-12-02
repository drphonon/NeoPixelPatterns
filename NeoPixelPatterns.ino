#include <Adafruit_NeoPixel.h>
#include "strip_controller.h"
#include "segment_patterns.h"

#define PIN 8
#define LED_COUNT 48

Adafruit_NeoPixel led_strip = Adafruit_NeoPixel (LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);

StripController strip_controller = StripController(led_strip);

// Array of pattern setting functions
typedef void (*fp)(StripController &strip_controller);
const int numPatterns = 8;
fp patterns[numPatterns];
const int switchDelay = 10000;

void setup() {
  // Set up the pattern setting functions array
//  patterns[0] = patternSet1;
//  patterns[1] = patternSet5;
//  patterns[2] = patternSet3;
//  patterns[3] = patternSet4;
//  patterns[4] = patternSet6;
//  patterns[5] = patternSet7;
//  patterns[6] = patternSet8;
//  patterns[7] = patternSet9;

  led_strip.begin();
  led_strip.show();
  delay(3000);

 // waves(strip_controller);
//  breath(strip_controller);
//  pulse(strip_controller);
  patternSet9(strip_controller);
}

void loop() {
  static int currPattern = 0;
  static unsigned long lastMillis = 0;

//  if(millis() - lastMillis > switchDelay || lastMillis == 0)
//  {
//    patterns[currPattern](strip_controller);
//    currPattern = (currPattern + 1) % numPatterns;
//    lastMillis = millis();
//  }
  
  strip_controller.show();
}

// One circler per ring, ccw rotation. 
void patternSet1(StripController &strip_controller) {
  strip_controller.deleteSegments();
  strip_controller.addSegment(new CirclerSegment(12, 2, 10, 0, 255, 0, 0, false), 0);
  strip_controller.addSegment(new CirclerSegment(12, 4, 20, 0, 0, 255, 6, false), 12);
  strip_controller.addSegment(new CirclerSegment(12, 6, 30, 255, 0, 0, 0, false), 24);
  strip_controller.addSegment(new CirclerSegment(12, 8, 40, 120, 0, 120, 6, false), 36);
}

// One circler per ring, cw rotation
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

// Two circlers per ring, rotating in the same direction at the same speed.
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

// Two circlers per ring, rotating in the same direction at the same speed.
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

// One circler per ring, cw rotation, rotating in the same direction at variable speeds over a single color ring segment.
void patternSet6(StripController &strip_controller) {
  strip_controller.deleteSegments();
  strip_controller.addSegment(new RingSegment(48, 10, 10, 10), 0);
  strip_controller.addSegment(new CirclerSegment(12, 2, 20, 0, 255, 0, 0, true), 0);
  strip_controller.addSegment(new CirclerSegment(12, 2, 30, 0, 0, 255, 6, true), 12);
  strip_controller.addSegment(new CirclerSegment(12, 2, 40, 255, 0, 0, 0, true), 24);
  strip_controller.addSegment(new CirclerSegment(12, 2, 50, 120, 0, 120, 6, true), 36);
}

// One circler per ring, ccw rotation, rotating in the same direction at variable speeds over a single color ring segment.
void patternSet7(StripController &strip_controller) {
  strip_controller.deleteSegments();
  strip_controller.addSegment(new RingSegment(48, 0, 10, 50), 0);
  strip_controller.addSegment(new CirclerSegment(12, 2, 20, 0, 255, 0, 0, false), 0);
  strip_controller.addSegment(new CirclerSegment(12, 2, 30, 0, 0, 255, 6, false), 12);
  strip_controller.addSegment(new CirclerSegment(12, 2, 40, 255, 0, 0, 0, false), 24);
  strip_controller.addSegment(new CirclerSegment(12, 2, 50, 120, 0, 120, 6, false), 36);
}

// Two circlers per ring, rotating on opposite directions.
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

void patternSet9(StripController &strip_controller) {
  strip_controller.deleteSegments();

  strip_controller.addSegment(new SpinnerSegment(12, 2, 100, 5000, 0, 100, 0), 0);  
  
  strip_controller.addSegment(new SpinnerSegment(12, 6, 50, 3000, 0, 100, 0, 0), 12);  
  strip_controller.addSegment(new SpinnerSegment(12, 6, 50, 3000, 100, 10, 70, 6), 12);  
  //strip_controller.addSegment(new CirclerSegment(12, 2, 40, 0, 255, 0, 0, false), 0);

  strip_controller.addSegment(new SpinnerSegment(12, 9, 50, 3000, 0, 0, 100, 0, false), 24);  
  strip_controller.addSegment(new SpinnerSegment(12, 3, 50, 3000, 70, 100, 10, 6, false), 24);  
}

void waves(StripController &strip_controller) {
  strip_controller.deleteSegments();
 
  strip_controller.addSegment(new PulserSegment(12, 0, 0, 255, 1000, 6, 3, .5), 0);  
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 1000, 6, 9, .75), 0);  
  
  strip_controller.addSegment(new PulserSegment(12, 0, 0, 255, 1000, 6, 9, 0.25), 12);  
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 1000, 6, 3, 0), 12);  
  
  //strip_controller.addSegment(new CirclerSegment(12, 2, 1000.0/12.0, 0, 0, 255, 0, false), 0);
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 2000, 4, 0, 0.667), 24);  
  strip_controller.addSegment(new PulserSegment(12, 255, 0, 0, 2000, 2, 4, 0.833), 24);  
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 2000, 4, 6, 0.667), 24);  
  strip_controller.addSegment(new PulserSegment(12, 255, 0, 0, 2000, 2, 10, 0.5), 24);  

  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 2000, 3, 0, 0.167), 36);  
  strip_controller.addSegment(new PulserSegment(12, 255, 0, 0, 2000, 3, 3, 0.333), 36);  
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 2000, 3, 6, 0.167), 36);  
  strip_controller.addSegment(new PulserSegment(12, 255, 0, 0, 2000, 3, 9, 0.0), 36);  

}

void breath(StripController &strip_controller) {
  strip_controller.deleteSegments();
 
  strip_controller.addSegment(new PulserSegment(12, 0, 0, 255, 3000, 6, 3, 0), 0);  
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 3000, 6, 9, .5), 0);  
  
  strip_controller.addSegment(new PulserSegment(12, 0, 0, 255, 2000, 6, 9, 0.0), 12);  
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 2000, 6, 3, 0.5), 12);  
  
  //strip_controller.addSegment(new CirclerSegment(12, 2, 1000.0/12.0, 0, 0, 255, 0, false), 0);
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 2000, 4, 0, 0.5), 24);  
  strip_controller.addSegment(new PulserSegment(12, 255, 0, 0, 2000, 2, 4, 0), 24);  
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 2000, 4, 6, 0.5), 24);  
  strip_controller.addSegment(new PulserSegment(12, 255, 0, 0, 2000, 2, 10, 0), 24);  

  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 2000, 4, 0, 0.5), 36);  
  strip_controller.addSegment(new PulserSegment(12, 255, 0, 0, 2000, 2, 4, 0), 36);  
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 2000, 4, 6, 0.5), 36);  
  strip_controller.addSegment(new PulserSegment(12, 255, 0, 0, 2000, 2, 10, 0.0), 36);  
}

void pulse(StripController &strip_controller) {
  strip_controller.deleteSegments();
 
  strip_controller.addSegment(new PulserSegment(12, 0, 0, 255, 3000, 6, 3, 0), 0);  
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 3000, 6, 9, 0), 0);  
  
  strip_controller.addSegment(new PulserSegment(12, 0, 0, 255, 2000, 6, 9, 0.0), 12);  
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 2000, 6, 3, 0.0), 12);  
  
  //strip_controller.addSegment(new CirclerSegment(12, 2, 1000.0/12.0, 0, 0, 255, 0, false), 0);
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 1000, 4, 0), 24);  
  strip_controller.addSegment(new PulserSegment(12, 255, 0, 0, 500, 2, 4), 24);  
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 1000, 4, 6), 24);  
  strip_controller.addSegment(new PulserSegment(12, 255, 0, 0, 500, 2, 10), 24);  

  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 1050, 4, 0), 36);  
  strip_controller.addSegment(new PulserSegment(12, 255, 0, 0, 1050, 2, 4), 36);  
  strip_controller.addSegment(new PulserSegment(12, 0, 255, 0, 1050, 4, 6), 36);  
  strip_controller.addSegment(new PulserSegment(12, 255, 0, 0, 1050, 2, 10), 36);  
}

