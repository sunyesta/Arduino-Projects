/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.cpp start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/

#ifndef APP_ENV_HPP
#define APP_ENV_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" start --*/

// #ifndef NO_ERRORS_HPP
// #define NO_ERRORS_HPP

// #define uint8_t int

// #define A0 0
// #define A1 0
// #define A2 0
// #define A3 0
// #define A4 0
// #define A5 0
// #define A6 0

// #define NULL 0
// #define OUTPUT 0
// #define INPUT 0
// #define HIGH 0
// #define LOW 0

// #include <iostream>
// using namespace std;

// class SerialObj {
//    public:
//     template <typename T>
//     void println(T txt) {
//         cout << txt << endl;
//     }
//     template <typename T>
//     void print(T txt) {
//         cout << txt;
//     }
//     void begin(int x) {}
// };

// class LiquidCrystal {
//    public:
//     LiquidCrystal(int rs, int e, int db4, int db5, int db6, int db7) {}
//     void begin(int rows, int cols) {}
//     void setCursor(int x, int y) {}
//     void print(char *x);
// };

// int analogRead(int pin) {}
// void delay(int time) {}

// SerialObj Serial;

// void pinMode(uint8_t pin, int type) {}

// void digitalWrite(uint8_t pin, int mode) {}

// int digitalRead(int pin) {}

// int millis() {}

// int main() {}

// int pulseIn(uint8_t pin, int out) {}

// int analogWrite(int pin, int out) {}

// class EEPROM_class {
//    public:
//     int get(int x, int y){};
//     int put(int x, int y){};
// };

// EEPROM_class EEPROM;

// #endif /* NO_ERRORS_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" end --*/

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

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/

#include <EEPROM.h>

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" start --*/

#ifndef APP_HPP
#define APP_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" start --*/

#ifndef ANALOG_BUTTON_HPP
#define ANALOG_BUTTON_HPP

class AnalogButton {
   public:
    AnalogButton() = default;

    void onButtonPressed();
};

#endif /* ANALOG_BUTTON_HPP */

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/Lcd.hpp" start --*/

#ifndef LCD_HPP
#define LCD_HPP

class LiquidCrystal;

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
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
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/Lcd.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" end --*/

class App {
   protected:
    char texts[2][17];
    void fireUpdate();

   public:
    App();

    virtual void activate();
    virtual void deactivate();
    virtual char* toString();
    virtual void onButtonPressed(AnalogButton* btn);
};
// protected
void App::fireUpdate() { appEnv->lcd->update(this, texts); }

// public
App::App() {
    sprintf(texts[0], "sixteen chars==1");
    sprintf(texts[1], "sixteen chars==2");
}

void App::onButtonPressed(AnalogButton* btn) {
    const char buff[] = "button pressed (from App parent class)";
    Serial.println(buff);
}

void App::activate() {
    const char buff[] = "WARNING: parent";
    Serial.println(buff);

    fireUpdate();
}

void App::deactivate() {}

char* App::toString() { return "Default app"; }

#endif /* APP_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/ForceSprayApp.hpp" start --*/

#ifndef FORCE_SPRAY_APP
#define FORCE_SPRAY_APP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AirFreshener.hpp" start --*/

#ifndef AIR_FRESHENER_HPP
#define AIR_FRESHENER_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/

#ifndef LOOPABLE_HPP
#define LOOPABLE_HPP

class LoopManager;

class Loopable {
   public:
    int index;
    Loopable();
    virtual void loop();
};

#endif /* LOOPABLE_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/

class Debounce;

class AirFreshener : public Loopable {
   private:
    Pin outputPin;
    Debounce *sprayTimer;

   public:
    AirFreshener(Pin outputPin);
    void activate();
    void loop();
};

#endif /* AIR_FRESHENER_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AirFreshener.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" start --*/

#ifndef DEBOUNCE_HPP
#define DEBOUNCE_HPP

#define ULONG_MAX 4294967296

#define DebounceTime unsigned long

class Debounce {
   private:
    DebounceTime lastLoggedTime;
    DebounceTime *debounceTime;
    bool running;

   public:
    Debounce(DebounceTime *debounceTime) {
        this->lastLoggedTime = 0;
        this->debounceTime = debounceTime;
        this->running = false;
    }

    // works with millis rollover time
    unsigned long getDeltaTime() {
        if (millis() >= lastLoggedTime) {
            // normal operation
            return millis() - lastLoggedTime;
        } else {
            // millis rollover
            return ULONG_MAX - lastLoggedTime + millis();
        }
    }

    // resets the debounce timer
    void start() {
        running = true;
        lastLoggedTime = millis();
    }

    inline bool isValid() { return running && getDeltaTime() > *debounceTime; }
    bool isValidOnce() {
        if (isValid()) {
            running = false;
            return true;
        }
        return false;
    }
};

