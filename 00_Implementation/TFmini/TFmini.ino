//#include <HardwareSerial.h> //<-- ESP32 specific code
//HardwareSerial SerialTFMini( 3 ); //<-- ESP32 specific code
// serial(1) = pin12=RX, pin13=TX
// serial(2) = pin16=RX green, pin17=TX white
#include <SoftwareSerial.h>

SoftwareSerial Serial3(3,2);



void getTFminiData(int* distance, int* strength) {
  static char i = 0;
  char j = 0;
  int checksum = 0;
  static int rx[9];
  if(Serial3.available())
  { 
   // Serial.println( "tfmini serial available" );
    rx[i] = Serial3.read();
    if(rx[0] != 0x59) {
      i = 0;
    } else if(i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if(i == 8) {
      for(j = 0; j < 8; j++) {
        checksum += rx[j];
      }
      if(rx[8] == (checksum % 256)) {
        *distance = rx[2] + rx[3] * 256;
        *strength = rx[4] + rx[5] * 256;
        // Serial.println( *distance );
         //Serial.println( *strength );
      }
      i = 0;
    } else
    {
      i++;
    }
  } 
}


void setup() {
  Serial.begin(9600);
 
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
