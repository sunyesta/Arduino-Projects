#include <Arduino.h>

#ifndef LIGHT_SENSOR_HPP
#define LIGHT_SENSOR_HPP

#include "../AppEnv.hpp"
#include "../Modules/Loopable.hpp"
#include "./AMUX.hpp"

class LightSensor : public Loopable {
   private:
    AMUX *amux;
    AMUX_mode amux_mode;
    DebounceTime dt = 2000;
    Debounce *debounce = new Debounce(&dt);
    int _lightness = -1;

   public:
    LightSensor(AMUX *amux, AMUX_mode amux_mode) : Loopable() {
        this->amux = amux;
        this->amux_mode = amux_mode;
        debounce->start();
    }

    void loop() {
        if (debounce->isValidRestart()) {
            update();
        }
    }
    int lightness() { return _lightness; }

    void update() { appEnv->data->setLightLevel(amux->getVal(amux_mode)); }
};

#endif /* LIGHT_SENSOR_HPP */