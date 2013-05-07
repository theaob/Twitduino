#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 
// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
 
// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   
 return btnNONE;  // when all others fail, return this...
}
 
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0,0);
}
 
int lcdIndex = 0;
int lcdLine = 0;
  
void loop()
{
 lcd_key = read_LCD_buttons();  // read the buttons
 
 while( Serial.available() > 0 )
 {
   char value = Serial.read();
   
   if ( value != -1 )
   {
     lcd.print(value);
     lcdIndex++;
     if( (lcdIndex > 16) && (lcdLine == 0) )
     {
       lcdIndex = 0;
       lcdLine++;
       moveCursor();
     }
     else if ( (lcdIndex > 16) && (lcdLine == 1))
     {
       lcdIndex = 0;
       lcdLine = 0; 
       moveCursor();
     }
   }
 }
}

void moveCursor()
{
  if( lcdLine == 0)
     lcd.setCursor(1, 0); 
  else
     lcd.setCursor(0,0);
}
