#include <Adafruit_NeoPixel.h>
#include "segment_controller.h"

class StripController
{
  private:
    Adafruit_NeoPixel &led_strip;
    SegmentControllerArray segments;
    int segPosition[MAX_SEGMENTS];
    
  public:
    StripController(Adafruit_NeoPixel &led_strip) :
    led_strip(led_strip)
    {
    }

    ~StripController() {
    }
    
    void addSegment(SegmentController *obj, int n_position) {
      segments.add(obj);
      segPosition[segments.getCount() - 1] = n_position;
    }

  void show() {
    // Clear LEDs
    led_strip.clear();

    unsigned long currMillis = millis();
    
    // Get the LED information from each segment controller and set the pixel color on the correspoing strip's LED
    for(int i = 0; i < segments.getCount(); i++) {
      SegmentController *currSegment = segments.getItem(i);
      int startPos = segPosition[i];
      UpdateItems updates = currSegment->update(currMillis);
      
      // Update the led_strip's pixels
      for(int j = 0; j < updates.getSize(); j++) {
        UpdateItem *currUpdate = updates.getItem(j);
        led_strip.setPixelColor(startPos + currUpdate->position, currUpdate->r, currUpdate->g, currUpdate->b);
      }
    }
    
    led_strip.show();
  }

  void deleteSegments() {
    // Empty the SegmentControllerArray
    segments.clear();
  }
};

