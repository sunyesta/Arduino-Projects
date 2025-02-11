
#pragma once
#ifndef LOOP_MANAGER_HPP
#define LOOP_MANAGER_HPP

#include "./Assert.hpp"
#include "./Loopable.hpp"

class Loopable;

class LoopManager {
   private:
    static const int maxLoopable = 20;
    int loopableCount = 0;
    Loopable *loopables[maxLoopable];

   public:
    LoopManager();
    int connect(Loopable *loopable);
    void loop();
};

LoopManager::LoopManager() {}

int LoopManager::connect(Loopable *loopable) {
    assert_int(this->loopableCount < maxLoopable,
               "cur loopables must be below max loopable", maxLoopable);
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

LoopManager *loopManager = new LoopManager();

#endif /* LOOP_MANAGER_HPP */