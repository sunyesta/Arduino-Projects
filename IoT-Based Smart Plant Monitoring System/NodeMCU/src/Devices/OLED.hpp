

#ifndef OLED_HPP
#define OLED_HPP

#include <Wire.h>

#include "./PressureTempSensor.hpp"
#include "SSD1306Wire.h"
// Only needed for Arduino 1.6.5 and earlier
// #include <images.h>  // Optionally include custom images

#define DEMO_DURATION 3000
#define LINE_WIDTH 200
#define LINE_HEIGHT 8
#include "../AppEnv.hpp"

class OLED : public Loopable {
   private:
    Pin scl, sda;  // digital pins
    SSD1306Wire *display;
    Debounce *lastWatered = new Debounce(5);
    Debounce *popupScreenDB = new Debounce(2000);
    char popupText[50];

   public:
    OLED(Pin digital_scl, Pin digital_sda) {
        this->scl = digital_scl;
        this->sda = digital_sda;

        this->display = new SSD1306Wire(0x3c, sda, scl);

        display->init();

        display->flipScreenVertically();
        display->setFont(ArialMT_Plain_10);

        redraw();
    }

    void drawRectDemo() {
        // Draw a pixel at given position
        for (int i = 0; i < 10; i++) {
            display->setPixel(i, i);
            display->setPixel(10 - i, i);
        }
        display->drawRect(12, 12, 20, 20);

        // Fill the rectangle
        display->fillRect(14, 14, 17, 17);

        // Draw a line horizontally
        display->drawHorizontalLine(0, 40, 20);

        // Draw a line horizontally
        display->drawVerticalLine(40, 0, 20);
    }

    int curLine = 0;
    void writeOnNextLine(char *buff) {
        display->drawString(0, curLine * LINE_HEIGHT, buff);
        curLine++;
    }
    void resetLineNumber() { curLine = 0; }
    char buff[50];
    void drawAllData() {
        // TODO fix the moistuer printing

        // sprintf(buff, "Temp =  %dC*\n Pressure = %dPa\n lightness = %d",
        //         appEnv->devices->pressureTempSensor->temperature_C(),
        //         appEnv->devices->pressureTempSensor->pressure_Pa(),
        //         appEnv->devices->lightSensor->lightness());
        display->setTextAlignment(TEXT_ALIGN_LEFT);

        (appEnv->data->isAutomatic()) ? (sprintf(buff, "automatic"))
                                      : (sprintf(buff, "manual"));
        writeOnNextLine(buff);

        sprintf(buff, "light level = %d ", appEnv->data->lightLevel());
        writeOnNextLine(buff);
        // display->drawString(0, 0, buff);

        // display->drawString(0, 1 * LINE_HEIGHT, buff);

        sprintf(buff, "moisture = %d", appEnv->data->soilMoisture());
        writeOnNextLine(buff);

        sprintf(buff, "pressure = %d", appEnv->data->pressure());
        writeOnNextLine(buff);
        // display->drawString(0, 1 * LINE_HEIGHT, buff);

        sprintf(buff, "temperature = %d", appEnv->data->temperature());
        writeOnNextLine(buff);
        // display->drawString(0, 1 * LINE_HEIGHT, buff);

        if (appEnv->data->wateringNow()) {
            sprintf(buff, "X");
        } else {
            sprintf(buff, "_");
        }
        display->setTextAlignment(TEXT_ALIGN_RIGHT);
        display->drawString(128, 0, buff);
    }

    void runPopupScreen(char *text) {
        popupScreenDB->start();
        sprintf(popupText, "%s", text);
    }

    void drawPopupScreen() {
        display->drawString(0, 0 * LINE_HEIGHT, popupText);
    }

    void drawAlternatingScreens() {
        static Debounce *nextDB = new Debounce(3000);
        static int curScreen = 0;
        static const int maxScreens = 4;
        if (nextDB->isValidRestart()) {
            Serial.println("next screen");
            curScreen += 1;
            curScreen = curScreen % maxScreens;
        }

        switch (curScreen) {
            case 0:
                drawAllData();
                break;
            case 1:
                sprintf(buff, "light level = %d ", appEnv->data->lightLevel());
                writeOnNextLine(buff);
                sprintf(buff, "moisture = %d", appEnv->data->soilMoisture());
                writeOnNextLine(buff);
                break;
            case 2:
                sprintf(buff, "pressure = %d", appEnv->data->pressure());
                writeOnNextLine(buff);
                // display->drawString(0, 1 * LINE_HEIGHT, buff);

                sprintf(buff, "temperature = %d", appEnv->data->temperature());
                writeOnNextLine(buff);
                break;
            case 3:
                sprintf(buff, "last watered = %d seconds",
                        lastWatered->getDeltaTime() / 1000);
                writeOnNextLine(buff);
                break;
            default:
                break;
        }
    }

    void onWateringNowTrue() { lastWatered->start(); }
    void drawDebug() {
        sprintf(buff, "last watered = %d seconds",
                lastWatered->getDeltaTime() / 1000);
        writeOnNextLine(buff);
    }

    void redraw() {
        display->clear();
        display->setTextAlignment(TEXT_ALIGN_LEFT);
        resetLineNumber();
        // // draw the current demo method
        if (popupScreenDB->running()) {
            // drawPopupScreen();
            Serial.println("alt display");
            drawPopupScreen();

            popupScreenDB->isValidOnce();
        } else {
            drawAlternatingScreens();
            // drawDebug();
        }

        display->setFont(ArialMT_Plain_10);
        display->setTextAlignment(TEXT_ALIGN_RIGHT);
        display->drawString(128, 54, String(millis()));
        // write the buffer to the display
        display->display();
    }

    void loop() { redraw(); }
};

#endif /* OLED_HPP */