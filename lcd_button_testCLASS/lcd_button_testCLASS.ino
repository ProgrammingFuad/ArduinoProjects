/*
      1/27/2015
      I copied this sketch from http://linksprite.com/wiki/index.php5?title=16_X_2_LCD_Keypad_Shield_for_Arduino
      Use it to test your Arduino and LCD keypad
      Make sure all buttons work!
      Kevin
*/


/*
 
  This example code is in the public domain.
 
  ---------------------------------------------------------------------
 
  This program demonstrates button detection, LCD text/number printing,
  and LCD backlight control on the Freetronics LCD & Keypad Shield, connected to an Arduino board.
 
 
  Pins used by LCD & Keypad Shield:
 
    A0: Buttons, analog input from voltage ladder
    D4: LCD bit 4
    D5: LCD bit 5
    D6: LCD bit 6
    D7: LCD bit 7
    D8: LCD RS
    D9: LCD E
    D10: LCD Backlight (high = on, also has pullup high so default is on)
 
  ADC voltages for the 5 buttons on analog input pin A0:
 
    RIGHT:  0.00V :   0 @ 8bit ;   0 @ 10 bit
    UP:     0.71V :  36 @ 8bit ; 145 @ 10 bit
    DOWN:   1.61V :  82 @ 8bit ; 329 @ 10 bit
    LEFT:   2.47V : 126 @ 8bit ; 505 @ 10 bit
    SELECT: 3.62V : 185 @ 8bit ; 741 @ 10 bit
*/
/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <LiquidCrystal.h>   // include LCD library
#include <EEPROM.h>

/*
      byte EEPROM.read(int address)
      EEPROM.write(int address, byte data);

/*--------------------------------------------------------------------------------------
  Defines
--------------------------------------------------------------------------------------*/
// Pins in use
#define BUTTON_ADC_PIN           A0  // A0 is the button ADC input
#define LCD_BACKLIGHT_PIN         10  // D10 controls LCD backlight
// ADC readings expected for the 5 buttons on the ADC input
#define RIGHT_10BIT_ADC           0  // right
#define UP_10BIT_ADC            145  // up
#define DOWN_10BIT_ADC          329  // down
#define LEFT_10BIT_ADC          505  // left
#define SELECT_10BIT_ADC        741  // right
#define BUTTONHYSTERESIS         10  // hysteresis for valid button sensing window
//return values for ReadButtons()
#define BUTTON_NONE               0  // 
#define BUTTON_RIGHT              1  // 
#define BUTTON_UP                 2  // 
#define BUTTON_DOWN               3  // 
#define BUTTON_LEFT               4  // 
#define BUTTON_SELECT             5  // 
//some example macros with friendly labels for LCD backlight/pin control, tested and can be swapped into the example code as you like
#define LCD_BACKLIGHT_OFF()     digitalWrite( LCD_BACKLIGHT_PIN, LOW )
#define LCD_BACKLIGHT_ON()      digitalWrite( LCD_BACKLIGHT_PIN, HIGH )
#define LCD_BACKLIGHT(state)    { if( state ){digitalWrite( LCD_BACKLIGHT_PIN, HIGH );}else{digitalWrite( LCD_BACKLIGHT_PIN, LOW );} }
/*--------------------------------------------------------------------------------------
  Variables
--------------------------------------------------------------------------------------*/
byte buttonJustPressed  = false;         //this will be true after a ReadButtons() call if triggered
byte buttonJustReleased = false;         //this will be true after a ReadButtons() call if triggered
byte buttonWas          = BUTTON_NONE;   //used by ReadButtons() for detection of button events



