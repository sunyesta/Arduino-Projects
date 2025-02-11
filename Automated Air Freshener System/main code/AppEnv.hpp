
#pragma once
#ifndef APP_ENV_HPP
#define APP_ENV_HPP

#include "NoErrors.hpp"

#define Pin uint8_t

class AirFreshener;
class AnalogButton;
class App;
class AppEnv;
class DistanceSensor;
class ForceSprayApp;
class InfoApp;
class Lcd;
class MainMenuApp;
class MotionSensor;
class ResetSpraysApp;
class RGBLed;
class SprayConfigApp;
class TemperatureSensor;
class MagnetSwitch;
class IsOpenApp;

enum class MachineState {
    isOpen,
    notInUse,
    menuInUse,
    useUnknown,
    useNum1,
    useNum2,
    useCleaning,
    triggeredSprayImminent
};

class AppEnv {
   public:
    class Config {
       public:
        static const int defaultSprayCount = 2400;
        static const int lcdRows = 2;

        // remember to add 1 for the null terminator if
        // creating an array of exact size
        static const int lcdCols = 16;
    };
    class Data {
       private:
        MachineState _machineState;

       public:
        Data();
        App *activeApp;
        App *defaultApp;

        int distance;
        int spraysRemaining;
        int temperature;
        unsigned long sprayDelay;

        // modified by interrupts
        bool hasMotion;
        bool magnetSwitchTriggered;

        MachineState machineState();
        void setMachineState(MachineState machineState);
    };

    class Apps {
       public:
        Apps();
        InfoApp *infoApp;
        MainMenuApp *mainMenuApp;
        SprayConfigApp *sprayConfigApp;
        ForceSprayApp *forceSprayApp;
        ResetSpraysApp *resetSpraysApp;
        IsOpenApp *isOpenApp;
    };

    class MiscComponents {
       public:
        MiscComponents();
        AirFreshener *airFreshener;
        TemperatureSensor *temperatureSensor;
        DistanceSensor *distanceSensor;
        MotionSensor *motionSensor;
        RGBLed *rgbLed;
        MagnetSwitch *magnetSwitch;
    };

    class Btns {
       public:
        Btns();
        AnalogButton *nextButton;
        AnalogButton *selectButton;
        AnalogButton *manButton;
    };

    class Funcs {
       public:
        Funcs();
        void openSelectionMenu();
        void openDefaultApp();
        void setMotion(bool hasMotion);
        void setSpraysRemaining(int spraysRemaining);
        bool isSensorsOn();
    };

    AppEnv();

    // setup function allows apps to reference the appEnv pointer
    // on the heap because AppEnv only gets stored onto the heap after the
    // contructor is finished
    void setup();

    Lcd *lcd;
    Config *config;
    Data *data;
    Apps *apps;
    Btns *btns;
    MiscComponents *miscComponents;
    Funcs *funcs;
};

AppEnv *appEnv;

#endif /* APP_ENV_HPP */
