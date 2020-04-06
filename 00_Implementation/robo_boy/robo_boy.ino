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


SoftwareSerial Serial1(TF_mini_RX,TF_mini_TX); //define software serial port name 

int dist; //actual distance measurements of LiDAR
int strength; //signal strength of LiDAR
int check;  //save check value
int i;
int uart[9];  //save data measured by LiDAR
const int HEADER=0x59;  //frame header of data package

int pwm_speed = 100;
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
}

void loop() { 

  analogWrite(enA, pwm_speed);
  analogWrite(enB, pwm_speed);

//  if (Serial1.available()) {  //check if serial port has data input
//    if(Serial1.read() == HEADER) {  //assess data package frame header 0x59
//      uart[0]=HEADER;
//      if (Serial1.read() == HEADER) { //assess data package frame header 0x59
//        uart[1] = HEADER;
//        for (i = 2; i < 9; i++) { //save data in array
//          uart[i] = Serial1.read();
//        }
//        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
//        if (uart[8] == (check & 0xff)){ //verify the received data as per protocol
//          dist = uart[2] + uart[3] * 256;     //calculate distance value
//          strength = uart[4] + uart[5] * 256; //calculate signal strength value
//          Serial.print("dist = ");
//          Serial.print(dist); //output measure distance value of LiDAR
//          Serial.print('\t');
//          Serial.print("strength = ");
//          Serial.print(strength); //output signal strength value
//          Serial.print('\n');
//        }
//      }
//    }
//  }
  delay(2000);
  forward();
  delay(4000);
  leftward();
  delay(1000);
  forward();
  delay(4000);
  backward();
  delay(4000);
  rightward();
  delay(1000);
  Stop();
  if(pwm_speed<=255)
    pwm_speed+=25;
  else
    pwm_speed=100;
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
