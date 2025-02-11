#include "./MagnetSwitch.hpp"

#include "../AppEnv.hpp"
#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"

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
