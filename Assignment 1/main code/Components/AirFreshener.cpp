#include "AirFreshener.hpp"

#include "../AppEnv.hpp"
#include "../Apps/ForceSprayApp.hpp"
#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"
#include "../NoErrors.hpp"

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