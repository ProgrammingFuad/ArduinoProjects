#include <LiquidCrystal.h>   // include LCD library
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
#define LEFT_10BIT_ADC          505  // left1
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
   lcd.print( "Fuad Mohamoud"  );
   //
   lcd.setCursor( 0, 1 );   //bottom left
   //          1234567890123456
   lcd.print( "Btn:" );
   
   Serial.begin(9600);
   Serial.print("Hello Fuad\n");
   Serial.print(sizeof(char));
   Serial.print("\n");
   Serial.print(sizeof(long));
   Serial.print("\n");
   Serial.print(sizeof(short));
   Serial.print("\n");
   Serial.print(sizeof(int));
   Serial.print("\n");
   Serial.print(sizeof(float));
   Serial.print("\n"); 
   Serial.print(sizeof(double));
   Serial.print("\n");
   
}
/*--------------------------------------------------------------------------------------
  loop()
  Arduino main loop
--------------------------------------------------------------------------------------*/
void loop()
{
   byte button;
   byte timestamp;
    
 
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
         
        if (buttonWas == BUTTON_RIGHT && buttonJustReleased)
        { 
          Serial.print("Right Released \n");
        }
        
        break;
      }
      case BUTTON_RIGHT:
      {
         lcd.setCursor( 4, 1 );
         lcd.print( "RIGHT" );
          if(buttonJustPressed){
          Serial.print("RIGHT\n");
         
          }break;
      }
      case BUTTON_UP:
      {
        lcd.setCursor( 4, 1 );
          lcd.print("UP"); 
        if(buttonJustPressed){
          Serial.print("UP\n");
         }
        
         break;
      }
      case BUTTON_DOWN:
      {
         lcd.setCursor( 4, 1 );
         lcd.print( "DOWN" );
         if(buttonJustPressed){
          Serial.print("DOWN\n");
         
          }
         
         break;
      }
      case BUTTON_LEFT:
      {
        lcd.setCursor( 4, 1 );
        lcd.print( "LEFT" );
        
        if(buttonJustPressed){
          Serial.print("LEFT\n");
         
          }
        
        break;
     }
     case BUTTON_SELECT:
     {
        lcd.setCursor( 5, 1 );
        lcd.print( "TIGHT-DADDY" );    
 
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
 /*  // print the number of seconds since reset (two digits only)
  // timestamp = ( (millis() / 1000) % 100 );   //"% 100" is the remainder of a divide-by-100, which keeps the value as 0-99 even as the result goes over 100
   lcd.setCursor( 14, 1 );
   if( timestamp <= 9 )
      lcd.print( " " );   //quick trick to right-justify this 2 digit value when it's a single digit
   lcd.print( timestamp, DEC );
*/

 switch(button)
    {
       case BUTTON_RIGHT:
        lcd.print("           ");
         int z= 255;
        lcd.setCursor(12,1);
          lcd.print(" ");
          lcd.print("*");

          break;
    }

 switch(button)
    {
      case BUTTON_LEFT:
       lcd.print("           ");
       int z= 0;
       lcd.setCursor(14,1);
        lcd.print(" ");
        lcd.print(z);

        break;
    }

/*
int count;
count = 1;
if {
  buttonJustPressed || buttonJustReleased
count <100;
then count = count + 1;
lcd.print(count);
break;
}
*/

switch(button)
    {
      case BUTTON_UP:
      int x = 0;
      while (x<100)  
           {  lcd.setCursor( 14,1);
             lcd.print(x);
               x++;
              delay( 50);
             }           
  
  
       break;
      }

switch(button)
{
  case BUTTON_DOWN:
  int y = 99;
  while ( y>1)
  {
    lcd.setCursor(14,1);
    lcd.print(y);
     y--;
     delay(50);
   }

break;
}
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
