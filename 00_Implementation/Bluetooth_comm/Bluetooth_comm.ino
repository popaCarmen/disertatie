//#include <SoftwareSerial.h>  //header file of software serial port
//
//#define Tx 8
//#define Rx 9
//SoftwareSerial Serial1(Tx, Rx); //define software serial port name as Serial1 and define pin2 as RX and pin3 as TX


//int a1 = 0;
//int a2 = 0;
int val = 0;
char received_data;
bool array_reached = false;
int distance_values[150];
int indexx = 0;

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);

  Serial.println("Start");

  for(int i=0;i<140;i++)
  {
    distance_values[i] = random(100);
    Serial.print("Distance[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(distance_values[i]);
  }
}

void loop()
{
   if (Serial2.available())
      {
        received_data = Serial2.read();
        if (received_data == 'S')
        {
         // if (array_reached == false)
          {
            
            if (indexx > 140)
            {
              array_reached = true;
             // send_value_flag = false; //s-a trimis primul set de date
               Serial.println("Send data to Matlab");
               Serial2.print("F .");
            }
            else
            {
              Serial2.print('D');
            Serial2.print(distance_values[indexx]);
            Serial2.print('.');
            indexx++;
            Serial.println(indexx);
            }
          }
//          else
//          {
//           
//          }
        }
      }
}
