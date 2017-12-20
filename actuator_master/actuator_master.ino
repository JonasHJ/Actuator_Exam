//Libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

// Pins
const char buttonPin = 11;

// Global variables
bool buttonState = 0;
unsigned short prevDist = 0;

// Function measuring whether button is held down or not
double cmToInch(unsigned short &cmDist)
{
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) 
  {
    lcd.setCursor(7,1); 
    lcd.print("      "); 
    lcd.setCursor(7,1);
    lcd.print("inch");
    return cmDist*0.393700787;
  }
  else 
  {
    lcd.setCursor(7,1); 
    lcd.print("      "); 
    lcd.setCursor(7,1); 
    lcd.print("cm");
    return cmDist;
  }
}

void setup() 
{
  pinMode(buttonPin, INPUT);
  
  // Communication with slave
  Wire.begin();
  
  // LCD display
  lcd.begin(16,2);
  lcd.backlight();

  // Set cursor and print
  lcd.setCursor(0,0); //Defining positon to write from first row,first column .
  lcd.print("Distance: "); //You can write 16 Characters per line .lcd.setCursor(0,1);  //Defining positon to write from second row,first column .
}

void loop() 
{
  // Request two bytes from slave nr. 8
  Wire.requestFrom(8, 2);

  // If data is available
  while (Wire.available())
  { 
    // Combine the two bytes
    unsigned short cmDist = Wire.read() << 8 | Wire.read(); 

    // Define output for LCD
    double cmInch = cmToInch(cmDist);

    // Check if distance = previous distance
    if(prevDist != cmInch)
    { 
      lcd.setCursor(0,1); 
      lcd.print("       ");
      lcd.setCursor(0,1);

      // Check if distance is above limit
      if (cmInch < 800)
      {
        lcd.print(cmInch);
      }
    }
    prevDist = cmInch;
  }
  delay(300);
}





