//#include <SoftwareSerial.h> //header file of software serial port
//#include <AltSoftSerial.h> // header file of software serial port for pin 8 and 9 - bluetooth device\

//#define Tx_Lidar      7
//#define Rx_Lidar      6
//
//#define Rx_Bluethooth     8
//#define Tx_Bluethooth     9

//SoftwareSerial Serial_Lidar(Rx_Lidar, Tx_Lidar); //define software serial port name as Serial_Lidar and define pin 6 as RX and pin 7 as TX
//SoftwareSerial Serial_Bluetooth(Rx_Bluethooth, Tx_Bluethooth); //define software serial port name as Serial_Bluetooth and define pin 8 as RX and pin 9 as TX
//AltSoftSerial Serial_Bluetooth;

int dist;     //actual distance measurements of LiDAR
int strength; //signal strength of LiDAR
int check;    //save check value
int i;
int uart[9];             //save data measured by LiDAR
const int HEADER = 0x59; //frame header of data package

char received_data;

int value = 100;
int value_array[180];
int index = 0;
bool finished = true;

void setup()
{
  Serial.begin(9600);    //set bit rate of serial port connecting Arduino with computer
  Serial3.begin(115200); //set bit rate of serial port connecting LiDAR with Arduino
  Serial2.begin(9600); //set bit rate of serial port connecting Bluethooth with Arduino

  Serial.println("Start");

  value_array[0] = -255;
  for (int i = 1; i < 180; i++)
  {
    value_array[i] = i;
  }
}

void loop()
{
  if (Serial2.available())
  {
    received_data = Serial2.read();
    if (received_data == 'S')
    {
      if (finished == true)
      {
        Serial2.print(value_array[index]);
        index++;
        if(index >= 180)
        {
          finished = false;
        }
      }
      else
      {
        Serial2.print("F");
      }
    }
  }
}
