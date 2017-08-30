#include <Arduino.h>

// Tablet library taken from here http://pccar.ru/showpost.php?p=366382&postcount=669

#include "Tablet.h"

// Constant values for 1K resistor

#define NOBUTTON 484
#define PLAY 678
#define NEXT 845
#define PREV 767
#define VOLUP 913
#define VOLDOWN 972

uint8_t analogPin=3;

class WheelKeyEvent {
protected:
  uint16_t tolerance;
  uint16_t resistance;
  uint32_t timestamp;

public:
  void set(const uint16_t r, const uint16_t t) {
    resistance = r;
    timestamp = t;
  }

  void set(const uint16_t r, const uint16_t t, const uint16_t tol) {
    resistance = r;
    timestamp = t;
    tolerance = tol;
  }

  void setTolerance(const uint16_t t) {
    tolerance = t;
  }

  uint16_t getResistance() const {
    return resistance;
  }

  uint16_t getTimestamp() const {
    return timestamp;
  }

  uint16_t getTolerance() const {
    return tolerance;
  }

  boolean resistanceEqualsTolerance(const uint16_t expected) const
  {
    return ((resistance >= expected - tolerance) && (resistance <= expected + tolerance));
  }

  void operator = (const WheelKeyEvent v)  {
    resistance = v.getResistance();
    timestamp = v.getTimestamp();
    tolerance = v.getTolerance();
  }

};

WheelKeyEvent data;
WheelKeyEvent dataPrev;

uint16_t flag = 0;
uint16_t eventTime = 0;
uint16_t pauseMillis = 0;

boolean between(const uint16_t value, const uint16_t a, const uint16_t b)
{
  return ( (value >= a) && (value <= b) );
}

void setup()
{
    data.set(NOBUTTON, 0, 10);
    dataPrev.set(NOBUTTON, 0, 10);
}

void loop()
{
  data.set(analogRead(analogPin), millis());

  if (data.resistanceEqualsTolerance(NOBUTTON)) {
    if (dataPrev.resistanceEqualsTolerance(NEXT) && (data.getTimestamp() - dataPrev.getTimestamp() <= 500) ) {
      Tablet.next();
      delay(500);
      Tablet.clear();
    } else if (dataPrev.resistanceEqualsTolerance(PREV) && (data.getTimestamp() - dataPrev.getTimestamp() <= 500) ) {
      Tablet.previous();
      delay(500);
      Tablet.clear();
    } else {
      Tablet.clear();
    }
  } else if (data.resistanceEqualsTolerance(VOLUP)) {
    Tablet.vol_up();
    delay(250);
    Tablet.clear();
  } else if (data.resistanceEqualsTolerance(VOLDOWN)) {
    Tablet.vol_down();
    delay(250);
    Tablet.clear();
  } else if (data.resistanceEqualsTolerance(NEXT) && dataPrev.resistanceEqualsTolerance(NEXT) && (data.getTimestamp() - dataPrev.getTimestamp() > 500) ) {
    Tablet.forward();
    delay(250);
    Tablet.clear();
  } else if (data.resistanceEqualsTolerance(PREV) && dataPrev.resistanceEqualsTolerance(PREV) && (data.getTimestamp() - dataPrev.getTimestamp() > 500) ) {
    Tablet.rewind();
    delay(250);
    Tablet.clear();
  } else if (data.resistanceEqualsTolerance(PLAY)) {
    Tablet.play_pause();
    delay(500);
    Tablet.clear();
  }

  if (!data.resistanceEqualsTolerance(dataPrev.getResistance())) {
    dataPrev = data;
  }

}
