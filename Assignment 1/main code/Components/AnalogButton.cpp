#include "./AnalogButton.hpp"

#include "../AppEnv.hpp"
#include "../Apps/App.hpp"

void AnalogButton::onButtonPressed() {
    if (appEnv->data->activeApp) {
        appEnv->data->activeApp->onButtonPressed(this);
    }
}
