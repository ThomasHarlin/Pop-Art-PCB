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


int whichFrame = 0;

int colors [6][3] {
  {255, 0, 0},
  {255, 150, 0},
  {255, 255, 0},
  {0, 255, 0},
  {0, 0, 255},
  {60, 0, 255},
};

void setup() {
  strip.begin();
  strip.clear();
  strip.setBrightness(255);

  butt.attach(1);
  butt.interval(5);

  sT = millis();

}

void loop() {
  butt.update();

  if (butt.rose()) {
    stuff = (stuff + 1) % 4;
    strip.clear();
    strip.show();
    sT = millis();
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void offFunc() {
  strip.clear();
  strip.show();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void staticFunc() {
  //makes the board look like it has a purple lable and black vinyl
  for (int i = 0; i < strip.numPixels(); i++) {
    //pink record lable
    if (i == 3 || i == 6 || i == 7 || i == 11 || i == 12 || i == 16 || i == 17 || i == 20) {
      strip.setPixelColor(i, 255, 0, 255);
    }
    else{
      strip.setPixelColor (i, 50,50,50);
    }
  }
  strip.show();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void simpleFunc() {
  //rainbow fade on the lable, rest is white
  timer = 15;

  for (int i = 0; i < strip.numPixels(); i++) {

    //fade lable
    if (i == 3 || i == 6 || i == 7 || i == 11 || i == 12 || i == 16 || i == 17 || i == 20) {
      strip.setPixelColor(i, Wheel(fade));
    }
    else {
      //white outside
      strip.setPixelColor(i, 50, 50, 50);
    }
  }
  if ((millis() - sT) > timer) {
    fade = (fade + 1) % 255;
    strip.show();
    sT = millis();
  }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fancyFunc() {
  //make a rotating record animation, maybe have the lable in the middle color fade
  timer = 100;

  for (int i = 0; i < strip.numPixels(); i++) {

    int pixAddress = pixelMap[i];
    int whichColor = animation[whichFrame][i];

    int red = colors[whichColor][0];
    int green = colors[whichColor][1];
    int blue = colors[whichColor][2];

    if (pixAddress != -1) {
      strip.setPixelColor(pixAddress, red, green, blue);
    }
  }

  if (millis() - sT > timer) {
    sT = millis();
    whichFrame = (whichFrame + 1) % 6;
    strip.show();
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
