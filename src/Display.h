#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display{

    public:

    void init();
    void sendPoint(int Ix, int Iy);
    void dispDistAn(int dist);
    void dispDistPw(int dist);
    void dispDistRX(String dist);

    void update();
    void clear();
    void format();

    private:

    #define SCREEN_WIDTH 128 // OLED display width, in pixels
    #define SCREEN_HEIGHT 64 // OLED display height, in pixels

    #define OLED_RESET     17 // Reset pin # (or -1 if sharing Arduino reset pin)
    #define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
   
};