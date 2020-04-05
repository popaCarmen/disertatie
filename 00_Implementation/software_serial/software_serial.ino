//#include <AltSoftSerial.h>
#include <SoftwareSerial.h>


//AltSoftSerial altSerial; //9 - Tx; 8 - Rx
SoftwareSerial altSerial(8, 9);


void setup() {
  Serial.begin(9600);
  Serial.print("AltSoftSerial Test Begin");
  Serial.println(10);
  altSerial.begin(9600);
  altSerial.println("Hello World");

}

void loop() {
  char c;

  altSerial.write("100");
  if (Serial.available()) {
    c = Serial.read();
    Serial.println(c);
    Serial.println("Ar fi trebuit sa fie aici");
  }

  if (altSerial.available()) {
    c = altSerial.read();
    Serial.print(c);
    Serial.println("Dar de fapt e aici");
  }

//   if (altSerial.available())
//    Serial.write(altSerial.read());
//  if (Serial.available())
//    altSerial.write(Serial.read());
}
