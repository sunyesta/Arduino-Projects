

#pragma once
#ifndef ASSERT_HPP
#define ASSERT_HPP

#include "../NoErrors.hpp"

void printErr() { Serial.print("ERROR: "); }

void assert_simple(bool val, char *message) {
    if (!val) {
        printErr();
        Serial.println(message);
        delay(100);
        exit(-1);
    }
}

void assert_str(bool val, char *message, char *actual) {
    if (!val) {
        printErr();
        Serial.println(message);
        Serial.print("actual: ");
        Serial.println(actual);
        delay(100);
        exit(-1);
    }
}

// template <typename T>
// void assert_val(bool val, char *message, T actual) {
//     if (!val) {
//         printErr();
//         Serial.println(message);
//         Serial.print("actual: ");
//         Serial.println(actual);
//         delay(100);
//         exit(-1);
//     }
// }

void assert_int(bool val, char *message, int actual) {
    if (!val) {
        printErr();
        Serial.println(message);
        Serial.print("actual: ");
        Serial.println(actual);
        delay(100);
        exit(-1);
    }
}

#endif /* ASSERT_HPP */