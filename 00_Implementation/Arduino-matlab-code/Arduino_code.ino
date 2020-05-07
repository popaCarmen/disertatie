//https://forum.arduino.cc/index.php?topic=575443.0
#include <Arduino.h>
#include "algorithm.h"
#include "max30102.h"

//Bluetooth Transmission
#include <SoftwareSerial.h>
SoftwareSerial blueSerial(11, 12); //RX, TX
char doi;

#define MAX_BRIGHTNESS 255

uint16_t aun_ir_buffer[100]; //infrared LED sensor data
uint16_t aun_red_buffer[100];  //red LED sensor data
int32_t n_ir_buffer_length; //data length
int32_t n_spo2;  //SPO2 value
int8_t ch_spo2_valid;  //indicator to show if the SPO2 calculation is valid
int32_t n_heart_rate; //heart rate value
int8_t  ch_hr_valid;  //indicator to show if the heart rate calculation is valid
uint8_t uch_dummy;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(13, OUTPUT);  //LED output pin 13 on Arduino

  maxim_max30102_reset(); //resets the MAX30102
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  // initialize Bluetooth communication at baudrate 57600
  blueSerial.begin(57600);
  pinMode(10, INPUT);  //pin D10 connects to the interrupt output pin of the MAX30102
  delay(1000);
  maxim_max30102_read_reg(REG_INTR_STATUS_1,&uch_dummy);  //Reads/clears the interrupt status register
    delay(10000);   // Give enough time to open the serial monitor for debugging purposes
    Serial.println(F("Waiting for connection..."));
    delay(1000);
  maxim_max30102_init();  //initialize the MAX30102
}

// the loop routine
void loop() {
  uint32_t un_min, un_max, un_prev_data, un_brightness;  //variables to calculate the on-board LED brightness that reflects the heartbeats
  float f_temp;  
  un_brightness=0;
  un_min=0x3FFFF;
  un_max=0;
  int isample=0;  // Samples counter for debugging purposes
  //char str_buff[50];

  char doi; int val, xval, yval, zval;
  
  n_ir_buffer_length=100;  // buffer length of 100 stores 4 seconds of samples running at 25sps
  //read the first 100 samples, and determine the signal range
  for(i=0;i<n_ir_buffer_length;i++)
  {
    while(digitalRead(10)==1);  //wait until the interrupt pin asserts
    maxim_max30102_read_fifo((aun_red_buffer+i), (aun_ir_buffer+i));  //read from MAX30102 FIFO
    
    if(un_min>aun_red_buffer[i])
      un_min=aun_red_buffer[i];  //update signal min
    if(un_max<aun_red_buffer[i])
      un_max=aun_red_buffer[i];  //update signal max
  }
  un_prev_data=aun_red_buffer[i];
  //calculate heart rate and SpO2 after first 100 samples (first 4 seconds of samples)
  maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);

  //Continuously taking samples from MAX30102.  Heart rate and SpO2 are calculated every 1 second
  
  while(1)
  {
    i=0;
    un_min=0x3FFFF;
    un_max=0;

    //dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
    for(i=25;i<100;i++)
    {
      aun_red_buffer[i-25]=aun_red_buffer[i];
      aun_ir_buffer[i-25]=aun_ir_buffer[i];

      //update the signal min and max
      if(un_min>aun_red_buffer[i])
        un_min=aun_red_buffer[i];
      if(un_max<aun_red_buffer[i])
        un_max=aun_red_buffer[i];
    }

    //take 25 sets of samples before calculating the heart rate.
    for(i=75;i<100;i++)
    {
      un_prev_data=aun_red_buffer[i-1];
      while(digitalRead(10)==1);
      digitalWrite(9, !digitalRead(9));
      maxim_max30102_read_fifo((aun_red_buffer+i), (aun_ir_buffer+i));

        if(blueSerial.available()){
          doi = (char)blueSerial.read();
          if(doi == 'S'){                                //if processing program requests a new measurement
        
        val = analogRead(A2);  // Read from ECG sensor
        xval = analogRead(A3);  // Read value for X axis of accelerometer
        yval = analogRead(A4);  // Read value for Y axis of accelerometer
        zval = analogRead(A5);  // Read value for Z axis of accelerometer
    
        //send samples and calculation result to terminal program through UART
       // PPG sensor
        Serial.print(isample);       //  Print sample number and value
        Serial.print("  ");
        Serial.println(aun_ir_buffer[i], DEC);  // Value of infrared LED of PPG sensor

        blueSerial.print("R");   // Identifier for the value of red LED of PPG sensor
        blueSerial.print(aun_red_buffer[i], DEC);   // Value of red LED of PPG sensor
        blueSerial.print("I");   // Identifier for the value of infrared LED of PPG sensor
        blueSerial.print(aun_ir_buffer[i], DEC);  // Value of infrared LED of PPG sensor
        blueSerial.print("H"); // Identifier for the value of calculated heart rate from PPG sensor
        blueSerial.print(n_heart_rate, DEC);  // Value of calculated heart rate from PPG sensor
        blueSerial.print("V");  // Identifier if calculated heart rate from PPG sensor is valid
        blueSerial.print(ch_hr_valid, DEC);  // 1 - value is valid; 0 - value is not valid
        blueSerial.print("S");  // Identifier for the value of calculated SpO2
        blueSerial.print(n_spo2, DEC);  // Value of calculated Sp02
        blueSerial.print("W");  // Identifier if calculated SpO2 value from PPG sensor is valid
        blueSerial.print(ch_spo2_valid, DEC);  // 1 - value is valid; 0 - value is not valid

        //ECG sensor
        blueSerial.print("E"); // Identifier for the value of ECG sensor
        blueSerial.print(val); // Value of ECG sensor

        //Accelerometer
        blueSerial.print("X"); // Identifier for the value of X axis of the accelerometer
        blueSerial.print(xval); // Value of X axis of the accelerometer
        blueSerial.print("Y"); // Identifier for the value of Y axis of the accelerometer
        blueSerial.print(yval); // Value of Y axis of the accelerometer
        blueSerial.print("Z"); // Identifier for the value of Z axis of the accelerometer
        blueSerial.println(zval); // Value of Z axis of the accelerometer
        isample+=1;
          }
          }
        }
    maxim_heart_rate_and_oxygen_saturation(aun_ir_buffer, n_ir_buffer_length, aun_red_buffer, &n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid);  
  }
}