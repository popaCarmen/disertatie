#include <Servo.h>

#define X_Serv_Pin 9


Servo horizontal_Servo;

int minPosServo = 0;
int maxPosServo = 180;
int lastPosServo = 0; // variable used for determining if the servo position is different from the previous one
int posServo = minPosServo; // this is the middle position of the servomotor, so that the lidar sensor to be in the middle

int distance_values[180];
int angle_value[180];

bool scanning = true;
bool scanDirection = true;
int scanIncrement = 1;
bool read_flag = 0;

bool moved = false;
bool finished = false;

int i;
int internal_flag = false;
void setup() {
  horizontal_Servo.attach(X_Serv_Pin);

  Serial.begin(9600); //set bit rate of serial port connecting Arduino with computer
  Serial3.begin(115200);  //set bit rate of serial port connecting LiDAR with Arduino
  Serial.println("Start");

  horizontal_Servo.write(minPosServo);
}

void loop() {
  int distance = 0;
  int strength = 0;

  if (finished == false)
  {
    if (read_flag == true)
    {
      if (scanning == true)
      {
        if (scanDirection == true)
        {
          posServo += scanIncrement;
        }
        else
        {
          posServo -= scanIncrement;
        }
        if (posServo > maxPosServo || posServo < minPosServo)
        {
          scanDirection = !scanDirection;
          scanning = false; //???????
        }
      }
      else {
        scanning = true;
        posServo = minPosServo;
        scanDirection = true;
        finished = true;
      }
      posServo = min(max(posServo, minPosServo), maxPosServo);
      moved = moveServo();
    }
    else
    {
      Lidar_reading(&distance, &strength);
      if (distance) {
        if (i <= 180)
        {
          distance_values[i] = distance;
          angle_value[i] = posServo;
        }
        Serial.print(distance);
        Serial.print("cm\t");
        Serial.print("strength: ");
        Serial.println(strength);
        read_flag = true;
        i++;
      }
    }
  }
  else
  {
    // Serial.println("Am terminat o tura");
    if (internal_flag == false)
    {
      for (int j = 0; j <= 180; j++)
      {
        Serial.print(" distance: ");
        Serial.print(distance_values[j]);
        Serial.print(" angle: ");
        Serial.println(angle_value[j]);
      }
      internal_flag = true;
    }
  }

}

bool moveServo()
{
  bool movement;
  static int lastPosServo;
  Serial.print("Angle: ");
  Serial.println(posServo);
  if (posServo != lastPosServo)
  {
    horizontal_Servo.write(posServo);
    Serial.print("Angle: ");
    Serial.println(posServo);
    lastPosServo = posServo;
    movement = true;
    read_flag = false;
    delay(50);
  }
  Serial.println("Stop servo");

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
    // Serial.println( "tfmini serial available" );
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
