
#include "./LoopManager.hpp"

#include <Arduino.h>

#include "./Assert.hpp"
#include "./Loopable.hpp"

LoopManager *loopManager = new LoopManager();

LoopManager::LoopManager() {}

int LoopManager::connect(Loopable *loopable) {
    assert_int(this->loopableCount < maxLoopable,
               (char *)"cur loopables must be below max loopable", maxLoopable);
    int index = loopableCount;
    this->loopableCount += 1;
    loopables[index] = loopable;

    // Serial.print("created loopable at:");
    // Serial.println(index);
    // Serial.print("size of arr: ");
    // Serial.println(loopableCount);
    return index;
}
void LoopManager::loop() {
    for (int i = 0; i < loopableCount; i++) {
        loopables[i]->loop();
    }
}
