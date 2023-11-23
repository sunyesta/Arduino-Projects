
#pragma once
#ifndef DEBOUNCE_HPP
#define DEBOUNCE_HPP

#define ULONG_MAX 4294967296

#define DebounceTime unsigned long

class Debounce {
   private:
    DebounceTime lastLoggedTime;
    DebounceTime *debounceTime;
    bool running;

   public:
    Debounce(DebounceTime *debounceTime) {
        this->lastLoggedTime = 0;
        this->debounceTime = debounceTime;
        this->running = false;
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
        running = true;
        lastLoggedTime = millis();
    }

    inline bool isValid() { return running && getDeltaTime() > *debounceTime; }
    bool isValidOnce() {
        if (isValid()) {
            running = false;
            return true;
        }
        return false;
    }
};

#endif /* DEBOUNCE_HPP */