#endif /* DEBOUNCE_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" end --*/

class ForceSprayApp : public App, public Loopable {
   private:
    unsigned long debounceTime = 1000;
    Debounce* wait2Secs = new Debounce(&debounceTime);

   public:
    ForceSprayApp() : App(), Loopable() {}

    void activate() {
        // TODO handle no sprays
        if (appEnv->data->spraysRemaining > 0) {
            sprintf(texts[0], "Forcing");
            sprintf(texts[1], "Spray...");
            appEnv->miscComponents->airFreshener->activate();
        } else {
            sprintf(texts[0], "No Sprays!!!");
            sprintf(texts[1], "");
            wait2Secs->start();
        }

        fireUpdate();
    }

    void loop() {
        if (wait2Secs->isValidOnce()) {
            appEnv->funcs->openDefaultApp();
        }
    }

    // this function should only be called by the AirFreshener
    void finishSpray() {
        const char buff[] = "finished spray";
        Serial.println(buff);
        appEnv->funcs->openDefaultApp();
    }

    char* toString() { return "ForceSprayApp"; }
};

#endif /* FORCE_SPRAY_APP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/ForceSprayApp.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/InfoApp.hpp" start --*/

#ifndef INFO_APP_HPP
#define INFO_APP_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AirFreshener.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AirFreshener.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" end --*/

enum Page { PAGE_TEMP_SPRAY, PAGE_MOT_DIS, PAGE_CURSTATE, PAGE_COUNT };

class InfoApp : public App {
   private:
    Page page;  // should only be changed by setPage()
    void setPage(Page page);
    void onButtonPressed(AnalogButton *btn);

   public:
    InfoApp();

    void activate();
    void deactivate();

    // Specific Methods

    void updateTemperature(bool updateScreen);
    void updateSpraysRemaining(bool updateScreen);
    void updateHasMotion(bool updateScreen);
    void updateDistance(bool updateScreen);
    void updateCurState(bool updateScreen);

    char *toString() { return "InfoApp"; }
};

InfoApp::InfoApp() : App() { setPage(PAGE_MOT_DIS); }

void InfoApp::activate() {
    appEnv->data->setMachineState(MachineState::notInUse);
    setPage(this->page);
    fireUpdate();
}
void InfoApp::deactivate() {
    appEnv->data->setMachineState(MachineState::menuInUse);
}

void InfoApp::onButtonPressed(AnalogButton *btn) {
    if (btn == appEnv->btns->selectButton) {
        appEnv->funcs->openSelectionMenu();
    } else if (btn == appEnv->btns->nextButton) {
        Page nextPage = static_cast<Page>((page + 1) % PAGE_COUNT);

        setPage(nextPage);
        fireUpdate();

    } else if (btn == appEnv->btns->manButton) {
        appEnv->lcd->activateApp(appEnv->apps->forceSprayApp);
    }
}

void InfoApp::setPage(Page page) {
    this->page = page;
    updateTemperature(false);
    updateSpraysRemaining(false);
    updateHasMotion(false);
    updateDistance(false);
    updateCurState(false);
}
//

// UPDATES

void InfoApp::updateTemperature(bool updateScreen) {
    if (page == PAGE_TEMP_SPRAY) {
        sprintf(texts[0], "Temp: %dC", appEnv->data->temperature);

        if (updateScreen) {
            fireUpdate();
        }
    }
}

void InfoApp::updateSpraysRemaining(bool updateScreen) {
    if (page == PAGE_TEMP_SPRAY) {
        // if (appEnv->data->spraysRemaining > 0) {
        //     sprintf(texts[1], "sprays rem %d",
        //     appEnv->data->spraysRemaining);
        // } else {
        //     sprintf(texts[1], "no sprays rem");
        // }

        sprintf(texts[1], "sprays rem %d", appEnv->data->spraysRemaining);

        if (updateScreen) {
            fireUpdate();
        }
    }
}

void InfoApp::updateHasMotion(bool updateScreen) {
    if (page == PAGE_MOT_DIS) {
        char hasMotion = (appEnv->data->hasMotion ? 'X' : '-');

        sprintf(texts[0], "Has Motion = %c", hasMotion);
        if (updateScreen) {
            fireUpdate();
        }
    }
}

void InfoApp::updateDistance(bool updateScreen) {
    if (page == PAGE_MOT_DIS) {
        sprintf(texts[1], "Distance = %d", appEnv->data->distance);
        if (updateScreen) {
            fireUpdate();
        }
    }
}

