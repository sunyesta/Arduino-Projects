
#pragma once
#ifndef INFO_APP_HPP
#define INFO_APP_HPP

#include "../AppEnv.hpp"
#include "../Components/AirFreshener.hpp"
#include "../Components/AnalogButton.hpp"
#include "App.hpp"

enum Page { PAGE_TEMP_SPRAY, PAGE_MOT_DIS, PAGE_CURSTATE, PAGE_COUNT };

class InfoApp : public App {
   private:
    Page page;  // should only be changed by setPage()
    void setPage(Page page);
    void onButtonPressed(AnalogButton *btn);

   public:
    InfoApp();

    void activate();
    void deactivate();

    // Specific Methods

    void updateTemperature(bool updateScreen);
    void updateSpraysRemaining(bool updateScreen);
    void updateHasMotion(bool updateScreen);
    void updateDistance(bool updateScreen);
    void updateCurState(bool updateScreen);

    char *toString() { return "InfoApp"; }
};

InfoApp::InfoApp() : App() { setPage(PAGE_MOT_DIS); }

void InfoApp::activate() {
    appEnv->data->setMachineState(MachineState::notInUse);
    setPage(this->page);
    fireUpdate();
}
void InfoApp::deactivate() {
    appEnv->data->setMachineState(MachineState::menuInUse);
}

void InfoApp::onButtonPressed(AnalogButton *btn) {
    if (btn == appEnv->btns->selectButton) {
        appEnv->funcs->openSelectionMenu();
    } else if (btn == appEnv->btns->nextButton) {
        Page nextPage = static_cast<Page>((page + 1) % PAGE_COUNT);

        setPage(nextPage);
        fireUpdate();

    } else if (btn == appEnv->btns->manButton) {
        appEnv->lcd->activateApp(appEnv->apps->forceSprayApp);
    }
}

void InfoApp::setPage(Page page) {
    this->page = page;
    updateTemperature(false);
    updateSpraysRemaining(false);
    updateHasMotion(false);
    updateDistance(false);
    updateCurState(false);
}
//

// UPDATES

void InfoApp::updateTemperature(bool updateScreen) {
    if (page == PAGE_TEMP_SPRAY) {
        sprintf(texts[0], "Temp: %dC", appEnv->data->temperature);

        if (updateScreen) {
            fireUpdate();
        }
    }
}

void InfoApp::updateSpraysRemaining(bool updateScreen) {
    if (page == PAGE_TEMP_SPRAY) {
        // if (appEnv->data->spraysRemaining > 0) {
        //     sprintf(texts[1], "sprays rem %d",
        //     appEnv->data->spraysRemaining);
        // } else {
        //     sprintf(texts[1], "no sprays rem");
        // }

        sprintf(texts[1], "sprays rem %d", appEnv->data->spraysRemaining);

        if (updateScreen) {
            fireUpdate();
        }
    }
}

void InfoApp::updateHasMotion(bool updateScreen) {
    if (page == PAGE_MOT_DIS) {
        char hasMotion = (appEnv->data->hasMotion ? 'X' : '-');

        sprintf(texts[0], "Has Motion = %c", hasMotion);
        if (updateScreen) {
            fireUpdate();
        }
    }
}

void InfoApp::updateDistance(bool updateScreen) {
    if (page == PAGE_MOT_DIS) {
        sprintf(texts[1], "Distance = %d", appEnv->data->distance);
        if (updateScreen) {
            fireUpdate();
        }
    }
}

void InfoApp::updateCurState(bool updateScreen) {
    if (page == PAGE_CURSTATE) {
        char *curState;
        switch (appEnv->data->machineState()) {
            case MachineState::menuInUse:
                curState = "menuInUse";
                break;
            case MachineState::notInUse:
                curState = "notInUse";
                break;
            case MachineState::triggeredSprayImminent:
                curState = "trigSprayImnent";
                break;
            case MachineState::useCleaning:
                curState = "useCleaning";
                break;
            case MachineState::useNum1:
                curState = "useNum1";
                break;
            case MachineState::useNum2:
                curState = "useNum2";
                break;
            case MachineState::useUnknown:
                curState = "useUnknown";
                break;
            case MachineState::isOpen:
                curState = "Open";
                break;
            default:
                curState = "ERROR STATE";
                break;
        }
        sprintf(texts[0], "cur state is");
        sprintf(texts[1], curState);

        if (updateScreen) {
            fireUpdate();
        }
    }
}

#endif /* INFO_APP_HPP */