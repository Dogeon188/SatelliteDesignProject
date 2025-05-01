#include "util.h"

#define BYTES_PER_LINE 16

bool isLikelyAscii(const String &str) {
    for (char c : str) {
        if ((c < 0x20 || c > 0x7E) && c != 0x0A && c != 0x0D) {
            return false;   // Non-ASCII character found
        }
    }
    return true;   // All characters are ASCII
}

void printString(const String &str) {
    if (isLikelyAscii(str)) {
        Serial.println(str);
    } else {
        Serial.println("Non-ASCII String:");
        Serial.println(str);
        Serial.println("Hexadecimal representation: ");
        const char *strPtr = str.c_str();
        for (size_t i = 0; i < str.length(); i++) {
            unsigned char c = (unsigned char)strPtr[i];
            if (c < 0x10) {
                Serial.print("0");   // Pad with leading zero if necessary
            }
            Serial.print(c, HEX);
            Serial.print(" ");
            if ((i + 1) % BYTES_PER_LINE == 0) {
                Serial.println();   // New line every 16 bytes
            }
        }
        Serial.println();
    }
}
