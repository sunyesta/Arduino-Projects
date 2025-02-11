
#pragma once
#ifndef DISTANCE_SENSOR_HPP
#define DISTANCE_SENSOR_HPP

#include "../AppEnv.hpp"
#include "../Apps/InfoApp.hpp"
#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"

class DistanceSensor : Loopable {
   private:
    int distance_cm = -1;
    Pin echoPin, trigPin;
    unsigned long secs2 = 2, secs10 = 10, debounceTime = 1000;
    Debounce *wait2 = new Debounce(&secs2), *wait10 = new Debounce(&secs10),
             *debounce = new Debounce(&debounceTime);
    bool looped = true;

   public:
    DistanceSensor(Pin echoPin, Pin trigPin);

    void loop();
};

// public
DistanceSensor::DistanceSensor(Pin echoPin, Pin trigPin) : Loopable() {
    this->echoPin = echoPin;
    this->trigPin = trigPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    debounce->start();
}

void DistanceSensor::loop() {
    if (appEnv->funcs->isSensorsOn()) {
        if (debounce->isValidOnce()) {
            digitalWrite(trigPin, LOW);
            wait2->start();
        } else if (wait2->isValidOnce()) {
            digitalWrite(trigPin, HIGH);
            wait10->start();
        } else if (wait10->isValidOnce()) {
            digitalWrite(trigPin, LOW);

            long duration = pulseIn(echoPin, HIGH);

            distance_cm = duration * 0.034 / 2;
            appEnv->data->distance = distance_cm;
            appEnv->apps->infoApp->updateDistance(true);
            debounce->start();
        }
    } else {
        debounce->start();  // restarts debounce sequence;
    }

    // SLOW WAY
    //  digitalWrite(trigPin, LOW);
    //  delayMicroseconds(2);
    //  digitalWrite(trigPin, HIGH);
    //  delayMicroseconds(10);
    //  digitalWrite(trigPin, LOW);

    // long duration = pulseIn(echoPin, HIGH);
    // distance_cm = duration * 0.034 / 2;
    // appEnv->data->distance = distance_cm;
    // Serial.println(distance_cm);
    // appEnv->apps->infoApp->updateDistance(true);
    // END SLOW WAY
}
// private

#endif /* DISTANCE_SENSOR_HPP */