void InfoApp::updateCurState(bool updateScreen) {
    if (page == PAGE_CURSTATE) {
        char *curState;
        switch (appEnv->data->machineState()) {
            case MachineState::menuInUse:
                curState = "menuInUse";
                break;
            case MachineState::notInUse:
                curState = "notInUse";
                break;
            case MachineState::triggeredSprayImminent:
                curState = "trigSprayImnent";
                break;
            case MachineState::useCleaning:
                curState = "useCleaning";
                break;
            case MachineState::useNum1:
                curState = "useNum1";
                break;
            case MachineState::useNum2:
                curState = "useNum2";
                break;
            case MachineState::useUnknown:
                curState = "useUnknown";
                break;
            case MachineState::isOpen:
                curState = "Open";
                break;
            default:
                curState = "ERROR STATE";
                break;
        }
        sprintf(texts[0], "cur state is");
        sprintf(texts[1], curState);

        if (updateScreen) {
            fireUpdate();
        }
    }
}

#endif /* INFO_APP_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/InfoApp.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/MainMenuApp.hpp" start --*/

#ifndef MAIN_MENU_APP_HPP
#define MAIN_MENU_APP_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" end --*/

class MainMenuApp : public App {
   private:
    class Option {
       public:
        char text[100];
        void (*callback)();

        Option(char *text, void (*callbackFunc)()) {
            sprintf(this->text, "%s", text);

            this->callback = callback;
        }

        void select() {}
    };

    int itemIndex = 0;
    static const int optionCount = 4;
    char options[4][12];

    void displayMenuItem(char *op);

   public:
    MainMenuApp();
    void activate();
    void onButtonPressed(AnalogButton *btn);
    void triggerSelection(int selectionIndex);
    char *toString() { return "MainMenuApp"; }
};

MainMenuApp::MainMenuApp() : App() {
    sprintf(options[0], "info app");
    sprintf(options[1], "spray mode");
    sprintf(options[2], "spray");
    sprintf(options[3], "reset");
}

void MainMenuApp::displayMenuItem(char *op) { sprintf(texts[0], "%s", op); };

void MainMenuApp ::activate() {
    itemIndex = 0;
    displayMenuItem(options[itemIndex]);
    sprintf(texts[1], "<- scroll ->");
    fireUpdate();
}

void MainMenuApp::triggerSelection(int selectionIndex) {
    if (selectionIndex == 0) {
        appEnv->lcd->activateApp(appEnv->apps->infoApp);
    } else if (selectionIndex == 1) {
        appEnv->lcd->activateApp(appEnv->apps->sprayConfigApp);
    } else if (selectionIndex == 2) {
        appEnv->lcd->activateApp(appEnv->apps->forceSprayApp);
    } else if (selectionIndex == 3) {
        appEnv->lcd->activateApp(appEnv->apps->resetSpraysApp);
    }
}

void MainMenuApp ::onButtonPressed(AnalogButton *btn) {
    if (btn == appEnv->btns->nextButton) {
        itemIndex += 1;
        itemIndex = itemIndex % optionCount;
        displayMenuItem(options[itemIndex]);
        fireUpdate();
    } else if (btn == appEnv->btns->selectButton) {
        triggerSelection(itemIndex);
        // TODO turn this callback into a function that is
        // hard codes with if statements for each button
    }
}

#endif /* MAIN_MENU_APP_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/MainMenuApp.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/ResetSpraysApp.hpp" start --*/

#ifndef RESET_SPRAYS_APP
#define RESET_SPRAYS_APP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" end --*/

class ResetSpraysApp : public App, public Loopable {
   private:
    unsigned long debounceTime = 1000;
    Debounce *wait2Secs = new Debounce(&debounceTime);

   public:
    ResetSpraysApp() : App(), Loopable() {}

    void activate() {
        sprintf(texts[0], "Resetting");
        sprintf(texts[1], "Sprays...");
        fireUpdate();
        appEnv->funcs->setSpraysRemaining(appEnv->config->defaultSprayCount);
        wait2Secs->start();
    }

    void loop() {
        if (wait2Secs->isValidOnce()) {
            appEnv->funcs->openDefaultApp();
        }
    }

    char *toString() { return "ResetSpraysApp"; }
};

#endif /* RESET_SPRAYS_APP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/ResetSpraysApp.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/SprayConfigApp.hpp" start --*/


#ifndef SPRAY_CONFIG_APP_HPP
#define SPRAY_CONFIG_APP_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Assert.hpp" start --*/


#ifndef ASSERT_HPP
#define ASSERT_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" end --*/

void printErr() { Serial.print("ERROR: "); }

void assert_simple(bool val, char *message) {
    if (!val) {
        printErr();
        Serial.println(message);
        delay(100);
        exit(-1);
    }
}

void assert_str(bool val, char *message, char *actual) {
    if (!val) {
        printErr();
        Serial.println(message);
        Serial.print("actual: ");
        Serial.println(actual);
        delay(100);
        exit(-1);
    }
}

// template <typename T>
// void assert_val(bool val, char *message, T actual) {
//     if (!val) {
//         printErr();
//         Serial.println(message);
//         Serial.print("actual: ");
//         Serial.println(actual);
//         delay(100);
//         exit(-1);
//     }
// }

