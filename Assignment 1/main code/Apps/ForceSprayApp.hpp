
#pragma once
#ifndef FORCE_SPRAY_APP
#define FORCE_SPRAY_APP

#include "../Components/AirFreshener.hpp"
#include "../Modules/Debounce.hpp";
#include "../Modules/Loopable.hpp";
#include "App.hpp";

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