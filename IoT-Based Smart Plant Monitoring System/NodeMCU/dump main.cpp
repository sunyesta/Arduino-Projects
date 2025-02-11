
#include <Arduino.h>
#include <SPI.h>

#include "./Modules/LoopManager.hpp"
#include "AppEnv.hpp"

int sel = D0;
int output = A0;
void setup() {
    Serial.begin(9600);
    while (!Serial) delay(100);  // wait for native usb
    appEnv->setup();
}

void loop() { loopManager->loop(); }