void assert_int(bool val, char *message, int actual) {
    if (!val) {
        printErr();
        Serial.println(message);
        Serial.print("actual: ");
        Serial.println(actual);
        delay(100);
        exit(-1);
    }
}

#endif /* ASSERT_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Assert.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" end --*/

class SprayConfigApp : public App {
   private:
    int level;  // btwn 1 and 5
    const static int maxLevel = 5;
    void setLevel(int level);

   public:
    SprayConfigApp();
    void onButtonPressed(AnalogButton *btn);
    void activate();
    char *toString() { return "SprayConfigApp"; }
};

void SprayConfigApp::setLevel(int level) {
    assert_simple(level >= 1 && level <= maxLevel,
                  "level must be btwn 1 and maxLevel");
    // data setting
    this->level = level;
    appEnv->data->sprayDelay = (unsigned long)(20000 + this->level * 1000);

    // text setting
    char levelTxt[level + 1];
    for (int i = 1; i <= level; i++) {
        levelTxt[i - 1] = 'X';
    }
    levelTxt[level] = '\0';
    sprintf(texts[0], "%s", levelTxt);
}

SprayConfigApp ::SprayConfigApp() : App() {
    level = 1;
    sprintf(texts[0], "");
    sprintf(texts[1], "spray delay");

    setLevel(level);
}

void SprayConfigApp::activate() { fireUpdate(); }

void SprayConfigApp ::onButtonPressed(AnalogButton *btn) {
    if (btn == appEnv->btns->nextButton) {
        int nextLevel = level + 1;
        nextLevel = ((nextLevel - 1) % maxLevel) + 1;
        setLevel(nextLevel);
        fireUpdate();
    } else if (btn == appEnv->btns->selectButton) {
        appEnv->funcs->openDefaultApp();
    }
}

#endif /* SPRAY_CONFIG_APP_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/SprayConfigApp.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/isOpenApp.hpp" start --*/

#ifndef IS_OPEN_APP_HPP
#define IS_OPEN_APP_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" end --*/

class IsOpenApp : public App {
   public:
    IsOpenApp() : App() {}

    void activate() {
        sprintf(texts[0], "Machine is");
        sprintf(texts[1], "Open");
        fireUpdate();
    }

    char *toString() { return "IsOpenApp"; }
};

#endif /* IS_OPEN_APP_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/isOpenApp.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AirFreshener.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AirFreshener.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/DistanceSensor.hpp" start --*/

#ifndef DISTANCE_SENSOR_HPP
#define DISTANCE_SENSOR_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/InfoApp.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/InfoApp.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/

class DistanceSensor : Loopable {
   private:
    int distance_cm = -1;
    Pin echoPin, trigPin;
    unsigned long secs2 = 2, secs10 = 10, debounceTime = 1000;
    Debounce *wait2 = new Debounce(&secs2), *wait10 = new Debounce(&secs10),
             *debounce = new Debounce(&debounceTime);
    bool looped = true;

   public:
    DistanceSensor(Pin echoPin, Pin trigPin);

    void loop();
};

// public
DistanceSensor::DistanceSensor(Pin echoPin, Pin trigPin) : Loopable() {
    this->echoPin = echoPin;
    this->trigPin = trigPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    debounce->start();
}

void DistanceSensor::loop() {
    if (appEnv->funcs->isSensorsOn()) {
        if (debounce->isValidOnce()) {
            digitalWrite(trigPin, LOW);
            wait2->start();
        } else if (wait2->isValidOnce()) {
            digitalWrite(trigPin, HIGH);
            wait10->start();
        } else if (wait10->isValidOnce()) {
            digitalWrite(trigPin, LOW);

            long duration = pulseIn(echoPin, HIGH);

            distance_cm = duration * 0.034 / 2;
            appEnv->data->distance = distance_cm;
            appEnv->apps->infoApp->updateDistance(true);
            debounce->start();
        }
    } else {
        debounce->start();  // restarts debounce sequence;
    }

    // SLOW WAY
    //  digitalWrite(trigPin, LOW);
    //  delayMicroseconds(2);
    //  digitalWrite(trigPin, HIGH);
    //  delayMicroseconds(10);
    //  digitalWrite(trigPin, LOW);

    // long duration = pulseIn(echoPin, HIGH);
    // distance_cm = duration * 0.034 / 2;
    // appEnv->data->distance = distance_cm;
    // Serial.println(distance_cm);
    // appEnv->apps->infoApp->updateDistance(true);
    // END SLOW WAY
}
// private

#endif /* DISTANCE_SENSOR_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/DistanceSensor.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/Lcd.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/Lcd.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/MagnetSwitch.hpp" start --*/

