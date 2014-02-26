HT1632C-Clock for Arduino
=============

LED Clock for Arduino based on wildstray's awesome [HT1632C Library](https://code.google.com/p/ht1632c/).

Requirements
=============
You first need to download and extract these libraries to Users/*Username*/Documents/Arduino/Libraries

* [Time Library](http://www.pjrc.com/teensy/td_libs_Time.html)
* [DS1307RTC Library](http://www.pjrc.com/teensy/td_libs_DS1307RTC.html)
* [HT1632C Library](https://code.google.com/p/ht1632c/)

Customization
=============

As explained in HT1632C.h you first need to edit the dotmatrix declaration according to your setup:

```c++
ht1632c dotmatrix = ht1632c(&PORTD, DATA_PIN, WRITE_PIN, CLK_PIN, CS_PIN, GEOM_32x16, 1);
```

You can also edit the init method to use another font (check HT1632C.h for the full font list):

```c++
void CLedClock::init()
{
  refresh = 1; // screen refresh flag - set to 1 initially to setup the clock
  dotmatrix.setfont(14); // FONT_7x13
}
```
