

#ifndef DEBOUNCE_HPP
#define DEBOUNCE_HPP

#include <Arduino.h>

#define ULONG_MAX 4294967296

#define DebounceTime unsigned long

class Debounce {
   private:
    DebounceTime lastLoggedTime;
    DebounceTime *debounceTime;
    DebounceTime storage;
    bool _running;

   public:
    Debounce(DebounceTime *debounceTime) {
        this->lastLoggedTime = 0;
        this->debounceTime = debounceTime;
        this->_running = false;
        start();
    }
    Debounce(DebounceTime debounceTime) {
        this->lastLoggedTime = 0;
        this->storage = debounceTime;
        this->debounceTime = &storage;
        this->_running = false;
        start();
    }

    // works with millis rollover time
    unsigned long getDeltaTime() {
        if (millis() >= lastLoggedTime) {
            // normal operation
            return millis() - lastLoggedTime;
        } else {
            // millis rollover
            return ULONG_MAX - lastLoggedTime + millis();
        }
    }

    // resets the debounce timer
    void start() {
        _running = true;
        lastLoggedTime = millis();
    }

    inline bool isValid() { return _running && getDeltaTime() > *debounceTime; }
    bool isValidOnce() {
        if (isValid()) {
            _running = false;
            return true;
        }
        return false;
    }

    bool isValidRestart() {
        if (isValid()) {
            start();
            return true;
        }
        return false;
    }

    bool running() { return _running; }
}

;

#endif /* DEBOUNCE_HPP */