#ifndef MAGNET_SWITCH_HPP
#define MAGNET_SWITCH_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/

class MagnetSwitch : public Loopable {
   private:
    MachineState lastState = MachineState::triggeredSprayImminent;
    Pin inputPin;
    DebounceTime time = 1000;
    Debounce *deb = new Debounce(&time);
    bool ready = true;

   public:
    MagnetSwitch(Pin inputPin);

    void loop();
};

#endif /* MAGNET_SWITCH_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/MagnetSwitch.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/MotionSensor.hpp" start --*/

#ifndef MOTION_SENSOR_HPP
#define MOTION_SENSOR_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/InfoApp.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/InfoApp.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/

class MotionSensor : public Loopable {
   private:
   public:
    Pin pin;
    MotionSensor(Pin pin);

    void loop();

    void updateMotion();
};

#endif /* MOTION_SENSOR_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/MotionSensor.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/RGBLed.hpp" start --*/

#ifndef RGB_LED_HPP
#define RGB_LED_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" end --*/

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
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/RGBLed.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/TemperatureSensor.hpp" start --*/

#ifndef TEMPERATURE_SENSO_HPP
#define TEMPERATURE_SENSO_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/InfoApp.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/InfoApp.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/

class TemperatureSensor : public Loopable {
   private:
    Pin pin;
    unsigned long milisec = 2000;
    Debounce* debounce = new Debounce(&milisec);

   public:
    TemperatureSensor(Pin analogPin) : Loopable() {
        // Serial.println("testingaaaaaaaaaaaaaaaaaaaaaaaaa");
        this->pin = analogPin;
        debounce->start();
    }
    void loop() {
        if (appEnv->funcs->isSensorsOn() && debounce->isValidOnce()) {
            int temperature = analogRead(pin);
            float celcius = (float)temperature / 1023 / 7;
            celcius = celcius * 5;
            celcius = celcius - 0.5;
            celcius = celcius * 100;

            appEnv->data->temperature = celcius;
            appEnv->apps->infoApp->updateTemperature(true);
            debounce->start();
        }
    }
};

#endif /* TEMPERATURE_SENSO_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/TemperatureSensor.hpp" end --*/

#define EEPROM_DEFAULT 0

// We use 5000 because it is impossible for spraysRemaining to = 5000
#define EEPROM_OFFSET 5000

// LCD display
// const Pin LCD_RS = 11, LCD_E = 12, LCD_DB4 = 4, LCD_DB5 = A5, LCD_DB6 = 13,
//   LCD_DB7 = 7;

// NEW LCD
const int rs = 2, en = 4, d4 = 7, d5 = 8, d6 = 12, d7 = 13;

const int spraysRemainingEEPROM = 0;

AppEnv::Data::Data() {
    activeApp = NULL;
    defaultApp = NULL;
    setMachineState(MachineState::notInUse);
    hasMotion = false;
    distance = -1;

    // // spraysRemaining from EEPROM
    // spraysRemaining = EEPROM.get(spraysRemainingEEPROM, spraysRemaining);
    // if (spraysRemaining == EEPROM_DEFAULT) {
    //     spraysRemaining = appEnv->config->defaultSprayCount;
    //     EEPROM.put(spraysRemainingEEPROM, spraysRemaining + EEPROM_OFFSET);
    // } else {
    //     spraysRemaining -= EEPROM_OFFSET;
    // }
    spraysRemaining = 2400;
    temperature = -1;
    sprayDelay = 1000;
}
MachineState AppEnv::Data::machineState() { return _machineState; }

void AppEnv::Data::setMachineState(MachineState machineState) {
    this->_machineState = machineState;
    appEnv->miscComponents->rgbLed->setColorToState();
    if (appEnv->data->activeApp == appEnv->apps->infoApp) {
        appEnv->apps->infoApp->updateCurState(true);
    }
}

AppEnv ::Apps::Apps() {
    this->infoApp = new InfoApp();
    this->mainMenuApp = new MainMenuApp();
    this->sprayConfigApp = new SprayConfigApp();
    this->forceSprayApp = new ForceSprayApp();
    this->resetSpraysApp = new ResetSpraysApp();
    this->isOpenApp = new IsOpenApp();
}

AppEnv ::Btns::Btns() {
    this->selectButton = new AnalogButton();
    this->nextButton = new AnalogButton();
}

AppEnv ::MiscComponents::MiscComponents() {
    this->airFreshener = new AirFreshener(11);
    this->temperatureSensor = new TemperatureSensor(A2);
    this->distanceSensor = new DistanceSensor(9, 10);
    this->motionSensor = new MotionSensor(A1);
    this->rgbLed = new RGBLed(3, 6, 5);
    this->magnetSwitch = new MagnetSwitch(A3);  // put the pin back in
    // place
}

AppEnv ::Funcs::Funcs() {}

