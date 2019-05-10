#include <Wire.h>
#include <RTClib.h>
#include "DST_RTC.h"
#include <DS3231.h>
#include <Adafruit_NeoPixel.h>

// define pins
#define NEOPIN 6
#define LED 4
#define FAN 2

#define STARTPIXEL 60 // Define Starting LED
DS3231  rtc(SDA, SCL);

DST_RTC dst_rtc; // Start DST object

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, NEOPIN, NEO_GRB + NEO_KHZ800); // strip object

byte pixelColorRed, pixelColorGreen, pixelColorBlue; // holds color values

//Define the amount of brightness the watch generates during different times of the day
#define DAYBRIGHT 50
#define NIGHTBRIGHT 20


// cutoff times for day / night brightness.
#define MORNINGCUTOFF 7  // when does daybrightness begin?   7am
#define NIGHTCUTOFF 20 // when does nightbrightness begin? 10pm

//Init a time-data strutct
Time  t;

void setup () {
  Wire.begin();  // Begin I2C
  rtc.begin();   // begin clock
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);//Start Serial Monitor
  
  //Serial.begin(9600);
  // set pinmodes
  pinMode(NEOPIN, OUTPUT);

  
  
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(13, 06, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2019
  

  strip.begin();
  //strip.show(); // Initialize all pixels to 'off'


  // Boot seq
  delay(500);
  colorWipe(strip.Color(255, 0, 0), 20); // Red
  colorWipe(strip.Color(0, 255, 0), 20); // Green
  colorWipe(strip.Color(0, 0, 255), 20); // Blue
  delay(500);
 
}

void loop () {
  digitalWrite(4, HIGH);
  digitalWrite(2, HIGH);
  t = rtc.getTime();
   
  Serial.println(rtc.getTimeStr()); // get time


  byte secondval = t.sec;  // get seconds
  byte minuteval = t.min;  // get minutes
  int hourval = t.hour;   // get hours
  int watchBrightness;

  // change brightness if it's night time
  // check less often, once per minute
  if (secondval == 0) {
    if (hourval < MORNINGCUTOFF || hourval >= NIGHTCUTOFF) {
      watchBrightness = NIGHTBRIGHT; // The brightness at night
    } else {
      watchBrightness = DAYBRIGHT; // The brightness at day
    }
  }

  strip.setBrightness(watchBrightness); // set brightness of the watch depending on what time it is

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


  //Debug to help you read from the serial monitor.
  //TO-DO Add a display which holds the time and day in digital format.
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
