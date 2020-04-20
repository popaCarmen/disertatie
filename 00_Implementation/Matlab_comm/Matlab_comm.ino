// Declare variables
int rawSensorVal;
String incomingString;

void setup() {
  // Initialize serial port
  Serial.begin(115200);
  Serial.setTimeout(3);
}

void loop() {
  if (Serial.available() > 0)
  {
    Serial.println("matLab");
  }
  else
  {
    Serial.println("NON");
  }
}
