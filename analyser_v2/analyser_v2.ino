//Board: lgt8f328 https://github.com/dbuezas/lgt8fx
//Dislay: ILI9225 http://www.lcdwiki.com/2.2inch_Arduino_SPI_Module_ILI9225_SKU:MAR2201#Program_Download
//Receiver: NRF24 https://microcontrollerelectronics.com/using-an-nrf24l01-module-to-scan-the-2-4ghz-frequency-range/

#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_SPI.h> //Hardware-specific library

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

void setup() 
{
    mylcd.Init_LCD();
}

void h_l_lines_test(void)
{
    int i=0;
    mylcd.Fill_Screen(BLACK);
    mylcd.Set_Draw_color(WHITE);
    for(i =0;i<mylcd.Get_Display_Height();i+=5){
      mylcd.Draw_Fast_HLine(0,i,mylcd.Get_Display_Width()); 
    }
}

void loop() 
{    
    mylcd.Fill_Screen(WHITE);
    delay(3000);
    h_l_lines_test();
    delay(3000);
}