/*--------------------------------------------------------------------------------------
  Init the LCD library with the LCD pins to be used
--------------------------------------------------------------------------------------*/
LiquidCrystal lcd( 8, 9, 4, 5, 6, 7 );   //Pins for the freetronics 16x2 LCD shield. LCD: ( RS, E, LCD-D4, LCD-D5, LCD-D6, LCD-D7 )
/*--------------------------------------------------------------------------------------
  setup()
  Called by the Arduino framework once, before the main loop begins
--------------------------------------------------------------------------------------*/
void setup()
{
   //button adc input
   pinMode( BUTTON_ADC_PIN, INPUT );         //ensure A0 is an input
   digitalWrite( BUTTON_ADC_PIN, LOW );      //ensure pullup is off on A0
   //lcd backlight control
   digitalWrite( LCD_BACKLIGHT_PIN, HIGH );  //backlight control pin D3 is high (on)
   pinMode( LCD_BACKLIGHT_PIN, OUTPUT );     //D3 is an output
   //set up the LCD number of columns and rows: 
   lcd.begin( 16, 2 );
   //Print some initial text to the LCD.
   lcd.setCursor( 0, 0 );   //top left
   //          1234567890123456
   lcd.print( "LinkSprite  16x2" );
   //
   lcd.setCursor( 0, 1 );   //bottom left
   //          1234567890123456
   lcd.print( "Btn:" );
   
  // pinMode(3, OUTPUT);
   pinMode(11, OUTPUT);
   
  // int i = 23;
 //  EEPROM.write(0, i);
}
/*--------------------------------------------------------------------------------------
  loop()
  Arduino main loop
--------------------------------------------------------------------------------------*/
int inc = 2;
void loop()
{
   byte button;
   byte timestamp;
   
   static int position = 0;
   static int count  = 0;
 
   //get the latest button pressed, also the buttonJustPressed, buttonJustReleased flags
   button = ReadButtons();
   //blank the demo text line if a new button is pressed or released, ready for a new label to be written
   if( buttonJustPressed || buttonJustReleased )
   {
     lcd.setCursor( 4, 1 );
     lcd.print( "            " );
   }
   //show text label for the button pressed
   switch( button )
   {
      case BUTTON_NONE:
      {
         break;
      }
      case BUTTON_RIGHT:
      {
        
        count = readInt(10);
         delay(200);
         break;
      }
      case BUTTON_UP:
      {
         //  ++count;
    //    digitalWrite(3, HIGH);
     //   digitalWrite(11, HIGH);
     
     
        /*  asm(
           "sbi 0xB, 3 \n\t "
           ::
         );
        */ 
         
           asm(
           "sbi 0x05, 11 \n\t "    // Trying to turn Pin 11 on. Assuming B is 11 in Hex.
           ::
           );
     
     
          asm volatile(
          "move r16, %1 \n\t "
          "ori r16, 0x05 \n\t "
          "mov  %0, r16 \n\t "
          : "=r" (PORTB)
          : "r" (PORTB)
          );
  
        /* asm volatile(
           "mov r16, %1 \n\t "
           "ori r16, 0x08 \n\t "
           "mov  %0,r16 \n\t"
           : "=r" (PORTD)
           : "r"  (PORTD)
         );
      */
        // PORTD = test;
        
         
        //PORTD = PORTD | 0x08; port d bin 3
        //PORTB = PORTB | 0x08; port b pin 11
       
         count =  addTwo(count, inc);
         lcd.setCursor( 0,0);
        lcd.print( "                " );
         lcd.setCursor( 0, 0 );
         lcd.print( count );
         delay(200);
         break;
      
      }
      case BUTTON_DOWN:
      {
       // --count;
      // digitalWrite(11, LOW);
       
      // PORTB= PORTB | 0xF7; turning portb B pin 11 off  
       
       asm(
           "cbi 0x05, 11 \n\t "
         );
        
        
          asm volatile(
          "move r16, %1 \n\t "
          "andi r16, 0xF7 \n\t "
          "mov  %0, r16 \n\t "
          : "=r" (PORTB)
          : "r" (PORTB)
          );
        
        
        count =  addTwo(count, -inc);
         lcd.setCursor( 0,0);
        lcd.print( "                " );
         lcd.setCursor( 0, 9 );
         lcd.print( count );
         delay(200);
         break;
      }
      case BUTTON_LEFT:
      {
       writeInt(10, count);
         delay(200);
         break;
     }
     case BUTTON_SELECT:
     {
        lcd.setCursor( 4, 1 );
        lcd.print( "SELECT-FLASH" );    
 
        //SELECT is a special case, it pulses the LCD backlight off and on for demo
        digitalWrite( LCD_BACKLIGHT_PIN, LOW );
        delay( 150 );
        digitalWrite( LCD_BACKLIGHT_PIN, HIGH );   //leave the backlight on at exit
        delay( 150 );
 
        /* an example of LCD backlight control via macros with nice labels
        LCD_BACKLIGHT_OFF();
        delay( 150 );
        LCD_BACKLIGHT_ON();   //leave the backlight on at exit
        delay( 150 );
        */
 
        /*
        // an example of LCD backlight control via a macro with nice label, called with a value
        LCD_BACKLIGHT(false);
        delay( 150 );
        LCD_BACKLIGHT(true);   //leave the backlight on at exit
        delay( 150 );
        */
 
        break;
      }
      default:
     {
        break;
     }
   }
   // print the number of seconds since reset (two digits only)
   timestamp = ( (millis() / 1000) % 100 );   //"% 100" is the remainder of a divide-by-100, which keeps the value as 0-99 even as the result goes over 100
   lcd.setCursor( 14, 1 );
   if( timestamp <= 9 )
      lcd.print( " " );   //quick trick to right-justify this 2 digit value when it's a single digit
   lcd.print( timestamp, DEC );
/*  
   //debug/test display of the adc reading for the button input voltage pin.
   lcd.setCursor(12, 0);
   lcd.print( "    " );          //quick hack to blank over default left-justification from lcd.print()
   lcd.setCursor(12, 0);         //note the value will be flickering/faint on the LCD
   lcd.print( analogRead( BUTTON_ADC_PIN ) );
*/
   //clear the buttonJustPressed or buttonJustReleased flags, they've already done their job now.
   if( buttonJustPressed )
      buttonJustPressed = false;
   if( buttonJustReleased )
      buttonJustReleased = false;
}
/*--------------------------------------------------------------------------------------
  ReadButtons()
  Detect the button pressed and return the value
  Uses global values buttonWas, buttonJustPressed, buttonJustReleased.
--------------------------------------------------------------------------------------*/
byte ReadButtons()
{
   unsigned int buttonVoltage;
   byte button = BUTTON_NONE;   // return no button pressed if the below checks don't write to btn
 
   //read the button ADC pin voltage
   buttonVoltage = analogRead( BUTTON_ADC_PIN );
   //sense if the voltage falls within valid voltage windows
   if( buttonVoltage < ( RIGHT_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_RIGHT;
   }
   else if(   buttonVoltage >= ( UP_10BIT_ADC - BUTTONHYSTERESIS )
           && buttonVoltage <= ( UP_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_UP;
   }
   else if(   buttonVoltage >= ( DOWN_10BIT_ADC - BUTTONHYSTERESIS )
           && buttonVoltage <= ( DOWN_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_DOWN;
   }
   else if(   buttonVoltage >= ( LEFT_10BIT_ADC - BUTTONHYSTERESIS )
           && buttonVoltage <= ( LEFT_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_LEFT;
   }
   else if(   buttonVoltage >= ( SELECT_10BIT_ADC - BUTTONHYSTERESIS )
           && buttonVoltage <= ( SELECT_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_SELECT;
   }
   //handle button flags for just pressed and just released events
   if( ( buttonWas == BUTTON_NONE ) && ( button != BUTTON_NONE ) )
   {
      //the button was just pressed, set buttonJustPressed, this can optionally be used to trigger a once-off action for a button press event
      //it's the duty of the receiver to clear these flags if it wants to detect a new button change event
      buttonJustPressed  = true;
      buttonJustReleased = false;
   }
   if( ( buttonWas != BUTTON_NONE ) && ( button == BUTTON_NONE ) )
   {
      buttonJustPressed  = false;
      buttonJustReleased = true;
   }
 
   //save the latest button value, for change event detection next time round
   buttonWas = button;
 
   return( button );
}


void writeInt(int address, int val)
{
  byte *p = (byte *) &val;
  EEPROM.write(address, *p);
   ++p;
  EEPROM.write(address +1, *p);
}

int readInt(int address)
{
  int val;
  byte *p = (byte *) &val;
  *p = EEPROM.read(address);
  ++p;
  *p = EEPROM.read(address + 1);
}

int addTwo(int a, int b)
{
  int c = a + b;
  
   lcd.setCursor( 10, 0 );
         lcd.print( c );
  return c;
  
}

