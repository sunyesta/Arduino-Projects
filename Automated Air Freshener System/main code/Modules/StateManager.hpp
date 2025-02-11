
#pragma once
#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include "../AppEnv.hpp"
#include "../Components/AirFreshener.hpp"
#include "./Debounce.hpp"
#include "./Loopable.hpp"

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