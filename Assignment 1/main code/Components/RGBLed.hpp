
#pragma once
#ifndef RGB_LED_HPP
#define RGB_LED_HPP

#include "../AppEnv.hpp"
#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"
#include "../NoErrors.hpp"

class RGBLed {
   private:
    Pin rPin;
    Pin gPin;
    Pin bPin;
    int r, g, b;
    DebounceTime time = 1;

   public:
    RGBLed(Pin PinPWM_red, Pin PinPWM_green, Pin PinPWM_blue);

    void setColor(int r, int g, int b);
    // need to be put in loop

    void setColorToState();
};

RGBLed::RGBLed(Pin PinPWM_red, Pin PinPWM_green, Pin PinPWM_blue) {
    this->rPin = PinPWM_red;
    this->gPin = PinPWM_green;
    this->bPin = PinPWM_blue;

    pinMode(rPin, OUTPUT);
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);
}

void RGBLed::setColor(int r, int g, int b) {
    analogWrite(rPin, r);
    analogWrite(gPin, g);
    analogWrite(bPin, b);

    this->r = r;
    this->g = g;
    this->b = b;
}

void RGBLed::setColorToState() {
    switch (appEnv->data->machineState()) {
        case MachineState::menuInUse:
            setColor(0, 0, 255);  // dark blue
            break;
        case MachineState::notInUse:
            setColor(255, 255, 255);  // white
            break;
        case MachineState::triggeredSprayImminent:
            setColor(255, 0, 0);  // red
            break;
        case MachineState::useCleaning:
            setColor(255, 255, 0);  // yellow
            break;
        case MachineState::useNum1:
            setColor(0, 255, 0);  // green
            break;
        case MachineState::useNum2:
            setColor(255, 0, 255);  // purple
            break;
        case MachineState::useUnknown:
            setColor(255, 115, 0);  // cyan
            break;

        default:
            setColor(100, 0, 0);  // off
            break;
    }
}

#endif /* RGB_LED_HPP */