#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>

// Function to check if a string is likely ASCII
// This function checks if a string contains only ASCII characters
// (0x20 to 0x7E) and line feed (0x0A) or carriage return (0x0D).
bool isLikelyAscii(const String &str);

void printString(const String &str);

#endif   // UTIL_H
