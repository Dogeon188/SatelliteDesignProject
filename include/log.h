#ifndef LOG_H
#define LOG_H

#include <Arduino.h>

extern char buffer[32];

#ifdef WITH_SERIAL_MONITOR
#define LOG(message) { \
    sprintf(buffer, "[%08lu] ", millis()); \
    Serial.print(buffer); \
    Serial.println(message); \
}
#else
#define LOG(message) {}
#endif

#endif   // LOG_H