void AppEnv ::Funcs::openSelectionMenu() {
    appEnv->lcd->activateApp(appEnv->apps->mainMenuApp);
}

void AppEnv ::Funcs::openDefaultApp() {
    appEnv->lcd->activateApp(appEnv->data->defaultApp);
}

bool AppEnv ::Funcs::isSensorsOn() {
    return appEnv->data->machineState() == MachineState::notInUse ||
           appEnv->data->machineState() == MachineState::useUnknown;
    // return true;
}

void AppEnv::Funcs::setMotion(bool hasMotion) {
    appEnv->data->hasMotion = hasMotion;
}

void AppEnv::Funcs::setSpraysRemaining(int spraysRemaining) {
    appEnv->data->spraysRemaining = spraysRemaining;
    EEPROM.put(spraysRemainingEEPROM, spraysRemaining + EEPROM_OFFSET);
}

AppEnv::AppEnv() {}

void AppEnv ::setup() {
    this->lcd = new Lcd(rs, en, d4, d5, d6, d7);
    this->config = new Config();
    this->data = new Data();
    this->apps = new Apps();
    this->btns = new Btns();
    this->miscComponents = new MiscComponents();
    this->funcs = new Funcs();

    this->data->defaultApp = this->apps->infoApp;
}

/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.cpp end --*/
/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AirFreshener.cpp start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AirFreshener.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AirFreshener.hpp" end --*/

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/ForceSprayApp.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/ForceSprayApp.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" end --*/

AirFreshener::AirFreshener(Pin outputPin) : Loopable() {
    this->outputPin = outputPin;
    pinMode(this->outputPin, OUTPUT);
    this->sprayTimer = new Debounce(
        &(appEnv->data->sprayDelay));  // TODO make debounce work with addresses
                                       //  instead of direct references to int
}
void AirFreshener::activate() {
    appEnv->data->setMachineState(MachineState::triggeredSprayImminent);
    appEnv->funcs->setSpraysRemaining(appEnv->data->spraysRemaining - 1);
    digitalWrite(outputPin, HIGH);

    sprayTimer->start();
}

void AirFreshener::loop() {
    if (sprayTimer->isValidOnce()) {
        digitalWrite(outputPin, LOW);
        appEnv->data->setMachineState(MachineState::notInUse);
        if (appEnv->data->activeApp == appEnv->apps->forceSprayApp) {
            appEnv->apps->forceSprayApp->finishSpray();
        }
    }
}
/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AirFreshener.cpp end --*/
/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.cpp start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" end --*/

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" end --*/

void AnalogButton::onButtonPressed() {
    if (appEnv->data->activeApp) {
        appEnv->data->activeApp->onButtonPressed(this);
    }
}

/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.cpp end --*/
/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/Lcd.cpp start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/Lcd.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/Lcd.hpp" end --*/

#include <LiquidCrystal.h>

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/App.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Assert.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Assert.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" end --*/

Lcd ::Lcd(Pin rs, Pin e, Pin db4, Pin db5, Pin db6, Pin db7) {
    this->lcd = new LiquidCrystal(rs, e, db4, db5, db6, db7);
    this->lcd->begin(lcdRows, lcdCols);
}

void Lcd ::setLineText(int line, char* text, bool centered) {
    assert_str(strlen(text) <= lcdCols, "text must be correct length", text);
    lcd->setCursor(0, line);

    char finalTxt[20];
    if (centered) {
        int spaces = (16 - strlen(text)) / 2;
        char* spacesTxt = "            ";
        spacesTxt[spaces] = '\0';

        sprintf(finalTxt, "%s%s%s", spacesTxt, text, spacesTxt);
        sprintf(finalTxt, "%-16s", finalTxt);
        spacesTxt[spaces] = ' ';
    } else {
        sprintf(finalTxt, "%-16s", text);
    }

    lcd->print(finalTxt);
}
void Lcd ::setText(char texts[2][17]) {
    assert_simple(texts, "must have text");
    setLineText(0, texts[0], false);
    setLineText(1, texts[1], false);
}

// TODO find error in this function
template <typename T_App>
void Lcd ::update(T_App* app, char texts[2][17]) {
    // Serial.println("updating lcd");
    if (appEnv->data->activeApp == app) {
        setText(texts);
    } else {
        Serial.print("WARNING: not activeApp trying to update LCD = ");
        char* str = app->toString();
        Serial.println(str);
    }
}

template <typename T_App>
void Lcd ::activateApp(T_App* app) {
    if (appEnv->data->activeApp) {
        appEnv->data->activeApp->deactivate();
    }

    appEnv->data->activeApp = app;
    app->activate();
}
/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/Lcd.cpp end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/LiquidCrystal.h" start --*/

/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/MagnetSwitch.cpp start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/MagnetSwitch.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/MagnetSwitch.hpp" end --*/

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/

