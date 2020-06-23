/*
  This program is the interpretation routine of standard output protocol of TFmini product on Arduino.
  For details, refer to Product Specifications.
  For Arduino boards with only one serial port like UNO board, the function of software visual serial port is to be used.
*/

#include <SoftwareSerial.h>  //header file of software serial port

//SoftwareSerial Serial1(17,16); //define software serial port name as Serial1 and define pin2 as RX and pin3 as TX

/* For Arduinoboards with multiple serial ports like DUEboard, interpret above two pieces of code and directly use Serial1 serial port*/

int dist; //actual distance measurements of LiDAR
int strength; //signal strength of LiDAR
int check;  //save check value
int i;
int rx[9];  //save data measured by LiDAR
const int HEADER = 0x59; //frame header of data package

void setup() {
  Serial.begin(115200); //set bit rate of serial port connecting Arduino with computer
  Serial3.begin(115200);  //set bit rate of serial port connecting LiDAR with Arduino
  Serial.println("Start");
}

void loop() {
  static char i =0; 
  
  if (Serial3.available()) {  //check if serial port has data input
    rx[i] = Serial3.read();
    if (rx[0] == 0x59) //header
    {
      if (i == 8)
      {
        check = rx[0] + rx[1] + rx[2] + rx[3] + rx[4] + rx[5] + rx[6] + rx[7];
      }
      else
      {
        i++;
      }
      if (rx[8] == (check % 256))
      {
        dist = rx[2] + rx[3] * 256;
        strength = rx[4] + rx[5] * 256;

      }
    }
  }
}

  /*
    Download the program into Arduino board and power on monitor for serial port. Then real-time distance values measured by LiDAR and corresponding signal strength can be viewed.
    In addition, data curve can be viewed in curve plotter for serial port, provided, however, that the above code regarding printing for serial port should be modified:
    //  Serial.print("dist = ");
    Serial.print(dist);//output measure distance value of LiDAR
    Serial.print(' ');
    //  Serial.print("strength = ");
    Serial.print(strength);//output signal strength value
    Serial.print('\n');
    Reinterpret and download the program into Arduino board and power on the curve plotter. Then two curves representing dist and strength can be viewed.
  */
