

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

    void endWateringNow() {
        appEnv->data->setWateringNow(false);
        this->servo->write(0);
    }

   public:
    MyServo(Pin digitalPin) : Loopable() {
        //
        this->outputPin = digitalPin;
        this->servo = new Servo();
        this->servo->attach(this->outputPin);
        this->servo->write(0);
        deb->start();

        pinMode(D3, INPUT);
    }

    void loop() {
        if (dipDebounce->isValidOnce()) {
            endWateringNow();
        }

        int buttonState = digitalRead(D3);
        if (buttonState == LOW) {
            appEnv->data->setWateringNow(true);
        }
    }

    void onWateringNowTrue() {
        dipDebounce->start();
        this->servo->write(100);
    }

    void onNewMoistureLevel(int moistureLevel) {
        if (moistureLevel > 40) {
            appEnv->data->setWateringNow(true);
        }
    }
};

#endif /* SERVO_HPP */