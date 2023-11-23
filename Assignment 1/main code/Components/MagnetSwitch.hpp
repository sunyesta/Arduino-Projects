
#pragma once
#ifndef MAGNET_SWITCH_HPP
#define MAGNET_SWITCH_HPP

#include "../AppEnv.hpp"
#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"

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