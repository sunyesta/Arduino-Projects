#include "Loopable.hpp"

#include "LoopManager.hpp"

Loopable::Loopable() { index = loopManager->connect(this); }

void Loopable::loop() {
    const char buff[] = "default loop function";
    Serial.println(buff);
}