#include <Wire.h>
#include <RTClib.h>
#include "DST_RTC.h"
#include <DS3231.h>

#include <Adafruit_NeoPixel.h>


// define pins
#define NEOPIN 6
#define LED 4

#define STARTPIXEL 1 // Define Starting LED
DS3231  rtc(SDA, SCL);

//RTC_DS1307 rtc; // Establish clock object

DST_RTC dst_rtc; // Start DST object

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, NEOPIN, NEO_GRB + NEO_KHZ800); // strip object

byte pixelColorRed, pixelColorGreen, pixelColorBlue; // holds color values

// nighttime dimming constants
// brightness based on time of day- could try warmer colors at night?
// 0-15
#define DAYBRIGHTNESS 64
#define NIGHTBRIGHTNESS 20

// cutoff times for day / night brightness. feel free to modify.
#define MORNINGCUTOFF 7  // when does daybrightness begin?   7am
#define NIGHTCUTOFF 22 // when does nightbrightness begin? 10pm

//Init a time-data strutct
Time  t;

void setup () {
  Wire.begin();  // Begin I2C
  rtc.begin();   // begin clock
  pinMode(4, OUTPUT);
  Serial.begin(115200);//Start Serial Monitor
  
  //Serial.begin(9600);
  // set pinmodes
  pinMode(NEOPIN, OUTPUT);

  
  
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(13, 06, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014
  

  strip.begin();
  //strip.show(); // Initialize all pixels to 'off'

  strip.setBrightness(DAYBRIGHTNESS); // set brightness

  // Boot seq
  delay(500);
  colorWipe(strip.Color(255, 0, 0), 20); // Red
  colorWipe(strip.Color(0, 255, 0), 20); // Green
  colorWipe(strip.Color(0, 0, 255), 20); // Blue
  delay(500);
 
}

void loop () {
  digitalWrite(4, HIGH);
  t = rtc.getTime();
   
  Serial.println(rtc.getTimeStr()); // get time


  byte secondval = t.sec;  // get seconds
  byte minuteval = t.min;  // get minutes
  int hourval = t.hour;   // get hours

  // change brightness if it's night time
  // check less often, once per minute
  if (secondval == 0) {
    if (hourval < MORNINGCUTOFF || hourval >= NIGHTCUTOFF) {
      strip.setBrightness(NIGHTBRIGHTNESS);
    } else {
      strip.setBrightness(DAYBRIGHTNESS);
    }
  }

  hourval = hourval % 12; // This clock is 12 hour, if 13-23, convert to 0-11`

  hourval = (hourval * 60 + minuteval) / 12; //each red dot represent 24 minutes.

  // arc mode
  for (uint8_t i = 0; i < strip.numPixels(); i++) {

    if (i <= secondval) {
      // calculates a faded arc from low to maximum brightness
      pixelColorBlue = (i + 1) * (255 / (secondval + 1));
      //pixelColorBlue = 255;
    }
    else {
      pixelColorBlue = 0;
    }

    if (i <= minuteval) {
      pixelColorGreen = (i + 1) * (255 / (minuteval + 1));
      //pixelColorGreen = 255;
    }
    else {
      pixelColorGreen = 0;
    }

    if (i <= hourval) {
      pixelColorRed = (i + 1) * (255 / (hourval + 1));
      //pixelColorRed = 255;
    }
    else {
      pixelColorRed = 0;
    }

    strip.setPixelColor((i + STARTPIXEL) % 60, strip.Color(pixelColorRed, pixelColorGreen, pixelColorBlue));
  }

  //display
  strip.show();

  // printTheTime(theTime);

  // wait
  delay(100);

}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    //strip.setPixelColor(i, c);
    strip.setPixelColor((i + STARTPIXEL) % 60, c);
    strip.show();
    delay(wait);
  }
}
