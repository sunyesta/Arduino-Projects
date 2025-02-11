
#pragma once
#ifndef RESET_SPRAYS_APP
#define RESET_SPRAYS_APP

#include "../Modules/Debounce.hpp";
#include "../Modules/Loopable.hpp";
#include "App.hpp";

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