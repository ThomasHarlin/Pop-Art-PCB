#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, 0);

void setup() {
  // put your setup code here, to run once:

strip.begin();
strip.clear();
strip.setBrightness(50);
strip.show();

}

void loop() {
  // put your main code here, to run repeatedly:

for(int i = 0; i<24; i++){
strip.setPixelColor(i,255,255,255);
strip.show();
}
}
