//SDA pin to be connected to pin 20
//SCL pin to be connected to pin 21, both for arudino mega 2560

#include <LiquidCrystal_I2C.h>

/* #include <Wire.h>

void setup() {
  Serial.begin(9600);

  Serial.println("\nI2C Scanner");
  Serial.println("Scanning...");
  byte device_count = 0;

  Wire.begin();
  for (byte address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
     // Serial.print ("Found address: ");
      Serial.print("I2C device found at address 0x");
      Serial.print(address, HEX);
      Serial.println("  !");
      device_count++;
      delay(1);
    }
  }
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (device_count);
  Serial.println (" device(s).");
}

void loop() {}
*/

//uncomment the top part only when you want to find the address of the LCD

void lcd_setup()
{
  lcd.init(); //initialise display
  lcd.clear(); //clear display buffer
}

void write_message(char* message)
{  
  lcd.setCursor(1,1);
  lcd.print(message);
}

void flash_message(char* message)
{
  int currenttime = millis();
  write_message(message);
  while(millis() != (currenttime + 1000));
  lcd.clear();
  while(millis() != (currenttime + 2000));
  write_message(message);
}
