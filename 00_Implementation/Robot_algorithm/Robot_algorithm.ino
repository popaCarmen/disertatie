#include <SoftwareSerial.h>  //header file of software serial port

//Lidar sensor
#define TF_mini_RX   6
#define TF_mini_TX   7

#define supply_5V    13

//Robot motors
//Motor A
#define enA          A1
#define in1          2
#define in2          3
//Motor B
#define enB          A0
#define in3          4
#define in4          5




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

  pinMode(supply_5V, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
  Serial1.begin(115200);  //set bit rate of serial port connecting LiDAR with Arduino

  analogWrite(enA, 130);
  analogWrite(enB, 130);

  digitalWrite(supply_5V, HIGH);
}

void loop() {

 if (Serial1.available()) {  //check if serial port has data input
    if (Serial1.read() == HEADER) { //assess data package frame header 0x59
      uart[0] = HEADER;
      if (Serial1.read() == HEADER) { //assess data package frame header 0x59
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) { //save data in array
          uart[i] = Serial1.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff)) { //verify the received data as per protocol
          lidar_dist = uart[2] + uart[3] * 256;     //calculate lidar_distance value
          strength = uart[4] + uart[5] * 256; //calculate signal strength value
          Serial.print("lidar_dist = ");
          Serial.print(lidar_dist); //output measure lidar_distance value of LiDAR
          Serial.print('\t');
          Serial.print("strength = ");
          Serial.print(strength); //output signal strength value
          Serial.print('\n');
        }
      }
    }
  }
}
