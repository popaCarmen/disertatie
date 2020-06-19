/*
  This program is the interpretation routine of standard output protocol of TFmini product on Arduino.
  For details, refer to Product Specifications.
  For Arduino boards with only one serial port like UNO board, the function of software visual serial port is to be used.
*/
#include <Servo.h>
//#include <SoftwareSerial.h>  //header file of software serial port
//#include <Servo.h>  //header file for servomotor
//#include <ServoTimer2.h>

#define X_Serv_Pin 9
#define Y_Serv_Pin 8


//SoftwareSerial Serial1(6, 7); //define software serial port name as Serial1 and define pin2 as RX and pin3 as TX

Servo horizontal_Servo;
Servo vertical_Servo;

//Servo horizontal_Servo; //define servo for horizontal movement
/* For Arduinoboards with multiple serial ports like DUEboard, interpret above two pieces of code and directly use Serial1 serial port*/

int dist; //actual distance measurements of LiDAR
int strength; //signal strength of LiDAR
int check;  //save check value
int i;
int uart[9];  //save data measured by LiDAR
const int HEADER = 0x59; //frame header of data package

int minPosServo = 0;
int maxPosServo = 180;
int lastPosServo = 0; // variable used for determining if the servo position is different from the previous one
int posServo = (maxPosServo + minPosServo) / 2; // this is the middle position of the servomotor, so that the lidar sensor to be in the middle

int minPosServoY = 0;
int maxPosServoY = 180;
int lastPosServoY = 0; // variable used for determining if the servo position is different from the previous one
int posServoY = (maxPosServoY + minPosServoY) / 2; // this is the middle position of the servomotor, so that the lidar sensor to be in the middle


int distance_values[180];
int angle_value[180];
bool scanning = true;
bool scanDirection = false;
int scanIncrement = 1;

int middlePos = 750 + posServo * 8.34;

//int index;
int distance;
int serial_open_flag;
bool moved = false;
void setup() {
  horizontal_Servo.attach(X_Serv_Pin);
  vertical_Servo.attach(Y_Serv_Pin);
 // horizontal_Servo.write(middlePos); //initial position

  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
 // Serial3.begin(115200);  //set bit rate of serial port connecting LiDAR with Arduino
  Serial.println("Start");
}

void loop() {

  vertical_Servo.write(90);

// // if (moved == false)
// // {
//  //  Serial.println("Now servo");
//    if (scanning == true)
//    {
//      if (scanDirection == true)
//      {
//        posServo += scanIncrement;
//      }
//      else
//      {
//        posServo -= scanIncrement;
//      }
//      if (posServo > maxPosServo || posServo < minPosServo)
//      {
//        scanDirection = !scanDirection;
//        scanning = false; //???????
//      }
//   // }
//    else {
//      scanning = true;
//      posServo = minPosServo;
//      scanDirection = true;
//    }
//    posServo = min(max(posServo, minPosServo), maxPosServo);
//    moved = moveServo();
//  }
// // else
//  //{
//
//    Serial.println("Now lidar");
//    int distance = 0;
//  int strength = 0;
//
//    //  horizontal_Servo.detach();
//   // if (serial_open_flag == 0)
//    {
//      //horizontal_Servo.detach();
//     // Serial1.begin(115200);
//     // serial_open_flag = 1;
//      Serial.print("Start serial1");
//    }
//       distance = Lidar_reading(&distance, &strength);
//        Serial.print(distance);
//      Serial.print("cm\t");
//      Serial.print("strength: ");
//      Serial.println(strength);
//
// // }
//
//
//
//
//
//  //  Serial.print("angle: ");
//  //  Serial.println(posServo);
//  //  Serial.print("distance: ");
//  //  Serial.println(distance);
//  // for (index=0; index<=180; index++)
//  // {
//  //   if(scanning!= false)
//  //   {
//  //     //Lidar_reading();
//  //    // delay(500);
//  //     horizontal_Servo.write(index); //initial position
//  //     delay(50);
//  //     Lidar_reading();
//  //     angle_value[index] = index;
//  //     distance_values[index] = dist;
//  //     Serial.print("angle: ");
//  //     Serial.println(angle_value[index]);
//  //     Serial.print("distance: ");
//  //     Serial.println(distance_values[index]);
//
//  //     if(index == 180)
//  //         scanning = false;
//  //   }
//  // }
//}
//
//bool moveServo()
//{
//  //  horizontal_Servo.attach(X_Serv_Pin);
//  bool movement;
//  static int lastPosServo;
//  // int delta = 0;
//  if (posServo != lastPosServo)
//  {
//    // delta+=abs(posServo-lastPosServo);
//    //int local_position = 750 + posServo * 8.34;
//    horizontal_Servo.write(posServo);
//    Serial.print("Angle: ");
//    Serial.println(posServo);
//    lastPosServo = posServo;
//    movement = true;
//
//  }
//  delay(800);
//  Serial.println("Stop servo");
//
//  return movement;
//}
//
//int Lidar_reading(int* distance, int* strength)
//{
//  static char i = 0;
//  char j = 0;
//  int checksum = 0;
//  static int rx[9];
//  if(Serial3.available())
//  { 
//    // Serial.println( "tfmini serial available" );
//    rx[i] = Serial3.read();
//    if(rx[0] != 0x59) {
//      i = 0;
//    } else if(i == 1 && rx[1] != 0x59) {
//      i = 0;
//    } else if(i == 8) {
//      for(j = 0; j < 8; j++) {
//        checksum += rx[j];
//      }
//      if(rx[8] == (checksum % 256)) {
//        *distance = rx[2] + rx[3] * 256;
//        *strength = rx[4] + rx[5] * 256;
//      }
//      i = 0;
//    } else
//    {
//      i++;
//    }
//  } 
}
