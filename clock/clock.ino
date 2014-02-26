#include <Wire.h>
#include <DS1307RTC.h>
#include <Time.h>
#include <ht1632c.h>

#include <stdlib.h>

ht1632c dotmatrix = ht1632c(&PORTD, 7, 6, 4, 5, GEOM_32x16, 2);

class CLedClock
{
private:
  byte refresh;
  byte color;

public:
  void init();
  void run();
};

#define UPPER_DOT_X 15
#define UPPER_DOT_Y 5
#define LOWER_DOT_X 15
#define LOWER_DOT_Y 10

void CLedClock::init()
{
  refresh = 1; // screen refresh flag - set to 1 initially to setup the clock
  dotmatrix.setfont(14); // FONT_7x14
}

//*****************************************************************************************************
// this function is called as part of the main loop;
//
void CLedClock::run()
{
    // if refresh flag is 1, we need to update the digits
    if (refresh)
    {
      // update time
      byte mins = minute(); 
      byte hours = hour();
        
      char buffer[3];

      itoa(hours,buffer,10);

      // fix - itoa removes leading zeros
      if (hours < 10) {
        buffer[1] = buffer[0];
        buffer[0] = '0';
      }
      dotmatrix.putchar( 1, 1, buffer[0], RED);
      dotmatrix.putchar( 8, 1, buffer[1], RED);
     
      itoa(mins,buffer,10); 
      if (mins < 10) {
        buffer[1] = buffer[0];
        buffer[0] = '0';
      } 
      dotmatrix.putchar(18, 1, buffer[0], RED);
      dotmatrix.putchar(25, 1, buffer[1], RED);  
       
      // reset refresh flag
      refresh = 0;
      
      // short wait
      delay(1000);
    }

    // let's make this clock blink, so much more fun!
    if (second() % 2)
      color = 2;
    else
      color = 0;
      
      dotmatrix.plot(UPPER_DOT_X, UPPER_DOT_Y, color);
      dotmatrix.plot(LOWER_DOT_X, LOWER_DOT_Y, color);
      
    // if coming up to secs = 59 we need to update our digits.
    if (second() == 59)
      refresh = 1;
    
    // apply changes
    dotmatrix.sendframe();
 
    delay(500);
}

CLedClock ledClock;

void setup ()
{
  setSyncProvider(RTC.get);
  dotmatrix.clear();
  ledClock.init();
}

void loop ()
{
  ledClock.run();
}
