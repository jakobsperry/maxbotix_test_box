#include "Display.h"


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void Display::init(){
    pinMode(23, OUTPUT);
    digitalWrite(23, LOW);
    delay(10);
    digitalWrite(23, HIGH);

    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

}


void Display::sendPoint(int Ix, int Iy){
    display.drawCircle(Ix*display.width()/1023, Iy*display.height()/1023, 8, SSD1306_WHITE);
}

void Display::update(){
    display.display();
}

void Display::clear(){
    display.clearDisplay();
}