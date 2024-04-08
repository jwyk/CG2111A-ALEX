// Pin mapping
#define S0 26
#define S1 25
#define S2 23
#define S3 22
#define sensorOut 24
#define colourDelay 50

// Stores frequency read by the photodiodes
uint32_t redFrequency = 0;
uint32_t greenFrequency = 0;
uint32_t blueFrequency = 0;


//Get 5 readings, and return the average frequency reading
int averageFreq() {
  int temp;
  int totalFreq = 0;
  for (int i = 0; i < 5; i++) {
    temp = pulseIn(sensorOut, LOW);
    totalFreq += temp;
    delay(20);
  }
  return totalFreq / 5;
}

void setupColour() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
   //TODO: Delete this after review with teammates
  //Serial.begin(9600);
}

void getColour() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  delay(colourDelay);

  // Reading the output frequency for RED
  redFrequency = averageFreq();
  delay(colourDelay);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  delay(colourDelay);

  // Reading the output frequency for GREEN
  greenFrequency = averageFreq();
  delay(colourDelay);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  delay(colourDelay);
  
  // Reading the output frequency for BLUE
  blueFrequency = averageFreq();
  delay(colourDelay);
}

//Create a Colour packet and send out the response
void sendColour() {
  //TODO: Check if this works
  TPacket colourPacket;
  colourPacket.packetType = PACKET_TYPE_RESPONSE;
  colourPacket.command = RESP_COLOUR;

  colourPacket.params[0] = redFrequency;
  colourPacket.params[1] = greenFrequency;
  colourPacket.params[2] = blueFrequency;  
  colourPacket.params[3] = getDistUltra(); //Add distance as a debugging tool later to see how accurate the colour is
  //TODO: Get the Ultrasonic sensor working.
  sendResponse(&colourPacket);
}
