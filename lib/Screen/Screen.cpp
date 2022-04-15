/**
 * @author  Castox
 * @file    oled096.cpp
 * @brief   functions to display the collected contend
 */ 

#include "Screen.h"



/**
 * @brief Construct a new Screen::Screen object
 * 
 */
Screen::Screen() {
  // start with clear display
  Adafruit_SSD1306 main_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  this->display =  &main_display;
  // 180 degree rotation of the display
  this->display->setRotation(2);
  this->display->clearDisplay();
  this->display->setTextSize(1);
  this->display->setTextColor(WHITE);
  this->display->setCursor(0, 0);
}

/**
 * @brief Destroy the Screen:: Screen object
 * 
 */
Screen::~Screen() {
  this->display->clearDisplay();
  this->display->display();  
}

Adafruit_SSD1306* Screen::get_display() {
  return this->display;
}


/**
 * @brief   set title of the displaied page and cursor to (0,10)
 * @param   const char[]
 */
void Screen::set_title(const char title[]) {
  this->display->setCursor(0, 0);
  this->display->println(title);
  // draw a Line under the heading. One Pixel high
  this->display->drawFastHLine(0, 8, 128, SSD1306_WHITE);
  this->display->display();
}

void Screen::set_title_icon() {
  // content space 9x9 pixels at the top right corner 
}

void print_content() {

}