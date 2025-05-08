#include "led.h"

#include <Arduino.h>

void led_blink(int half_period_ms, int repeat_time) {
    for (int i = 0; i < repeat_time; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(half_period_ms);   // LED on for 200ms
        digitalWrite(LED_BUILTIN, LOW);
        delay(half_period_ms);   // LED off for 200ms
    }
}
