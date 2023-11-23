
#pragma once
#ifndef LCD_HPP
#define LCD_HPP

class LiquidCrystal;

#include "../AppEnv.hpp"
class App;

class Lcd {
   private:
    const static int lcdRows = 2;
    const static int lcdCols = 16;

    LiquidCrystal* lcd;

   public:
    int test = 10;
    Lcd(Pin rs, Pin e, Pin db4, Pin db5, Pin db6, Pin db7);

    void setLineText(int line, char* text, bool centered);
    void setText(char texts[2][17]);
    // TODO find error in this function
    template <typename T_App>
    void update(T_App* app, char texts[2][17]);

    template <typename T_App>
    void activateApp(T_App* app);
};

#endif /* LCD_HPP */