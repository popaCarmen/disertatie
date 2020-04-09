#include <SoftwareSerial.h>  //header file of software serial port

//Lidar sensor
#define TF_mini_RX   8
#define TF_mini_TX   9

//Robot motors
//Motor A
#define enA          3
#define in1          2
#define in2          4
//Motor B
#define enB          6
#define in3          5
#define in4          7


SoftwareSerial Serial1(TF_mini_RX, TF_mini_TX); //define software serial port name

int lidar_dist; //actual lidar_distance measurements of LiDAR
int strength; //signal strength of LiDAR
int check;  //save check value
int i;
int uart[9];  //save data measured by LiDAR
const int HEADER = 0x59; //frame header of data package

int pwm_speed = 100;
int Lidar_distance;
int distanceRight, distanceLeft;
void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
  Serial1.begin(115200);  //set bit rate of serial port connecting LiDAR with Arduino

  analogWrite(enA, 80);
  analogWrite(enB, 80);
}

void loop()
{

  Stop();
  delay(200);
  backward();
  delay(400);
      Stop();
      delay(200);
      distanceRight = LookRight();
      delay(300);
      distanceLeft = LookLeft();
      delay(300);
  
  
}
