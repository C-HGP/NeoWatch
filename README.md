# NeoWatch 24hr DS3231

***TODO***
- [x] Clean up code, make it more readable.
- [x] Update logging for all events.
- [ ] Modulise and put code into neat folders for easy access and tinkering.
- [ ] Create InDesign manuals for easy use. 

The 60LED Neopixel watch is a fairly simple yet awesome project. I did this over 48h as a schoolproject in my Embedded class. It uses a 60LED ring to display the time. 

It does it in 3 different colors using blue, red, and green. 
* Green = Minutes
* Red = Hours
* Blue = Seconds.

When the colors overlap it gets combined so it has a visually nice look to it aswell.
The code halfy taken from Adafruits RingClock example. I have however modified it to get use from the **DS3231** instead of the **DS1307** 

# Components # 
* Arduino Leonardo
* Adafruits 60 LED Ring
* DS3231
* Black Box 
* Cables
* LED Lamp


# Schematics #
To rebuild a exacty copy of the alarm system I made
![alt text](https://raw.githubusercontent.com/C-HGP/NeoWatch/master/ProjectNeoWatch/Schematics.png)
