//Pin mapping
#define TRIG_PIN 30
#define ECHO_PIN 31
#define SPEED_OF_SOUND 340
//Returns the distance between wall and ultrasonic sensor
uint32_t getDistUltra() {
  //Clear TRIG_PIN
  digitalWrite(TRIG_PIN,LOW);
  delayMicroseconds(2);

  //Set TRIG_PIN on HIGH for 10us
  digitalWrite(TRIG_PIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN,LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * SPEED_OF_SOUND / 20000 - 2; 
}

//Send the distance from wall as a TPacket
void sendDist() {
  uint32_t distance = getDistUltra();
  TPacket distPacket;
  distPacket.packetType = PACKET_TYPE_RESPONSE;
  distPacket.command = RESP_DIST;
  distPacket.params[0] = distance;
  sendResponse(&distPacket);
}