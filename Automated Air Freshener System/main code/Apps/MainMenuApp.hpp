
#pragma once
#ifndef MAIN_MENU_APP_HPP
#define MAIN_MENU_APP_HPP

#include "../Components/AnalogButton.hpp"
#include "App.hpp"

class MainMenuApp : public App {
   private:
    class Option {
       public:
        char text[100];
        void (*callback)();

        Option(char *text, void (*callbackFunc)()) {
            sprintf(this->text, "%s", text);

            this->callback = callback;
        }

        void select() {}
    };

    int itemIndex = 0;
    static const int optionCount = 4;
    char options[4][12];

    void displayMenuItem(char *op);

   public:
    MainMenuApp();
    void activate();
    void onButtonPressed(AnalogButton *btn);
    void triggerSelection(int selectionIndex);
    char *toString() { return "MainMenuApp"; }
};

MainMenuApp::MainMenuApp() : App() {
    sprintf(options[0], "info app");
    sprintf(options[1], "spray mode");
    sprintf(options[2], "spray");
    sprintf(options[3], "reset");
}

void MainMenuApp::displayMenuItem(char *op) { sprintf(texts[0], "%s", op); };

void MainMenuApp ::activate() {
    itemIndex = 0;
    displayMenuItem(options[itemIndex]);
    sprintf(texts[1], "<- scroll ->");
    fireUpdate();
}

void MainMenuApp::triggerSelection(int selectionIndex) {
    if (selectionIndex == 0) {
        appEnv->lcd->activateApp(appEnv->apps->infoApp);
    } else if (selectionIndex == 1) {
        appEnv->lcd->activateApp(appEnv->apps->sprayConfigApp);
    } else if (selectionIndex == 2) {
        appEnv->lcd->activateApp(appEnv->apps->forceSprayApp);
    } else if (selectionIndex == 3) {
        appEnv->lcd->activateApp(appEnv->apps->resetSpraysApp);
    }
}

void MainMenuApp ::onButtonPressed(AnalogButton *btn) {
    if (btn == appEnv->btns->nextButton) {
        itemIndex += 1;
        itemIndex = itemIndex % optionCount;
        displayMenuItem(options[itemIndex]);
        fireUpdate();
    } else if (btn == appEnv->btns->selectButton) {
        triggerSelection(itemIndex);
        // TODO turn this callback into a function that is
        // hard codes with if statements for each button
    }
}

#endif /* MAIN_MENU_APP_HPP */