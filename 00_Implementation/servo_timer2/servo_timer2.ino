#include <ServoTimer2.h>
#include <SoftwareSerial.h>  //header file of software serial port

#define X_Serv_Pin 11


ServoTimer2 horizontal_Servo; 
SoftwareSerial Serial1(6,7); //define software serial port name as Serial1 and define pin2 as RX and pin3 as TX


//int minAngleServo = 0;
//int maxAngleServo = 180;
//int lastAngleServo = 0; // variable used for determining if the servo position is different from the previous one
//int posServo = (maxPosServo + minPosServo) / 2; // this is the middle position of the servomotor, so that the lidar sensor to be in the middle

int angle;

void setup() {
  

  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
  //Serial1.begin(115200);  //set bit rate of serial port connecting LiDAR with Arduino
  Serial.println("Start"); 
  //Serial1.begin(115200);  //set bit rate of serial port connecting LiDAR with Arduino

 // horizontal_Servo.attach(X_Serv_Pin); 

 // horizontal_Servo.write(1500); //initial position

}

void loop() {

// horizontal_Servo.write(1500); //initial position
//int read_val = horizontal_Servo.read();
//Serial.println(read_val);
  
   for (angle = 0; angle <= 180; angle += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    int local_angle = 750 + angle*8.34;
    horizontal_Servo.attach(X_Serv_Pin); 
    horizontal_Servo.write(local_angle);              // tell servo to go to position in variable 'pos'
                         // waits 15ms for the servo to reach the position
    Serial.print("Angle:");
    Serial.println(angle);
    Serial.print("Local angle:");
    Serial.println(local_angle);
    delay(800);  
    horizontal_Servo.detach(); 
  }
  
  for (angle = 180; angle >= 0; angle -= 1) { // goes from 180 degrees to 0 degrees
     int local_angle = 750 + angle*8.34;
     horizontal_Servo.attach(X_Serv_Pin); 
    horizontal_Servo.write(local_angle);              // tell servo to go to position in variable 'pos'
    Serial.print("Angle:");
    Serial.println(angle);
    Serial.print("Local angle:");
    Serial.println(local_angle);
    delay(800);  
     horizontal_Servo.detach(); // waits 15ms for the servo to reach the position
  }
  delay(3000);

}
