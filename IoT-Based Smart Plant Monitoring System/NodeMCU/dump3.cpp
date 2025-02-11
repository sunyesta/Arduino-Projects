

#ifndef SERVO_HPP
#define SERVO_HPP

#include <Servo.h>

#include "../AppEnv.hpp"
#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"

class MyServo : public Loopable {
   private:
    Pin outputPin;
    Servo *servo;
    DebounceTime dt = 1000;
    Debounce *deb = new Debounce(&dt);
    Debounce *dipDebounce = new Debounce(3000);
    bool val = false;

   public:
    MyServo(Pin digitalPin) : Loopable() {
        //
        this->outputPin = digitalPin;
        this->servo = new Servo();
        this->servo->attach(this->outputPin);
        dipInWater();

        deb->start();
    }

    void loop() {
        if (dipDebounce->isValidOnce()) {
            appEnv->data->setWateringNow(true);
            this->servo->write(180);
        } else {
            this->servo->write(0);
        }
    }

    void dipInWater() {
        // Serial.println(dipping);
        dipDebounce->start();
    }

    void onNewMoistureLevel(int moistureLevel) {
        if (moistureLevel > 20) {
            dipInWater();
        }
    }
};

#endif /* SERVO_HPP */