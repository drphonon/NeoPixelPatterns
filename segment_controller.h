#ifndef SEGMENT_CONTROLLER_H
#define SEGMENT_CONTROLLER_H

#define MAX_SEGMENTS 10

// This represents one LED in the segment's pattern. 
class UpdateItem {
  public:
    int position;
    uint8_t r, g, b;

    UpdateItem(int position = 0, uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) :
    position(position),
    r(r),
    g(g),
    b(b)
    {}

    void setValues(int n_position, uint8_t n_r, uint8_t n_g, uint8_t n_b) {
      position = n_position;
      r = n_r;
      g = n_g;
      b = n_b;
    }
};

// A dynamic array of UpdateItems
class UpdateItems {
  private:
    UpdateItem **items;
    int nItems;

  public:
    UpdateItems(int size) :
      nItems(size)
    {
      items = new UpdateItem*[nItems];
      for(int i = 0; i < nItems; i++)
      {
        items[i] = new UpdateItem();
      }
    }

    ~UpdateItems() {
      for(int i = 0; i < nItems; i++)
      {
        delete items[i];
      }
      delete items;
      items = NULL;
    }

    int getSize() {
      return nItems;
    }

    UpdateItem *getItem(int n) {
      return items[n];
    }
};

class SegmentController {
  
  private:
    int segmentLength; // The number of pixels controlled by this segment controller.
    
  public:

    SegmentController(int segmentLength) : segmentLength(segmentLength) {};
    ~SegmentController() {};

    int getSegmentLength() {return segmentLength;};
    
    virtual UpdateItems update() 
    {
      UpdateItems ret(segmentLength);
      for(int i = 0; i < ret.getSize(); i++) {
        ret.getItem(i)->setValues(i, 100, 0, 25);  
      }
      return ret;
    };    
};

class SegmentControllerArray
{
  private:
    SegmentController *segments[MAX_SEGMENTS];
    int nSegments;

  public:
    SegmentControllerArray() :
    nSegments(0)
    {
    }    

    ~SegmentControllerArray() 
    {
      clear();
    }
     
    void add(SegmentController *obj){
      segments[nSegments] = obj;
      nSegments++;
    }

    int getCount() {
      return nSegments;
    }

    SegmentController* getItem(int n) {
      return segments[n];
    }

    void clear() {
      for(int i = 0; i < nSegments; i++)
      {
        delete segments[i];
      }
      nSegments = 0;      
    }
};

#endif
