
#include "./Apps/MainMenuApp.hpp"
#include "./Components/AnalogBtnSet.hpp"
#include "./Components/AnalogButton.hpp"
#include "./Components/Lcd.hpp"
#include "./Modules/LoopManager.hpp"
#include "./Modules/StateManager.hpp"
#include "AppEnv.hpp"
#include "NoErrors.hpp"

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
