

#pragma once
#ifndef SPRAY_CONFIG_APP_HPP
#define SPRAY_CONFIG_APP_HPP

#include "../AppEnv.hpp"
#include "../Modules/Assert.hpp"
#include "App.hpp"

class SprayConfigApp : public App {
   private:
    int level;  // btwn 1 and 5
    const static int maxLevel = 5;
    void setLevel(int level);

   public:
    SprayConfigApp();
    void onButtonPressed(AnalogButton *btn);
    void activate();
    char *toString() { return "SprayConfigApp"; }
};

void SprayConfigApp::setLevel(int level) {
    assert_simple(level >= 1 && level <= maxLevel,
                  "level must be btwn 1 and maxLevel");
    // data setting
    this->level = level;
    appEnv->data->sprayDelay = (unsigned long)(20000 + this->level * 1000);

    // text setting
    char levelTxt[level + 1];
    for (int i = 1; i <= level; i++) {
        levelTxt[i - 1] = 'X';
    }
    levelTxt[level] = '\0';
    sprintf(texts[0], "%s", levelTxt);
}

SprayConfigApp ::SprayConfigApp() : App() {
    level = 1;
    sprintf(texts[0], "");
    sprintf(texts[1], "spray delay");

    setLevel(level);
}

void SprayConfigApp::activate() { fireUpdate(); }

void SprayConfigApp ::onButtonPressed(AnalogButton *btn) {
    if (btn == appEnv->btns->nextButton) {
        int nextLevel = level + 1;
        nextLevel = ((nextLevel - 1) % maxLevel) + 1;
        setLevel(nextLevel);
        fireUpdate();
    } else if (btn == appEnv->btns->selectButton) {
        appEnv->funcs->openDefaultApp();
    }
}

#endif /* SPRAY_CONFIG_APP_HPP */