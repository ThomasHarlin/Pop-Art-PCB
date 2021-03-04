#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>
#include"frames.h"


Adafruit_NeoPixel strip (24,0);

Bounce butt = Bounce();


int stuff = 0;



void setup() {
  // put your setup code here, to run once:

  strip.begin();
  strip.clear();

  butt.attach(1);
  butt.interval(5);

}

void loop() {
  // put your main code here, to run repeatedly:

  butt.update();

  if (butt.rose()) {
    stuff = (stuff+1)%4;
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
    //some stuff to add later
  }
}
//////////////////////////////////////////////////////
void simpleFunc() {
  for (int i = 0; i < strip.numPixels(); i++) {
    //some stuff to add later
  }
}
//////////////////////////////////////////////////////
void fancyFunc() {

}
//////////////////////////////////////////////////////
