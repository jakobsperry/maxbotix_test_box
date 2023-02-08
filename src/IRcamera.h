#include <Arduino.h>
#include <Wire.h>

class IRcamera{
    
    public:
        void init();
        void update();
        int getX(int i);
        int getY(int i);
        void print();

        int Ix[4];
        int Iy[4];
        int s;

    private:
        int IRsensorAddress = 0xB0;
        //int IRsensorAddress = 0x58;
        int slaveAddress;
        int ledPin = 13;
        boolean ledState = false;
        byte data_buf[16];
        int i;

        void Write_2bytes(byte d1, byte d2);

};