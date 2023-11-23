
#pragma once
#ifndef IS_OPEN_APP_HPP
#define IS_OPEN_APP_HPP

#include "../Modules/Debounce.hpp";
#include "../Modules/Loopable.hpp";
#include "App.hpp";

class IsOpenApp : public App {
   public:
    IsOpenApp() : App() {}

    void activate() {
        sprintf(texts[0], "Machine is");
        sprintf(texts[1], "Open");
        fireUpdate();
    }

    char *toString() { return "IsOpenApp"; }
};

#endif /* IS_OPEN_APP_HPP */