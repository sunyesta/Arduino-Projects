#include "MotionSensor.hpp"

#include "../AppEnv.hpp"
#include "../Modules/Loopable.hpp"


MotionSensor::MotionSensor(Pin pin) : Loopable() {
    this->pin = pin;
    pinMode(pin, INPUT);
    // attachInterrupt(digitalPinToInterrupt(pin), MotionSensor_toggleMotion,
    //                 CHANGE);
}

void MotionSensor::loop() {
    if (appEnv->funcs->isSensorsOn()) {
        updateMotion();
    }
}

void MotionSensor::updateMotion() {
    int motionData = digitalRead(pin);
    if (motionData == 1) {
        appEnv->data->hasMotion = true;
    } else {
        appEnv->data->hasMotion = false;
    }
    if (appEnv->data->activeApp == appEnv->apps->infoApp) {
        appEnv->apps->infoApp->updateHasMotion(true);
    }
}