MagnetSwitch::MagnetSwitch(Pin inputPin) : Loopable() {
    // const char buff[] = "created magnet switch";
    // Serial.println(buff);

    this->inputPin = inputPin;
    pinMode(inputPin, INPUT);
    deb->start();
}

void MagnetSwitch::loop() {
    int buttonState = digitalRead(inputPin);
    // Serial.println(buttonState);
    if (buttonState == HIGH && !ready) {
        // const char buff[] = "magnet switch stopped!!";
        // Serial.println(buff);
        appEnv->data->setMachineState(lastState);
        appEnv->lcd->activateApp(appEnv->apps->infoApp);
        ready = true;
    } else if (buttonState == LOW && ready) {
        // const char buff[] = "magnet switch triggered!";
        // Serial.println(buff);
        lastState = appEnv->data->machineState();
        appEnv->data->setMachineState(MachineState::isOpen);
        appEnv->lcd->activateApp(appEnv->apps->isOpenApp);
        ready = false;
    }
}

/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/MagnetSwitch.cpp end --*/
/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/MotionSensor.cpp start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/MotionSensor.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/MotionSensor.hpp" end --*/

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/

// TODO: fix data leak!
// static void MotionSensor_toggleMotion() {
//     appEnv->data->hasMotion = (appEnv->data->hasMotion) ? false : true;
//     if (appEnv->data->activeApp == appEnv->apps->infoApp) {
//         appEnv->apps->infoApp->updateHasMotion(true);
//     }
// }

MotionSensor::MotionSensor(Pin pin) : Loopable() {
    this->pin = pin;
    pinMode(pin, INPUT);
    // attachInterrupt(digitalPinToInterrupt(pin), MotionSensor_toggleMotion,
    //                 CHANGE);
}

void MotionSensor::loop() {
    if (appEnv->funcs->isSensorsOn()) {
        updateMotion();
    }
}

void MotionSensor::updateMotion() {
    int motionData = digitalRead(pin);
    if (motionData == 1) {
        appEnv->data->hasMotion = true;
    } else {
        appEnv->data->hasMotion = false;
    }
    if (appEnv->data->activeApp == appEnv->apps->infoApp) {
        appEnv->apps->infoApp->updateHasMotion(true);
    }
}
/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/MotionSensor.cpp end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/EEPROM.h" start --*/

/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.cpp start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/LoopManager.hpp" start --*/

#ifndef LOOP_MANAGER_HPP
#define LOOP_MANAGER_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Assert.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Assert.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/

class Loopable;

class LoopManager {
   private:
    static const int maxLoopable = 20;
    int loopableCount = 0;
    Loopable *loopables[maxLoopable];

   public:
    LoopManager();
    int connect(Loopable *loopable);
    void loop();
};

LoopManager::LoopManager() {}

int LoopManager::connect(Loopable *loopable) {
    assert_int(this->loopableCount < maxLoopable,
               "cur loopables must be below max loopable", maxLoopable);
    int index = loopableCount;
    this->loopableCount += 1;
    loopables[index] = loopable;

    // Serial.print("created loopable at:");
    // Serial.println(index);
    // Serial.print("size of arr: ");
    // Serial.println(loopableCount);
    return index;
}
void LoopManager::loop() {
    for (int i = 0; i < loopableCount; i++) {
        loopables[i]->loop();
    }
}

LoopManager *loopManager = new LoopManager();

#endif /* LOOP_MANAGER_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/LoopManager.hpp" end --*/

Loopable::Loopable() { index = loopManager->connect(this); }

void Loopable::loop() {
    const char buff[] = "default loop function";
    Serial.println(buff);
}
/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.cpp end --*/
/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/main.cpp start --*/

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/MainMenuApp.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Apps/MainMenuApp.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogBtnSet.hpp" start --*/

#ifndef ANALOG_BTN_SET_HPP
#define ANALOG_BTN_SET_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Assert.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Assert.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" end --*/

// note: all analog buttons connected to the same pin must also have the same
// resistorOhms
class AnalogBtnSet : public Loopable {
   private:
    DebounceTime dt = 100;
    Debounce* debounceTemp = new Debounce(&dt);
    Pin pin;
    static const int btnCount = 3;
    int startingVolts;
    int resistorKOhms;
    bool ready = true;
    DebounceTime debounceTime = 300;
    Debounce* debounce = new Debounce(&debounceTime);
    AnalogButton* btns[btnCount];  // WARNING: button count has been hardcoded

    int getMaxVoltage(const int btnNum);
    int getMinVoltage(const int btnNum);

    void triggerButton(AnalogButton* btn);

   public:
    AnalogBtnSet(AnalogButton* btns[], int btnCount, Pin analogPin,
                 const int startingVolts, const int resistorKOhms);

    void loop();
};

