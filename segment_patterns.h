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

    UpdateItems update(unsigned long currMillis)
    {
      UpdateItems ret(patternLength);
      // set the pixels from startPos to startPos + patternLength to r, g, b
      for(int j = 0; j < ret.getSize(); j++) {
        ret.getItem(j)->setValues((startPos + j * posIncrement + getSegmentLength()) % getSegmentLength(), r, g, b);
      }
  
      if((currMillis - lastMillis) > stepTime)
      {
        // increment startPos every stepTime milliseconds
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

    UpdateItems update(unsigned long t) {
      UpdateItems ret(getSegmentLength());
      // Set every pixel in the segement to the color r, g, b
      for(int i = 0; i < ret.getSize(); i++) {
        ret.getItem(i)->setValues(i, r, g, b);  
      }
      return ret;
    }
};

class PulserSegment : public SegmentController
{
  private:
    uint8_t r, g, b;
    long period;
    int patternLength;
    int startPos;
    float phase; // from 0 phase angle for 0.0 to 2*PI phase angle for 1.0 
    unsigned long lastMillis;

  public:
    PulserSegment(int segmentLength, uint8_t r, uint8_t g, uint8_t b, long period, int patternLength, int startPosition, float phase = 0.0) :
     SegmentController(segmentLength),
     r(r),
     g(g),
     b(b),
     period(period),
     lastMillis(0),
     patternLength(patternLength),
     startPos(startPosition),
     phase(phase)
     {
      
     }

    UpdateItems update(unsigned long currMillis) {
      const float Pi = 3.141593;

      // Compute the brightness level
      float level = (sin(2.0*Pi*currMillis/period + 2.0*Pi*phase) + 1) * 0.5;      
      UpdateItems ret(patternLength);
      // Set every pixel in the segement to the color r, g, b
      for(int i = 0; i < patternLength; i++) {
        ret.getItem(i)->setValues((i + startPos) % getSegmentLength(), level*r, level*g, level*b);  
      }
      return ret;
    }
};

class SpinnerSegment : public SegmentController
{
  private:
    int patternLength;
    uint8_t r, g, b;
    int max_speed;  // in pixels/sec
    int period;
    int startPos;
    bool clockWise;
    int posIncrement;
    unsigned long lastMillis;
    long vmin;

  public:
    SpinnerSegment(int segmentLength, int patternLength, int max_speed, int period, uint8_t r, uint8_t g, uint8_t b,  int startPosition = 0, bool clockWise = true) :
    SegmentController(segmentLength),
    patternLength(patternLength),
    max_speed(max_speed),
    period(period),
    r(r),
    g(g),
    b(b),
    startPos(startPosition),
    clockWise(clockWise), 
    lastMillis(0)
    {
      posIncrement = clockWise ? 1 : -1;
      vmin = getSegmentLength();       
    }

    UpdateItems update(unsigned long currMillis) {
      const float Pi = 3.141593;
      long stepTime;
      UpdateItems ret(patternLength);

      // The velocity of the spinner varies like sin(2*PI*t/period)
      // Compute the current velocity. The spinner only goes in one direction so we 
      // change the range of sine from -1/1 to 0/1
      float v = max(max_speed * ((sin(2.0*Pi*currMillis/period) + 1) * 0.5), vmin);
      // compute the new stepTime. stepTime = 1/v *1000 in units of ms/px
      stepTime = 1000.0/v;
      if(currMillis - lastMillis > stepTime) {
        startPos += posIncrement;
        if(startPos > getSegmentLength()) startPos = 1;
        if(startPos < 0) startPos = getSegmentLength() - 1;
        lastMillis = currMillis;
      }

      // set the pixels from startPos to startPos + patternLength to r, g, b
      for(int j = 0; j < ret.getSize(); j++) {
        ret.getItem(j)->setValues((startPos + j * posIncrement + getSegmentLength()) % getSegmentLength(), r, g, b);
      }
   
      return ret;
    }
};

#endif
