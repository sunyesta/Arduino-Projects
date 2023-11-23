

#ifndef AMUX_HPP
#define AMUX_HPP

#include <Arduino.h>

#include "../AppEnv.hpp"
#include "../Modules/Assert.hpp"
#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"

enum class AMUX_mode { NONE, LDR, SOIL };

class AMUX : public Loopable {
   private:
    Pin outPin, selectPin;
    AMUX_mode mode = AMUX_mode::NONE;
    DebounceTime dt = 1000;
    Debounce *testDebounce = new Debounce(&dt);

   public:
    AMUX(Pin digital_selection, Pin analog_out) : Loopable() {
        this->selectPin = digital_selection;
        this->outPin = analog_out;

        pinMode(selectPin, OUTPUT);
        pinMode(outPin, INPUT);

        set_mode(AMUX_mode::SOIL);
        testDebounce->start();
    }

    void set_mode(AMUX_mode newMode) {
        if (this->mode == newMode) {
            return;
        }

        // Serial.print("mode = ");
        // Serial.println((int)newMode);
        this->mode = newMode;
        if (mode == AMUX_mode::LDR) {
            digitalWrite(this->selectPin, LOW);
        } else if (mode == AMUX_mode::SOIL) {
            digitalWrite(this->selectPin, HIGH);
        } else {
            assert_simple(false, (char *)"not valid mode");
        }
    }

    AMUX_mode getMode() { return mode; }

    int getVal(AMUX_mode newMode) {
        set_mode(newMode);

        return analogRead(outPin);
    }
    void loop() {}
};

#endif /* AMUX_HPP */