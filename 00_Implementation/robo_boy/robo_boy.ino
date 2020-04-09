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

  analogWrite(enA, 130);
  analogWrite(enB, 130);
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
//  Lidar_distance = Lidar_Reading();
//  Serial.print("Lidar_distance: ");
//  Serial.println(Lidar_distance);
//  if(Lidar_distance <= 30) 
//  {
//    Serial.println("dist < 30");
//      Stop();
//      delay(200);
//      backward();
//      delay(400);
//      Stop();
//      delay(200);
//      distanceRight = LookRight();
//      delay(300);
//      distanceLeft = LookLeft();
//      delay(300);
//
//      if(distanceRight >= distanceLeft)
//      {
//        rightward();
//        delay(1000);
//        Serial.println("Distance right > distance left");
//        Stop();
//      }
//      else
//      {
//        leftward();
//        delay(1000);
//        Serial.println("Distance left > distance right");
//        Stop();
//      }
//  }
//  else
//  {
//    forward();
//    Serial.println("Fata");
//  }
//  //  delay(2000);
//  //  forward();
//  //  delay(4000);
//  //  leftward();
//  //  delay(1000);
//  //  forward();
//  //  delay(4000);
//  //  backward();
//  //  delay(4000);
//  //  rightward();
//  //  delay(1000);
//  //  Stop();
//  //  if(pwm_speed<=255)
//  //    pwm_speed+=25;
//  //  else
//  //    pwm_speed=100;
}
int LookRight()
{
  Serial.println("look right");
    rightward();
    delay(1000);
    int distance = Lidar_Reading();
    Serial.println(distance);
   // delay(100);
    leftward();
    delay(1000);
    Stop();
    return distance;

}

int LookLeft()
{
  Serial.println("look left");
  leftward();
  delay(1000);
  int distance = Lidar_Reading();
      Serial.println(distance);

 // delay(100);
  rightward();
  delay(1000);
  Stop();
  return distance;
}
int Lidar_Reading()
{
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
  return lidar_dist;
}

void backward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void forward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void rightward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void leftward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
