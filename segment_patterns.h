#include "segment_controller.h"

#ifndef SEGMENT_PATTERNS_H
#define SEGMENT_PATTERNS_H

class CirclerSegment : public SegmentController
{
  private:
    unsigned long lastMillis;
    unsigned long stepTime;
    int patternLength;
    uint8_t r, g, b;
    int startPos;
    int posIncrement;

  public:
    CirclerSegment(int segmentLength, int patternLength, unsigned long stepTime, uint8_t r, uint8_t g, uint8_t b, int startPosition = 0, bool clockWise = true) :
    SegmentController(segmentLength),
    patternLength(patternLength),
    stepTime(stepTime),
    lastMillis(0),
    r(r),
    g(g),
    b(b),
    startPos(startPosition)
    {     
      posIncrement = clockWise ? 1 : -1;
    }

  UpdateItems update()
  {
    unsigned long currMillis = millis();

    UpdateItems ret(patternLength);
    for(int j = 0; j < ret.getSize(); j++) {
      ret.getItem(j)->setValues((startPos + j * posIncrement + getSegmentLength()) % getSegmentLength(), r, g, b);
    }

    if((currMillis - lastMillis) > stepTime)
    {
      startPos += posIncrement;
      if(startPos > getSegmentLength()) startPos = 1;
      if(startPos < 0) startPos = getSegmentLength() - 1;
      lastMillis = currMillis;
    }
    
    return ret;
  }
};

class RingSegment : public SegmentController
{
  private:
    uint8_t r, g, b;

  public:
    RingSegment(int segmentLength, uint8_t r, uint8_t g, uint8_t b) :
     SegmentController(segmentLength),
     r(r),
     g(g),
     b(b)
     {
      
     }

    UpdateItems update() {
      UpdateItems ret(getSegmentLength());
      for(int i = 0; i < ret.getSize(); i++) {
        ret.getItem(i)->setValues(i,r, g, b);  
      }
      return ret;
    }
};

#endif
