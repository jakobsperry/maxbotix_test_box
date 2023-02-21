
#include <Arduino.h>
#include "Display.h"
#include <SPI.h>

Display disp;

#define sensorPin 4
#define pulsePin 4
const int slaveAPin = 5;



unsigned long riseTime = micros();
unsigned long PulseWidth;


void ISR(){
  if(digitalRead(pulsePin)){
    riseTime = micros();
  }
  else{
    PulseWidth = micros() - riseTime;
  }
}


SPISettings settingsA(2000000, MSBFIRST, SPI_MODE0);

void setup() {
  Serial.begin(115200);
  // pinMode(sensorPin, INPUT);
  pinMode(pulsePin, INPUT);
  disp.init();
  attachInterrupt(pulsePin, ISR, CHANGE);
  pinMode (slaveAPin, OUTPUT);
  SPI.begin();
  Serial2.begin(9600); // configure serial port for MaxSonar, 16 = RX2, 17 = TX2
  Serial2.setRxInvert(true);


}



uint8_t MSB, LSB;

int read_sensor_analog(){
  SPI.beginTransaction(settingsA);

  digitalWrite (slaveAPin, LOW);

  // reading only, so data sent does not matter

  MSB = SPI.transfer(0x60);
  LSB = SPI.transfer(0);

  int chA = int(word(MSB , LSB));

  digitalWrite (slaveAPin, HIGH);

  SPI.endTransaction();

  // Serial.print(stat);
  Serial.println(chA*10);

  // float voltage = float(chA * (5.0/1023));
 return int(chA*10);


}


int read_sensor_pulseWidth(){
  return (PulseWidth/6);
}

String read_sensor_serial(){

  while (Serial2.available() > 0) {
    char c = Serial2.read();
    if (c == 'R') { // check for start character
      char rangeStr[4];
      for (int i = 0; i < 3; i++) {
        while (Serial2.available() == 0) {} // wait for next character
        rangeStr[i] = Serial2.read();
        // Serial.print(rangeStr[i]); // print received character to serial monitor
      }
      // int range = atoi(rangeStr); // convert range string to integer
       Serial.println(rangeStr); // print range to serial monitor
       
       String string = String(rangeStr);
       return String((float(string.toInt())*24.5));
    }
  }
}


unsigned long current_time;
unsigned long timer_end = millis();
unsigned long timerTime = 1000;
int distAn, distPw;
String distSerial;

void loop() {

  distAn = read_sensor_analog();
  distPw = read_sensor_pulseWidth();
  distSerial = read_sensor_serial();
  

 current_time = millis();

  if(current_time >= timer_end){

    disp.clear();
    disp.format();
    disp.dispDistAn(distAn);
    disp.dispDistPw(distPw);
    disp.dispDistRX(distSerial);
    disp.update();

    timer_end = millis() + timerTime;
  } 



}





