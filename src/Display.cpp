#include "Display.h"


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void Display::init(){
    pinMode(1, OUTPUT);
    digitalWrite(1, LOW);
    delay(10);
    digitalWrite(1, HIGH);

    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

}


void Display::sendPoint(int Ix, int Iy){
    display.drawCircle(Ix*display.width()/1023, Iy*display.height()/1023, 8, SSD1306_WHITE);
}


void Display::format(){
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.cp437(true);         // Use full 256 char 'Code Page 437' font


}

void Display::dispDistAn(int dist){

    String str = String(dist);

    display.setCursor(5, 5);     // Start at top-left corner
    display.write("AN Dist:");

    for(int i =0; i < str.length(); i++ ) {
    display.write(str[i]);
    }
     display.write("mm");

}

void Display::dispDistPw(int dist){

    String str = String(dist);

    display.setCursor(5, 25);     // Start at top-left corner
    display.write("PW Dist:");

    for(int i =0; i < str.length(); i++ ) {
    display.write(str[i]);
    }
     display.write("mm");

}

void Display::dispDistRX(String dist){
    display.setCursor(5, 50);     // Start at top-left corner
    display.write("RX Dist:");
    char charDist[3];
    dist.toCharArray(charDist, 4);
    display.write(charDist);
    display.write("mm");
}



void Display::update(){
    display.display();
}

void Display::clear(){
    display.clearDisplay();
}