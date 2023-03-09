
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

byte smile[8] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// initialize the pins:
int relayPin = 3;
const int sensor_pin = A1;



void setup() {

  Serial.begin(9600);
  
  pinMode(relayPin,OUTPUT); //output pin for relay board, this will sent signal to the relay
  digitalWrite(relayPin,HIGH);
  
  lcd.init();// initialize the LCD 
  lcd.setBacklight(1); // Turn on the blacklight and print a message.
  lcd.createChar(0, smile);

  lcd.setCursor(0, 0);
  lcd.print("Hi ");
  lcd.write(byte(0));// Display the custom character 0, the smile

  lcd.setCursor(0, 1);
  lcd.print("I'm the gardener");

  delay(5000);
  lcd.clear();
  

}

void loop() {

  float moisture_percentage = 0;
  int moisture = 0;

  //calculate the moisture of soil that comes from the sensor to the percentage
  moisture = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (moisture/1023.00) * 100 ) );

  //print moisture_percentage to serial monitor
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("%\n\n");

  //print moisture_percentage to LCD display
  lcd.setCursor(0, 0);
  lcd.print("moisture ");
  lcd.print(moisture_percentage);
  lcd.print("%");

  
  //If the soil moisture is less than acceptable, turn on the pump until it returns to the acceptable degree
  while(moisture_percentage < 40){ 
  
      digitalWrite(relayPin,LOW); //low to proving signal and water 
      Serial.println("Low moisture, needs watering.."); // for testing
      delay(100); 

      digitalWrite(relayPin,HIGH); //HIGH to stop the signal and water 
      delay(5000);

      moisture = analogRead(sensor_pin); // read the moisture of soil again to sure the plant got enough water
      moisture_percentage = ( 100 - ( (moisture/1023.00) * 100 ) ); 
      
  }
  delay(2000);
  lcd.clear(); // clear the display unit
  
}
