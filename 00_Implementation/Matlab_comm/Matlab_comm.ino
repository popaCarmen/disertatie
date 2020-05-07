#include <SoftwareSerial.h> //header file of software serial port

#define Tx_Lidar      7
#define Rx_Lidar      6

#define Rx_Bluethooth     8
#define Tx_Bluethooth     9

SoftwareSerial Serial_Lidar(Rx_Lidar, Tx_Lidar); //define software serial port name as Serial_Lidar and define pin 6 as RX and pin 7 as TX
SoftwareSerial Serial_Bluetooth(Rx_Bluethooth, Tx_Bluethooth); //define software serial port name as Serial_Bluetooth and define pin 8 as RX and pin 9 as TX

int dist;     //actual distance measurements of LiDAR
int strength; //signal strength of LiDAR
int check;    //save check value
int i;
int uart[9];             //save data measured by LiDAR
const int HEADER = 0x59; //frame header of data package

char received_data;

void setup()
{
  Serial.begin(9600);    //set bit rate of serial port connecting Arduino with computer
  Serial_Lidar.begin(115200); //set bit rate of serial port connecting LiDAR with Arduino
  Serial_Bluetooth.begin(9600); //set bit rate of serial port connecting Bluethooth with Arduino

  Serial.println("Start");
}

void loop()
{
  Lidar_reading();
  if(Serial_Bluetooth.available())
  {
    received_data = Serial_Bluetooth.read();
    if (received_data == 'S')
    {
      Serial_Bluetooth.print(dist);
      Serial.println("Message has been sent to Matlab");
    }
    
    //ToDo: Test if Arduino can send messages as string to Matlab. 
  }
}

void Lidar_reading(void)
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
}
