#include <SoftwareSerial.h> //header file of software serial port

#define Tx_Lidar 7
#define Rx_Lidar 6

#define Rx_Bluethooth 8
#define Tx_Bluethooth 9

//Robot motors
//Motor A
#define enA 3
#define in1 2
#define in2 A1
//Motor B
#define enB 5
#define in3 4
#define in4 A0
SoftwareSerial Serial_Lidar(Rx_Lidar, Tx_Lidar);               //define software serial port name as Serial_Lidar and define pin 6 as RX and pin 7 as TX
SoftwareSerial Serial_Bluetooth(Rx_Bluethooth, Tx_Bluethooth); //define software serial port name as Serial_Bluetooth and define pin 8 as RX and pin 9 as TX

int dist;     //actual distance measurements of LiDAR
int strength; //signal strength of LiDAR
int check;    //save check value
int i;
int uart[9];             //save data measured by LiDAR
const int HEADER = 0x59; //frame header of data package

int pwm_speed = 100;
int distanceRight, distanceLeft;

char received_data;


void setup()
{
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

  Serial.begin(9600);           //set bit rate of serial port connecting Arduino with computer
  Serial_Lidar.begin(115200);   //set bit rate of serial port connecting LiDAR with Arduino
  Serial_Bluetooth.begin(9600); //set bit rate of serial port connecting Bluethooth with Arduino

  Serial.println("Start");

  //Set Pwm speed for the motors
  analogWrite(enA, pwm_speed);
  analogWrite(enB, pwm_speed);
}

void loop()
{
  Lidar_reading();
  if (Serial_Bluetooth.available() > 0)
  {
    received_data = Serial_Bluetooth.read();
    if (received_data == 'S')
    {
      Serial_Bluetooth.print(dist);
      Serial.println("Message has been sent to Matlab");
    }
  }
  

  if(dist <= 32)
  {
    Serial_Bluetooth.print("Distance < 32");
    Stop();
    delay(200);
    backward();
    delay(200);
    Stop();
    distanceRight = LookRight();
    distanceLeft = LookLeft();
    delay(300);

    if(distanceRight >= distanceLeft)
    {
      rightward();
      delay(1000);
      Serial_Bluetooth.print("Distance right > distance left");
      Stop();
    }
    else
    {
      leftward();
      delay(1000);
      Serial_Bluetooth.print("Distance left > distance right");
      Stop();
    }
  }
  else
  {
    forward();
    Serial_Bluetooth.print("Forward");
  }
  
}

int Lidar_reading(void)
{
  if (Serial_Lidar.available())
  { //check if serial port has data input
    if (Serial_Lidar.read() == HEADER)
    { //assess data package frame header 0x59
      uart[0] = HEADER;
      if (Serial_Lidar.read() == HEADER)
      { //assess data package frame header 0x59
        uart[1] = HEADER;
        for (i = 2; i < 9; i++)
        { //save data in array
          uart[i] = Serial_Lidar.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff))
        {                                     //verify the received data as per protocol
          dist = uart[2] + uart[3] * 256;     //calculate distance value
          strength = uart[4] + uart[5] * 256; //calculate signal strength value
          Serial.print("dist = ");
          Serial.print(dist); //output measure distance value of LiDAR
          Serial.print('\t');
          Serial.print("strength = ");
          Serial.print(strength); //output signal strength value
          Serial.print('\n');
        }
      }
    }
  }
  return dist;
}

int LookRight()
{
  Serial_Bluetooth.print("Look right");
  rightward();
  delay(1000);
  int distance = Lidar_reading();
  Serial_Bluetooth.print("Right distance: " + distance);
 // Serial_Bluetooth.print(distance);
  leftward();
  delay(1000);
  Stop();
  Serial_Bluetooth.print("Done looking right");
  return distance;
}

int LookLeft()
{
  Serial_Bluetooth.println("Look left");
  leftward();
  delay(1000);
  int distance = Lidar_reading();
  Serial_Bluetooth.print("Left distance: " + distance);
  rightward();
  delay(1000);
  Stop();
  Serial_Bluetooth.print("Done looking left");
  return distance;
}
void backward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void forward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void rightward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void leftward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void Stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
