#include <Arduino.h>
#include "Tablet.h" // Tablet library taken from here http://pccar.ru/showpost.php?p=366382&postcount=669


// Constant values for 1K resistor

#define NOBUTTON 484
#define PLAY 678
#define NEXT 845
#define PREV 767
#define VOLUP 913
#define VOLDOWN 972
#define FFWD 5000
#define REW 10000

uint16_t allButtons[8] = { NOBUTTON, PLAY, NEXT, PREV, VOLUP, VOLDOWN, FFWD, REW };

uint8_t analogPin=3;

uint16_t currentTimestamp, newTimestamp;
uint16_t currentState, newState;
uint16_t tolerance;

boolean between(const uint16_t value, const uint16_t a, const uint16_t b)
{
  return ( (value >= a) && (value <= b) );
}

boolean resistanceEqualsTolerance(const uint16_t actual, const uint16_t expected)
{
  return ((actual >= expected - tolerance) && (actual <= expected + tolerance));
}

void setup()
{
  currentState = NOBUTTON;
  currentTimestamp = millis();
  tolerance = 10;
  Tablet.begin();
}

uint16_t normalizeResistance(uint16_t resistance) {
  for (int i=0;i<8;i++) {
    if (resistanceEqualsTolerance(resistance, allButtons[i])) {
      return allButtons[i];
    }
  }
  return NOBUTTON;
}

uint16_t noButton(uint16_t buttonState, uint32_t timestamp)
{
  currentTimestamp = timestamp;
  return buttonState;
}

uint16_t next(uint16_t buttonState, uint32_t timestamp)
{
  switch (buttonState) {
    case NOBUTTON:
      if (timestamp - currentTimestamp < 250) {
        currentTimestamp = timestamp;
        Tablet.next();
        Tablet.clear();
        return NOBUTTON;
      }
      break;
    case NEXT:
      if (timestamp - currentTimestamp >= 250) {
        currentTimestamp = timestamp;
        return FFWD;
      }
      return NEXT;
      break;
    default:
      currentTimestamp = timestamp;
      return buttonState;
      break;
  }
  return buttonState;
}

uint16_t prev(uint16_t buttonState, uint32_t timestamp)
{
  switch (buttonState) {
    case NOBUTTON:
      if (timestamp - currentTimestamp < 250) {
        currentTimestamp = timestamp;
        Tablet.previous();
        Tablet.clear();
        return NOBUTTON;
      }
      break;
    case PREV:
      if (timestamp - currentTimestamp >= 250) {
        currentTimestamp = timestamp;
        return REW;
      }
      return PREV;
      break;
    default:
      currentTimestamp = timestamp;
      return buttonState;
      break;
  }
  return buttonState;
}

uint16_t volup(uint16_t buttonState, uint32_t timestamp)
{
  switch (buttonState) {
    case VOLUP:
      if (timestamp - currentTimestamp >= 250) {
        Tablet.vol_up();
        Tablet.clear();
        currentTimestamp = timestamp;
      }
      return VOLUP;
      break;
    default:
      currentTimestamp = timestamp;
      return buttonState;
      break;
  }
  return buttonState;
}

uint16_t voldown(uint16_t buttonState, uint32_t timestamp)
{
  switch (buttonState) {
    case VOLDOWN:
      if (timestamp - currentTimestamp >= 250) {
        Tablet.vol_down();
        Tablet.clear();
        currentTimestamp = timestamp;
      }
      return VOLDOWN;
      break;
    default:
      currentTimestamp = timestamp;
      return buttonState;
      break;
  }
  return buttonState;
}

uint16_t play(uint16_t buttonState, uint32_t timestamp)
{
  switch (buttonState) {
    case NOBUTTON:
      currentTimestamp = timestamp;
      Tablet.play_pause();
      Tablet.clear();
      return buttonState;
      break;
    default:
      currentTimestamp = timestamp;
      return buttonState;
      break;
  }
  return buttonState;
}

uint16_t ffwd(uint16_t buttonState, uint32_t timestamp)
{
  switch (buttonState) {
    case NEXT:
      if (timestamp - currentTimestamp >= 250) {
        Tablet.forward();
        Tablet.clear();
        currentTimestamp = timestamp;
      }
      return FFWD;
      break;
    default:
      currentTimestamp = timestamp;
      return buttonState;
      break;
  }
  return buttonState;
}

uint16_t rew(uint16_t buttonState, uint32_t timestamp)
{
  switch (buttonState) {
    case PREV:
      if (timestamp - currentTimestamp >= 250) {
        Tablet.rewind();
        Tablet.clear();
        currentTimestamp = timestamp;
      }
      return REW;
      break;
    default:
      currentTimestamp = timestamp;
      return buttonState;
      break;
  }
  return buttonState;
}


void loop()
{
  newState = normalizeResistance(analogRead(analogPin));
  newTimestamp = millis();

  switch (currentState) {
    case NOBUTTON:
      currentState = noButton(newState, newTimestamp);
      break;
    case PLAY:
      currentState = play(newState, newTimestamp);
      break;
    case VOLUP:
      currentState = volup(newState, newTimestamp);
      break;
    case VOLDOWN:
      currentState = voldown(newState, newTimestamp);
      break;
    case NEXT:
      currentState = next(newState, newTimestamp);
      break;
    case PREV:
      currentState = prev(newState, newTimestamp);
      break;
    case FFWD:
      currentState = ffwd(newState, newTimestamp);
      break;
    case REW:
      currentState = rew(newState, newTimestamp);
      break;
    default:
      Tablet.clear();
      break;
  }
  delay(50);
}
