#include <GyverOLED.h>
GyverOLED<SSH1106_128x64> oled;

char Lorem_ipsum[] = "Lorem ipsum dolor sit amet, лорем ипсум долор сит амет привет народ ё, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip...";
void setup() {
  Serial.begin(9600);
  oled.init();              // инициализация
}

void loop() {
  showText();
}

void showText() {
  oled.clear();
  oled.home();
  oled.autoPrintln(true);
  oled.setScale(1);
  oled.print("Test message output");
  oled.update();
  delay(5000);
}
