
#pragma once
#ifndef AIR_FRESHENER_HPP
#define AIR_FRESHENER_HPP

#include "../AppEnv.hpp"
#include "../Modules/Loopable.hpp"

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