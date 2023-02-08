
#include "IRcamera.h"
#include "Display.h"

IRcamera irCamera;
Display disp;


void setup() {
  irCamera.init();
  disp.init();
}

void loop() {
  irCamera.update();
  disp.clear();
  for (int i = 0; i < 4; i++){
    if(irCamera.getX(i) != 1023 && irCamera.getY(i) != 1023){
      disp.sendPoint(irCamera.getX(i), irCamera.getY(i));
    }
  }
  disp.update();
  irCamera.print();

}
