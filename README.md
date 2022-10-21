# Wifi Analyser Project
Project for scanning available Wifi networks, including hidden and out of range

Built based on Arduino compatible Wemos D1 R2 board

#IDE Setup instruction: 
https://www.instructables.com/Arduino-WeMos-D1-WiFi-UNO-ESP-8266-IoT-IDE-Compati/

https://arduinomaster.ru/datchiki-arduino/esp8266-wemos-d1-mini-raspinovka/

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