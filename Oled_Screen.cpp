
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Oled_Screen.h"


Oled_Screen :: Oled_Screen(int oled_mosi, int oled_clk, int oled_dc, int oled_cs, int oled_reset) :
			Adafruit_SSD1306(oled_mosi, oled_clk, oled_dc, oled_reset, oled_cs){
			};

void Oled_Screen :: init(){
	tempoState=false;
		this->begin(SSD1306_SWITCHCAPVCC);
// 		// this->display();
		this->clearDisplay();
// 		// this->fillCircle(35, 35, 2, WHITE);
// 		// this->display();

// 		String i="ORSINI";
// 		String i2=" ";
// // display.print(i);
// 		this->setTextColor(WHITE);

// 		this->setTextSize(3);
// 		this->setCursor(10,0);

// 		this->print(i);

// 		this->setCursor(20,40);
// 		this->setTextSize(0);
// 		this->print(i2);
		// this->display();


//   this->setTextSize(1);
//   this->setTextColor(WHITE);
//   this->setCursor(20,20);
// int nchar=40;
// int start=0;
//   for (uint8_t i=start; i < 10; i++) {
//     if (i == '\n') continue;
//     this->write(i);
//     if ((i > 0) && (i % 21 == 0))
//       this->println();
//   }
//   this->display();


		// delay(20);

}
void Oled_Screen :: drawParameter(int xpos, int ypos, int w, int h,String title, String text){
		String a=title;
		String b=text;

		this->setTextSize(2);
		this->setTextColor(WHITE);
		this->setCursor(xpos,ypos+2);


		this->fillRect(xpos, ypos, w, h, BLACK);
		this->print(b);

		this->setTextSize(1);
		this->setTextColor(WHITE);
		this->setCursor(xpos,ypos+18);

		this->fillRect(xpos, ypos+18, w, h/2, BLACK);

		this->print(a);
		this->display();
}
void Oled_Screen :: drawParameterInverted(int xpos, int ypos, int w, int h,String title, String text){
		String a=title;
		String b=text;

		this->setTextSize(2);
		this->setTextColor(BLACK);
		this->setCursor(xpos+1,ypos+2);


		this->fillRect(xpos, ypos, w, h, WHITE);
		this->print(b);

		this->setTextSize(1);
		this->setTextColor(WHITE);
		this->setCursor(xpos+1,ypos+18);

		this->fillRect(xpos, ypos+18, w, h/2, BLACK);

		this->print(a);
		this->display();
}


// void Oled_Screen :: drawParameter2(int xpos, int ypos, int w, int h,String title, String text){
// 		this->setTextSize(2);
// 		this->setTextColor(WHITE);
// 		this->setCursor(xpos+2,ypos+2);
// 		String a=title;

// 		this->fillRect(xpos, ypos, w, h, BLACK);
// 		this->print(a);

// 		this->setTextSize(2);
// 		this->setTextColor(WHITE);
// 		this->setCursor(xpos,ypos+22);
// 		String b=text;
// 		this->fillRect(xpos, ypos+22, w, h, BLACK);

// 		this->print(b);
// 		this->display();
// }

void Oled_Screen :: drawTextSquare(int xpos, int ypos, int w, int h,String title, String text){
		this->fillRect(xpos-2, ypos-11, w, h, BLACK);

		this->setTextSize(0);
		this->setTextColor(WHITE);
		this->setCursor(xpos,ypos-10);
		String a=title;
		this->print(a);
		this->fillRect(xpos-2, ypos-1, w, h, WHITE);
		this->setTextSize(0);
		this->setTextColor(BLACK);
		this->setCursor(xpos,ypos);
		String b=text;

		this->print(b);
		this->display();
}
void Oled_Screen :: fillBlank(int xpos, int ypos, int w, int h){
		this->fillRect(xpos-2, ypos-11, w, h*2, BLACK);

		// this->setTextSize(0);
		// this->setTextColor(BLACK);
		// this->setCursor(xpos,ypos-10);
		// String a=title;
		// this->print(a);
		// this->fillRect(xpos-2, ypos, w, h, BLACK);
		// this->setTextSize(0);
		// this->setTextColor(BLACK);
		// this->setCursor(xpos,ypos);
		// String b=text;

		// this->print(b);
		this->display();
}

void Oled_Screen :: drawTextSquareInverted(int xpos, int ypos, int w, int h,String title, String text){
		this->fillRect(xpos-2, ypos-11, w, h, WHITE);
		this->setTextSize(0);
		this->setTextColor(BLACK);
		this->setCursor(xpos,ypos-10);
		String a=title;
		this->print(a);
		this->fillRect(xpos-2, ypos-1, w, h, BLACK);
		this->setTextSize(0);
		this->setTextColor(WHITE);
		this->setCursor(xpos,ypos);
		String b=text;

		this->print(b);
		this->display();
}

void Oled_Screen :: drawPixelTempo(byte tickC){

		if (tickC == 0){
			this->fillRect(110, 3, 3, 3, BLACK);
			this->fillRect(110, 5, 1, 1, WHITE);

			this->drawPixel(16, 5, WHITE);

		}
	    else
	    {
			this->fillRect(110, 3, 3, 3, WHITE);
			this->fillRect(110, 5, 1, 1, BLACK);

			this->drawPixel(126, 5, BLACK);

	    }


		this->display();
}
