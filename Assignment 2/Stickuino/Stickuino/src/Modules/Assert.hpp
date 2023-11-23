

#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <Arduino.h>

void printErr();

void assert_simple(bool val, char *message);

void assert_str(bool val, char *message, char *actual);

void assert_int(bool val, char *message, int actual);

#endif /* ASSERT_HPP */