#include "Lcd.hpp"

#include <LiquidCrystal.h>

#include "../AppEnv.hpp"
#include "../Apps/App.hpp"
#include "../Modules/Assert.hpp"
#include "../NoErrors.hpp"

Lcd ::Lcd(Pin rs, Pin e, Pin db4, Pin db5, Pin db6, Pin db7) {
    this->lcd = new LiquidCrystal(rs, e, db4, db5, db6, db7);
    this->lcd->begin(lcdRows, lcdCols);
}

void Lcd ::setLineText(int line, char* text, bool centered) {
    assert_str(strlen(text) <= lcdCols, "text must be correct length", text);
    lcd->setCursor(0, line);

    char finalTxt[20];
    if (centered) {
        int spaces = (16 - strlen(text)) / 2;
        char* spacesTxt = "            ";
        spacesTxt[spaces] = '\0';

        sprintf(finalTxt, "%s%s%s", spacesTxt, text, spacesTxt);
        sprintf(finalTxt, "%-16s", finalTxt);
        spacesTxt[spaces] = ' ';
    } else {
        sprintf(finalTxt, "%-16s", text);
    }

    lcd->print(finalTxt);
}
void Lcd ::setText(char texts[2][17]) {
    assert_simple(texts, "must have text");
    setLineText(0, texts[0], false);
    setLineText(1, texts[1], false);
}

// TODO find error in this function
template <typename T_App>
void Lcd ::update(T_App* app, char texts[2][17]) {
    // Serial.println("updating lcd");
    if (appEnv->data->activeApp == app) {
        setText(texts);
    } else {
        Serial.print("WARNING: not activeApp trying to update LCD = ");
        char* str = app->toString();
        Serial.println(str);
    }
}

template <typename T_App>
void Lcd ::activateApp(T_App* app) {
    if (appEnv->data->activeApp) {
        appEnv->data->activeApp->deactivate();
    }

    appEnv->data->activeApp = app;
    app->activate();
}