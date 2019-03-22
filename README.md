# NeoWatch 24hr DS3231

The 60LED Neopixel watch is a fairly simple yet awesome project i've made. I did this over 48h as a schoolproject in my Embedded class. It uses a 60LED ring to display the time. 

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

***TODO***
- [ ] Make the more advanced circut schematic.


I have soldered everything together on a circut with a ATMega processor (Which was unnecessarily much for such a simple project, but it was required for the class). But I made a simple more readble fritzing scheme. I used this setup when I was testing everything. 
# Schematics #

I have soldered everything together on a circut with a ATMega processor (Which was unnecessarily much for such a simple project). But I made a simple more readble fritzing scheme. I used this setup when I was testing everything. 

![alt text](https://raw.githubusercontent.com/C-HGP/NeoWatch/master/ProjectNeoWatch/Schematics.png)
