# Wifi Analyser Project
Project for scanning available Wifi networks, including hidden and out of range

Built based on Arduino compatible Wemos D1 R2 board

#IDE Setup instruction: 
https://www.instructables.com/Arduino-WeMos-D1-WiFi-UNO-ESP-8266-IoT-IDE-Compati/

https://arduinomaster.ru/datchiki-arduino/esp8266-wemos-d1-mini-raspinovka/
 
(board manager URL is)
http://arduino.esp8266.com/stable/package_esp8266com_index.json
Then select Wemos D1 R2 in Tools->Board

#TFT Screen setup instruction
u2glib is not working with ESP

Using Adafruit and Adafruit GFX
https://electropeak.com/learn/interfacing-sh1106-1-3-inch-i2c-oled-128x64-display-with-arduino/

https://kit.alexgyver.ru/tutorials/oled/

SCK-->D1 --> Wemos D15(SCL)
SDA-->D2 --> Wemos D14(SDA)

LCD controller is SH1106 (not SSD1306) and therefore it's having issues with Adafruit
https://forum.arduino.cc/t/oled-1-3-i2c-iic-128x64-serial-lcd-faulty/250171/16
Using GyverOLED with GyverOLED<SSH1106_128x64> oled solves the issue

#ESP notes
Scan for available networks
https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/scan-class.html
Sadly but ESP can only scan 14 wifi channels. That's not enough, therefore trying to use nrf24l01 module

#NRF notes & Wemos pinouts
Connecting nrf24l01
https://www.reddit.com/r/arduino/comments/oik5ou/wemos_d1_r2_nrf24l01/

https://forum.arduino.cc/t/wemos-d1-pins/523831/15

#2022-12-11 an attempt to use lgt8f328p-lqfp32 
based on lgt8f328p-lqfp32 board (arduino compatible)
Setup instruction https://github.com/dbuezas/lgt8fx
Install it from Board manager!
Mine is lgt8f328

Display TFT LCD 2.2 SPI ILI9225
