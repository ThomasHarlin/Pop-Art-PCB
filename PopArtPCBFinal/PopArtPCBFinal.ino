#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>
#include"frames.h"

Adafruit_NeoPixel strip (24, 0);

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

//button for the pcb
Bounce butt = Bounce();

//switch variable
int stuff = 0;
//wheel index
int fade = 0;

//timer variables
long sT;
int timer;

void setup() {
  // put your setup code here, to run once:

  strip.begin();
  strip.clear();
  strip.setBrightness(255);

  butt.attach(1);
  butt.interval(5);

  sT = millis();

}

void loop() {
  // put your main code here, to run repeatedly:

  butt.update();

  if (butt.rose()) {
    stuff = (stuff + 1) % 4;
  }



  //state machine for the lights
  switch (stuff) {
    case 0:
      offFunc();
      break;
    case 1:
      staticFunc();
      break;
    case 2:
      simpleFunc();
      break;
    case 3:
      fancyFunc();
      break;
  }
}



//////////////////////////////////////////////////////
void offFunc() {
  strip.clear();
  strip.show();
}
//////////////////////////////////////////////////////
void staticFunc() {
  for (int i = 0; i < strip.numPixels(); i++) {
    //white outside with colored center lable. Mybe follow the vinyl outside instead?
  }
}
//////////////////////////////////////////////////////
void simpleFunc() {
  timer = 5;

  if ((sT - millis()) > timer) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(fade));
    }
    fade = (fade + 1) % 255;
    strip.show();
  }
  sT = millis();
}
//////////////////////////////////////////////////////
void fancyFunc() {
  //make a rotating record animation, maybe have the lable in the middle color fade
}
//////////////////////////////////////////////////////
