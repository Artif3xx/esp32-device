/**
 * @author  Castox
 * @file    oled096.cpp
 * @brief   functions to display the collected contend
 */ 

#include "Screen.h"

/**
 * @brief Construct a new Screen::Screen object
 * 
 * @param init_display 
 */
Screen::Screen(Adafruit_SSD1306 &init_display) {
  this->display = &init_display;
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

void print_content() {

}