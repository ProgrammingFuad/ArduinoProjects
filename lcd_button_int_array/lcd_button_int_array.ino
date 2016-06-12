/*
      CSCI 3/30/2015
      
      This program shows an example function to fill an array of integers with the
      first n (in this case 20) perfect squares.  What makes it interesting that the code
      in the function is all inline assembly. The left and right buttons move you throught the 
      array so you can see the elements.
      
      Your assignment:
      
      Wire up the up and down buttons to cycle you through the different ways we are
      going to fill the array.
      
      1. perfect squares //done!!
      2. 5 to 100 by 5's 
      3. powers of 2 e.g. 1 2 4 8 ... //do this the easy way with the shift operator
                                      //any problems with big numbers? Don't fix
      4. factorial   e.g 1 2 6 24  //Done??
      
      
      
      
      
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
   
   pinMode( 0, OUTPUT );

  Serial.begin(9600);


}

char name[10] = "HelloWrld";

//the data structure to fill in
#define MAX_SIZE 20
int myIntArray[MAX_SIZE] = {0};
int index = 0;


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
         break;
      }
      case BUTTON_RIGHT:
      {
        index = (index +1) % MAX_SIZE;
         displayArrayElement(myIntArray,  index);
         delay(200);
         break;
      }
      case BUTTON_UP:
      {
         fillSquares(myIntArray,  MAX_SIZE);
         delay(100);
         displayArrayElement(myIntArray,  index);
         delay(200);
         break;
      }
      case BUTTON_DOWN:
      {
       fillFactorial(myIntArray,  MAX_SIZE);
       int len = myStringLength(name);
         lcd.setCursor( 4, 1 );
         lcd.print( name);
          lcd.print( len);
         break;
      }
      case BUTTON_LEFT:
      {
        index = (index + (MAX_SIZE-1) ) % MAX_SIZE;
         displayArrayElement(myIntArray, index);
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


void fillEvens(int A[], int n)
{
  asm volatile(
      "clr r0  \n\t"          //this will be our counter
      "ldi r16, 5 \n\t"      //this is what we are filling the array with
      "ldi r17, 5 \n\t"
      "1: cp r0, %1  \n\t"    //compare the counter against loop stop
      "breq 2f \n\t"
      "st z, r16  \n\t"
      "add  r16, r17 \n\t"   //count by fives
      "adiw r30, 2  \n\t"
      "inc r0  \n\t"
      "rjmp 1b \n\t"
      "2: nop \n\t"
      :                       //output variable
      : "z" (A), "r" (n)      //input variables, note that register z is a pointer
      : "r16", "r17"          //clobber list
    );
  int i;
  
  
   Serial.println( n);
  for(i = 0; i < MAX_SIZE; ++i)
  {
    Serial.println( (int )A[i]);
  }
  
}

void fillSquares(int A[], int n)
{
  asm volatile(
      "ldi r16, 1           \n\t"          //this will be our counter
      "ldi r17, 0          \n\t"
      "top%=: cp %[n], r16  \n\t"    //compare the counter against loop stop, notice the order
      "brlt out%=            \n\t"           // no branch if greater so reversed the cp order
      "mul r16, r16 \n\t"      //answer from mul is two bytes in r0, r1
      "movw r18, r0 \n\t"           //move so we can do the rest of the mult
      "mul r17, r16 \n\t"
      "add  r19, r0 \n\t"
      "mul r16, r17 \n\t"   //I know, but keep track of the registers for two different operand
      "add  r19, r0 \n\t"
      "st z+, r18  \n\t"         //store the low byte and move z to the next byte 
      "st z+, r19 \n\t"       //store the high byte and move z to the next byte
      "inc  r16 \n\t"          //inc counter
 //    "adiw r30, 2  \n\t"      //now move the pointer to the next integer in A
      "rjmp top%= \n\t"           // bottom of the loop
      "out%=: clr r1 \n\t"         // clean up since addiw uses this register
      :                       //output variables
      : "z" (A),[n] "r" (n)      //input variables, note that register z is a pointer to our array A
      : "r16", "r17"                 //clobber list
    );

}

int incCount(int count, int inc)
{
    int out;
  
    asm volatile(
      "add %A1, %A2  \n\t"
      "adc %B1, %B2  \n\t"
      "mov %A0, %A1  \n\t"
      "mov %B0, %B1  \n\t"
      : "=r" (out)
      : "r" (count), "r" (inc)
    );
    return out;
}

int myStringLength(char *p)
{
  int count = 0;
  asm volatile(
     "clr r0  \n\t"
     "1: ld r16, x+ \n\t"
     "cpi r16, 0x0  \n\t"
     "breq 2f \n\t"
     "inc r0 \n\t"
     "rjmp 1b \n\t"
     "2: nop \n\t"
     "mov r16, r0\n\t"
    "ldi %B0, 0 \n\t"
    "mov %A0, r16 \n\t"
    :"=d" (count)
    : "x" ( p)
    : "r0", "r16", "r18"
  
  );
  
  return count;
}

/*
    Simple function to display an element of an array on
    the first line of the LCD screen
*/
void displayArrayElement(int A[], int which)
{
    char label[20];
    sprintf(label, "[%2d] = %3d", which, A[which]);
    lcd.setCursor( 0, 0 );
    lcd.print( "                " );
     lcd.setCursor( 0, 0 );
    lcd.print( label );
}

void fillFactorial(int A[], int n)
{
  int i;
  int *p = A;
  *p = 1; //1!
  ++p;
  for(i = 2; i <= n; ++i)
  {
     *p = *(p-1) * i;
     ++p;
  }
  
  
}
