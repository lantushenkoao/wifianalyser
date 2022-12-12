//Board: lgt8f328 https://github.com/dbuezas/lgt8fx
//Dislay: ILI9225 http://www.lcdwiki.com/2.2inch_Arduino_SPI_Module_ILI9225_SKU:MAR2201#Program_Download
//Receiver: NRF24 https://microcontrollerelectronics.com/using-an-nrf24l01-module-to-scan-the-2-4ghz-frequency-range/

//LCD related
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_SPI.h> //Hardware-specific library

//NRF24 related
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//LCD pinout define
#define MODEL ILI9225
#define CS   A5
#define CD   A3
#define RST  A4
#define SDA  A2
#define SCK  A1
#define LED  A0   //if you don't need to control the LED pin,you should set it to -1 and set it to 3.3V

//NRF pinout define
#define NRF_MISO  D12
#define NRF_MOSI  D11
#define NRF_SCK   D13
#define NRF_CE    D9
#define NRF_CSN   D10
#define NRF_GND
#define NRF_VSS

//#define NRF_MAX_LEVEL 255
//the definiens of software spi mode as follow:
//if the IC model is known or the modules is unreadable,you can use this constructed function
LCDWIKI_SPI mylcd(MODEL,CS,CD,-1,SDA,RST,SCK,LED); //model,cs,dc,sdo,sda,reset,sck,led

//define some colour values
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define LCD_WIDTH 220 //x
#define LCD_HEIGHT 176 //y

#define CHART_PADDING     10

//NRF24 configuration
RF24 radio(NRF_CE,NRF_CSN);
const uint8_t num_channels = 128;
uint8_t values[num_channels];
const int num_reps = 15;

const int lcd_chart_x_min = CHART_PADDING;
const int lcd_chart_y_min = CHART_PADDING;

const int lcd_chart_x_max = LCD_WIDTH  - lcd_chart_x_min - CHART_PADDING;
const int lcd_chart_y_max = LCD_HEIGHT - lcd_chart_y_min - CHART_PADDING;

const int lcd_chart_width  = LCD_WIDTH  - (CHART_PADDING * 2);
const int lcd_chart_height = LCD_HEIGHT - (CHART_PADDING * 2);

const double channel_width = (double)lcd_chart_width / (double)num_channels;

void setup(){
  mylcd.Init_LCD();
  mylcd.Set_Rotation(3);
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Text_Mode(0);
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Text_colour(WHITE);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(1);
  mylcd.Print_String("Scainning 2.4GHz networks", 0, 0);
  print_axis();
  
  radio.begin();
  radio.setAutoAck(false);

  // Get into standby mode
  radio.startListening();
  radio.stopListening();

}


void loop(){    
 //lcd_test();
 test_nrf();
}

void test_nrf(){
    // Clear measurement values
  memset(values,0,sizeof(values));

  // Scan all channels num_reps times
  int rep_counter = num_reps;
  while (rep_counter--){
    int i = num_channels;
    while (i--){
      // Select this channel
      radio.setChannel(i);

      // Listen for a little
      radio.startListening();
      delayMicroseconds(255);
      

      // Did we get a carrier?
      if ( radio.testCarrier() ){
        ++values[i];
      }
      radio.stopListening();
    }
  }

  // Print out channel measurements, clamped to a single hex digit
  int i = 0;
  while ( i < num_channels ){
    print_channel(i, min(num_reps, values[i] * 5));
    //printf("%x ; ",values[i]);
    ++i;
  }
  //printf("\n\r");
}

void lcd_test(){

  print_channel(1, 10);
  print_channel(2, 50);
  print_channel(3, 50);
  print_channel(100, 20);
  delay(1000);
}

void print_axis(){
  mylcd.Set_Draw_color(WHITE);
  mylcd.Draw_Fast_VLine(lcd_chart_x_min - 2, lcd_chart_y_min, lcd_chart_y_max - lcd_chart_y_min + 2); 
  mylcd.Draw_Fast_HLine(lcd_chart_x_min - 2, lcd_chart_y_max + 2, lcd_chart_x_max - lcd_chart_x_min); 

  //separate normal Wifi channels (1..16) with a white line
  mylcd.Draw_Fast_VLine(lcd_chart_x_min + 16 * channel_width, lcd_chart_y_max, LCD_WIDTH - lcd_chart_y_max); 
}

void print_channel(int channelNo, int value){
 
  //whipe up previous value
  mylcd.Set_Draw_color(BLACK);
  mylcd.Draw_Fast_VLine(lcd_chart_x_min + (channelNo * channel_width), lcd_chart_y_min, lcd_chart_y_max - lcd_chart_y_min); 
  //draw new value
  mylcd.Set_Draw_color(BLUE);
  const int normalisedValue = lcd_chart_y_max - value * (lcd_chart_height - CHART_PADDING)/ num_reps;
  const int barHeight = lcd_chart_y_max - normalisedValue;
  const int barY = barHeight - value;
  mylcd.Draw_Fast_VLine(lcd_chart_x_min + (channelNo * channel_width), normalisedValue, barHeight); 
}
