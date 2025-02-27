//Matlab and Arduino communication
//Lidar reading
//Servo x and servo y connected
//save distance value and angle in arrays
#include <Servo.h>

#define X_Serv_Pin 9
#define Y_Serv_Pin 8


Servo horizontal_Servo;
Servo vertical_Servo;

int minPosServoX = 0;
int maxPosServoX = 180;
int lastPosServoX = 0; // variable used for determining if the servo position is different from the previous one
//int posServoX = (maxPosServoX + minPosServoX) /2; // this is the middle position of the servomotor, so that the lidar sensor to be in the middle
int posServoX = minPosServoX;

int minPosServoY = 10;
int maxPosServoY = 150;
int lastPosServoY = 0; // variable used for determining if the servo position is different from the previous one
int posServoY = maxPosServoY; // this is the middle position of the servomotor, so that the lidar sensor to be in the middle

int distance_values[150];// 180 - x servo; 140 - y servo
int angle_value[150]; // 180 - x servo; 140 - y servo

bool scanning = true;
bool scanDirection = true;
int scanIncrement = 1;
bool read_flag = false;

bool moved = false;
bool finished = false;

bool send_value_flag = false;

bool local = false;

int i = 1;
char received_data;
int indexx = 0;
bool array_reached = false;

bool printed = false;
int x_movement = 0;
void setup() {
  horizontal_Servo.attach(X_Serv_Pin);
  vertical_Servo.attach(Y_Serv_Pin);

  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
  Serial3.begin(115200);  //set bit rate of serial port connecting LiDAR with Arduino
  Serial2.begin(9600); // Bluetooth
  Serial.println("Start");

  horizontal_Servo.write(posServoX); //starts from minimum position
  vertical_Servo.write(posServoY); //starts from minimum position
  Serial.println("Servo are at the minimum position");
}

void loop() {
  int distance = 0;
  int strength = 0;

  if (finished == true)
  {
    Serial.println("Am terminat de tot");
  }
  else
  {
    if (send_value_flag == false) // check if scan mode is finished
    {
      if (read_flag == true) // check if sensor readed the value
      {
        if (scanning == true)
        {
          //Scan on Y axis
          if (scanDirection == true)
          {
            posServoY -= scanIncrement; //go up
          }
          else
          {
            posServoY += scanIncrement; //go down
          }
          if (posServoY > maxPosServoY || posServoY < minPosServoY)
          {
            //am terminat o tura pe y
            //Scan on X axis
            scanDirection = !scanDirection;
            posServoX += scanIncrement; // go left

            send_value_flag = true; //similar with finished

            if (posServoX < minPosServoX)
            {
               scanning = false;
              //Finished scanning one round pe x
              //local = true;
              finished = true;
            }
          }
        }
        else {
          Serial.println("Am terminat o scanare");
          scanning = true;
          posServoX = 90;
          posServoY = 90;
          scanDirection = true;
          //        if(local == true)
          //        {
          //            finished = true;
          //        }
        }
        posServoX = min(max(posServoX, minPosServoX), maxPosServoX);
        posServoY = min(max(posServoY, minPosServoY), maxPosServoY);

        moved = moveServo();
      }
      else
      {
        //Lidar_reading(&distance, &strength);
        distance = i;
        if (distance) {
          if (posServoY >= 10 )
          {
            distance_values[150 - posServoY] = distance;
            angle_value[150 - posServoY] = 180 - posServoY;
          }
          //        if (Serial2.available())
          //        {
          //          char received_data = Serial2.read();
          //          if (received_data == 'S')
          //          {
          //            Serial2.print(distance);
          //            Serial.println("value sent to Matlab");
          //          }
          //        }
          //        Serial.print(distance);
          //        Serial.print("cm\t");
          //        Serial.print("strength: ");
          //        Serial.println(strength);
          read_flag = true;

          i++;
        }
      }
    }
    else
    { //am terminat o tura
      // if(printed == false)
      {
        Serial.println("Send data to Matlab");
//        for (int k = 0; k < 150; k++)
//        {
//          Serial.print("Distanta[");
//          Serial.print(k);
//          Serial.print("]= ");
//          Serial.println(distance_values[k]);
//
//          Serial.print("unghi[");
//          Serial.print(k);
//          Serial.print("]= ");
//          Serial.println(angle_value[k]);
//        }
        // printed = true;
        send_value_flag = false; //s-a trimis primul set de date
      }
      //  else
      {
        //   send_value_flag=false;
      }
      //    if (Serial2.available())
      //    {
      //      received_data = Serial2.read();
      //      if (received_data == 'S')
      //      {
      //        if (array_reached == false)
      //        {
      //          Serial2.print(distance_values[indexx]);
      //          indexx++;
      //          if (indexx > 180)
      //          {
      //            array_reached = true;
      //          }
      //        }
      //        else
      //        {
      //          Serial2.print("F");
      //        }
      //      }
      //    }
      //    // Serial.println("Am terminat o tura");
      //    Serial.print(" distance: ");
      //    Serial.print(distance_values[j]);
      //    Serial.print(" angle: ");
      //    Serial.println(angle_value[j]);
    }
  }
}




bool moveServo()
{
  bool movement;
  static int lastPosServoX;
  static int lastPosServoY;
  if (posServoY != lastPosServoY)
  {
    vertical_Servo.write(posServoY);
    Serial.print("Angle Y: ");
    Serial.println(posServoY);
    lastPosServoY = posServoY;
    movement = true;
    read_flag = false;
  }
  if (posServoX != lastPosServoX)
  {
    horizontal_Servo.write(posServoX);
    Serial.print("Angle X: ");
    Serial.println(posServoX);
    lastPosServoX = posServoX;
    movement = true;
    read_flag = false;

  }
  delay(15);
  return movement;
}

void Lidar_reading(int* distance, int* strength)
{
  static char i = 0;
  char j = 0;
  int checksum = 0;
  static int rx[9];
  if (Serial3.available())
  {
    rx[i] = Serial3.read();
    if (rx[0] != 0x59) {
      i = 0;
    } else if (i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if (i == 8) {
      for (j = 0; j < 8; j++) {
        checksum += rx[j];
      }
      if (rx[8] == (checksum % 256)) {
        *distance = rx[2] + rx[3] * 256;
        *strength = rx[4] + rx[5] * 256;

      }
      i = 0;
    } else
    {
      i++;
    }
  }
}
