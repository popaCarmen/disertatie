#include <SoftwareSerial.h>  //header file of software serial port

#define Tx 8
#define Rx 9
SoftwareSerial Serial1(8, 9); //define software serial port name as Serial1 and define pin2 as RX and pin3 as TX


//int a1 = 0;
//int a2 = 0;
int val = 0;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(19200);

  Serial.println("Start");
}

void loop()
{
  //  Tx = analogRead(8);
  //  Rx = analogRead(9);
  if (Serial1.available() > 0) {
    /* whatever is available from the serial is read here    */
    val = Serial1.read();
    Serial.println(val);

    if (val == 10)
    {
      Serial1.print(1000);
      val = 0; 
      Serial.println("Message has been sent");
    }
//    else if (val == 20)
//    {
//      Serial.println(val);
//    }
  }
}
