

#ifndef Oled_Screen_h
#define Oled_Screen_h
#include <Arduino.h> 

#define OLED_MOSI  22       // 9 
#define OLED_CLK   21       //10 
#define OLED_DC    20       //11 
#define OLED_CS    18       //12 
#define OLED_RESET 19       //13
class Oled_Screen : public Adafruit_SSD1306
{ // Down here where the damned thing belongs
public: 
    bool tempoState;
    Oled_Screen(int oled_mosi, int oled_clk, int oled_dc, int oled_cs, int oled_reset);
    void init(); 
    void drawTextSquare(int xpos, int ypos, int w, int h, String title, String text);
    void drawTextSquareInverted(int xpos, int ypos, int w, int h, String title, String text);
    void drawParameter(int xpos, int ypos, int w, int h, String title, String text);
    void drawParameterInverted(int xpos, int ypos, int w, int h, String title, String text);
    void fillBlank(int xpos, int ypos, int w, int h);
    void drawPixelTempo(byte tickC);
     
private:  
    // typedef enum {INTERNAL, MIDI} clock_type; 
    // struct  
    // {   
    //     clock_type clockMode;  
    //     float tempo; 

    //     int globalDivision;
    // }configuration; 

    // Adafruit_SSD1306 disp;
    
};

#endif