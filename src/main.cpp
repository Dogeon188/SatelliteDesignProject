#include <Arduino.h>
#include <SoftwareSerial.h>

#include "aprs.h"
#include "led.h"
#include "log.h"
#include "util.h"

#if BOARD_TYPE == 0   // 0: TT&C Board

const int APRS_RX_PIN = 2;   // RX pin for SoftwareSerial
const int APRS_TX_PIN = 3;   // TX pin for SoftwareSerial

SoftwareSerial aprsSerial(APRS_RX_PIN, APRS_TX_PIN);
APRS aprs(aprsSerial);

void setup() {
    LOG("Initializing Serial Monitor...");
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    aprsSerial.begin(9600);
    aprs.setup();
    led_blink(200, 5);
    LOG("Setup complete.");
}

void loop() {
    // Periodically send a message every 15 seconds

    static unsigned long lastMillis = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - lastMillis >= 15000) {   // 15 seconds
        lastMillis = currentMillis;
        LOG("Broadcasting...");
        String data = "AT+SENSOR=1234567890";
        String response = aprs.send(data);
        LOG("Response: ");
        printString(response);
        led_blink(500, 3);
    }

    // Read user commands from Serial Monitor and send to APRS

    // if (aprs.available()) {
    //     String aprs_text = aprs.receive();
    //     LOG("Received:\n");
    //     printString(aprs_text);
    // }
    // if (Serial.available()) {
    //     String command = Serial.readString();
    //     LOG("APRS Command: " + command);
    //     if (aprs.run(command)) {
    //         LOG("Response: ");
    //         String response = aprs.receive();
    //         printString(response);
    //     }
    // }
}

#elif BOARD_TYPE == 1   // 1: Payload Board

#elif BOARD_TYPE == 2   // 2: Car Board

#endif
