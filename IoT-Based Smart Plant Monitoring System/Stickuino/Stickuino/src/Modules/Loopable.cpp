#include "Loopable.hpp"

#include <Arduino.h>

#include "LoopManager.hpp"
#include "Loopable.hpp"

Loopable::Loopable() { index = loopManager->connect(this); }

void Loopable::loop() {
    const char buff[] = "default loop function";
    Serial.println(buff);
}