//#include <HardwareSerial.h> //<-- ESP32 specific code
//HardwareSerial SerialTFMini( 3 ); //<-- ESP32 specific code
// serial(1) = pin12=RX, pin13=TX
// serial(2) = pin16=RX green, pin17=TX white
//#include <SoftwareSerial.h>

//SoftwareSerial Serial3(3,2);
#define HEADER  0x59

void getTFminiData(int* distance, int* strength) {
  static char index = 0; //index is used for accessing Lidar bytes
  char j = 0;
  int CRC = 0;
  static int rx[9];
  if(Serial3.available())
  { 
    //Serial.println( "tfmini serial available" );
    receive[i] = Serial3.read();
             
    if(receive[0] != HEADER) {
      index = 0;
    } else if(index == 1 && receive[1] != HEADER) {
      index = 0;
    } else if(index == 8) {
      for(j = 0; j < 8; j++) {
        CRC += receive[j];
      }         
      if(receive[8] == (CRC % 256)) {
        
        *distance = receive[2] + receive[3] * 256;
        *strength = receive[4] + receive[5] * 256;
       
      }
      index = 0;
    } else
    {
      index++;
    }
  } 
}


void setup() {
  Serial.begin(115200);
 
Serial3.begin( 115200 );
Serial.print("Start");

}

void loop()
{
  int distance = 0;
  int strength = 0;

  getTFminiData(&distance, &strength);
  while(!distance) {
    getTFminiData(&distance, &strength);
    if(distance) {
      Serial.print(distance);
      Serial.print("cm\t");
      Serial.print("strength: ");
      Serial.println(strength);

    }
  }

//delay(100);
}
