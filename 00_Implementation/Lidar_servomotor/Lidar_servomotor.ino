/* 
  This program is the interpretation routine of standard output protocol of TFmini product on Arduino.
  For details, refer to Product Specifications.
  For Arduino boards with only one serial port like UNO board, the function of software visual serial port is to be used. 
*/ 

#include <SoftwareSerial.h>  //header file of software serial port
#include <Servo.h>  //header file for servomotor

#define X_Serv_Pin 10 

SoftwareSerial Serial1(6,7); //define software serial port name as Serial1 and define pin2 as RX and pin3 as TX

Servo horizontal_Servo; //define servo for horizontal movement
/* For Arduinoboards with multiple serial ports like DUEboard, interpret above two pieces of code and directly use Serial1 serial port*/

int dist; //actual distance measurements of LiDAR
int strength; //signal strength of LiDAR
int check;  //save check value
int i;
int uart[9];  //save data measured by LiDAR
const int HEADER=0x59;  //frame header of data package

int minPosServo = 0;
int maxPosServo = 180;
int lastPosServo = 0; // variable used for determining if the servo position is different from the previous one
int posServo = (maxPosServo + minPosServo) / 2; // this is the middle position of the servomotor, so that the lidar sensor to be in the middle

int distance_values[180]; 
int angle_value[180];
bool scanning = true; 

int index;

void setup() {
  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
  Serial1.begin(115200);  //set bit rate of serial port connecting LiDAR with Arduino
  
  Serial.println("Start"); 

  horizontal_Servo.attach(X_Serv_Pin); 

  horizontal_Servo.write(posServo); //initial position
}

void loop() { 

  //;
    for (index=0; index<=180; index++)
    {
      if(scanning!= false)
      {
        Lidar_reading();
        delay(500);
        horizontal_Servo.write(index); //initial position
        delay(50); 
       // Lidar_reading(); 
        angle_value[index] = index; 
        distance_values[index] = dist;
        Serial.print("angle: ");
        Serial.println(angle_value[index]); 
        Serial.print("distance: ");
        Serial.println(distance_values[index]); 
        
        if(index == 180)
            scanning = false; 
      }
    }
}



void Lidar_reading(void)
{
    if (Serial1.available()) {  //check if serial port has data input
    if(Serial1.read() == HEADER) {  //assess data package frame header 0x59
      uart[0]=HEADER;
      if (Serial1.read() == HEADER) { //assess data package frame header 0x59
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) { //save data in array
          uart[i] = Serial1.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff)){ //verify the received data as per protocol
          dist = uart[2] + uart[3] * 256;     //calculate distance value
          strength = uart[4] + uart[5] * 256; //calculate signal strength value
           Serial.print("dist = ");
           Serial.print(dist); //output measure distance value of LiDAR
//           Serial.print('\t');
//           Serial.print("strength = ");
//           Serial.print(strength); //output signal strength value
//           Serial.print('\n');
        }
      }
    }
  }
}