// private:
int AnalogBtnSet::getMaxVoltage(const int btnNum) {
    int resistorsBfrBtn = btnNum + 1;
    return (startingVolts * 100) - (resistorsBfrBtn * resistorKOhms * 100) +
           resistorKOhms * 100;
}

int AnalogBtnSet::getMinVoltage(const int btnNum) {
    return getMaxVoltage(btnNum) - 100;
}

void AnalogBtnSet::triggerButton(AnalogButton* btn) {
    if (ready) {
        btn->onButtonPressed();
        ready = false;
    }
}

// public:
AnalogBtnSet::AnalogBtnSet(AnalogButton* btns[], int btnCount, Pin analogPin,
                           const int startingVolts, const int resistorKOhms)
    : Loopable() {
    assert_int(this->btnCount == btnCount,
               "button count must be same as hard code", btnCount);
    this->pin = analogPin;
    this->startingVolts = startingVolts;
    this->resistorKOhms = resistorKOhms;
    for (int i = 0; i < btnCount; i++) {
        this->btns[i] = btns[i];
    }
    debounceTemp->start();
}

void AnalogBtnSet::loop() {
    int voltageInput = analogRead(this->pin);
    // Serial.println(voltageInput);
    if (debounceTemp->isValidOnce()) {
        char buff[50];
        sprintf(buff, "%d", voltageInput);
        Serial.println(buff);
        debounce->start();
    }

    // no button pressed
    if (voltageInput < 100) {
        ready = true;
        return;
    }
    // btn that isn't 1st btn is pressed
    // for (int i = this->btnCount - 1; i >= 1; i--) {
    //     if (voltageInput < getMaxVoltage(i)) {
    //         triggerButton(this->btns[i]);
    //         return;
    //     }
    // }

    if (voltageInput > 500 && voltageInput < 600) {
        triggerButton(this->btns[0]);
        return;
    }
    if (voltageInput > 300 && voltageInput < 400) {
        triggerButton(this->btns[1]);
        return;
    }
    if (voltageInput > 200 && voltageInput < 300) {
        triggerButton(this->btns[2]);
        return;
    }
    triggerButton(this->btns[0]);
}

#endif /* ANALOG_BTN_SET_HPP */

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogBtnSet.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AnalogButton.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/Lcd.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/Lcd.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/LoopManager.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/LoopManager.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/StateManager.hpp" start --*/

#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AirFreshener.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Components/AirFreshener.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Debounce.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/Loopable.hpp" end --*/

class StateManager : public Loopable {
   public:
    DebounceTime time = 5000;
    DebounceTime time2 = 10000;
    DebounceTime time3 = appEnv->data->sprayDelay + 1000;
    Debounce *peeTimer = new Debounce(&time), *poopTimer = new Debounce(&time2),
             *restartTimer = new Debounce(&time3);
    StateManager() : Loopable() { peeTimer->start(); }

    void loop() {
        time3 = appEnv->data->sprayDelay + 1000;
        if (appEnv->data->distance < 10) {
            peeTimer->start();
            poopTimer->start();
            Serial.println("restarted timer");
        }
        if (peeTimer->isValidOnce() &&
            appEnv->data->machineState() !=
                MachineState::triggeredSprayImminent &&
            appEnv->data->distance > 10 && !poopTimer->isValid()) {
            appEnv->miscComponents->airFreshener->activate();
        }

        if (poopTimer->isValidOnce() &&
            appEnv->data->machineState() !=
                MachineState::triggeredSprayImminent &&
            appEnv->data->distance > 10) {
            appEnv->miscComponents->airFreshener->activate();
            restartTimer->start();
        }
        if (restartTimer->isValidOnce()) {
            appEnv->miscComponents->airFreshener->activate();
        }
    }
};

#endif /* STATE_MANAGER_HPP */
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/Modules/StateManager.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/AppEnv.hpp" end --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" start --*/
/*-- #include "/Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/NoErrors.hpp" end --*/

AnalogBtnSet *analogBtnSet;

void setup() {
    Serial.begin(9600);
    appEnv = new AppEnv();
    StateManager *stateManager = new StateManager();
    char buff[50];
    sprintf(buff, "created app env at: %p", appEnv);
    Serial.println(buff);

    appEnv->setup();

    // loopManager = new LoopManager();
    AnalogButton *btns[] = {appEnv->btns->selectButton,
                            appEnv->btns->nextButton, appEnv->btns->manButton};
    analogBtnSet = new AnalogBtnSet(btns, 3, A0, 5, 10);

    appEnv->lcd->activateApp(appEnv->apps->infoApp);
}

void loop() {
    // analogBtnSet->loop();
    loopManager->loop();
    // Serial.println("got here");
    // delay(200);
}

/*-- File: /Users/mary/Documents/School/Interactive Tech/Asignment 1/main code/main.cpp end --*/
