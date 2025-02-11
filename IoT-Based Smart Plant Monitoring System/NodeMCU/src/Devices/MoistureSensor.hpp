

#ifndef MOISTURE_SENSOR_HPP
#define MOISTURE_SENSOR_HPP

#include "../AppEnv.hpp"
#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"
#include "./AMUX.hpp"
#include "./MyServo.hpp"

class MoistureSensor : public Loopable {
   private:
    AMUX *amux;
    AMUX_mode amux_mode;
    DebounceTime dt = 2000;
    Debounce *debounce = new Debounce(&dt);
    const int lowestWetness = 20;
    int _moisture;

   public:
    MoistureSensor(AMUX *amux, AMUX_mode amux_mode) : Loopable() {
        this->amux = amux;
        this->amux_mode = amux_mode;
        debounce->start();
    }

    void loop() {
        if (debounce->isValidRestart()) {
            update();
        }
    }
    void update() { appEnv->data->setSoilMoisture(amux->getVal(amux_mode)); }

    int moisture() { return _moisture; }
};

#endif /* MOISTURE_SENSOR_HPP */