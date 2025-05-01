#include <Arduino.h>
#include <SoftwareSerial.h>

#include "aprs.h"
#include "log.h"
#include "util.h"

#if BOARD_TYPE == 0   // 0: TT&C Board

const int APRS_RX_PIN = 2;   // RX pin for SoftwareSerial
const int APRS_TX_PIN = 3;   // TX pin for SoftwareSerial

SoftwareSerial aprsSerial(APRS_RX_PIN, APRS_TX_PIN);
APRS aprs(aprsSerial);

void setup() {
    Serial.begin(9600);
    aprsSerial.begin(9600);
    aprs.setup();
    LOG("Setup complete.");
}

void loop() {
    // Periodically send a message every 15 seconds
    static unsigned long lastMillis = 0;
    unsigned long currentMillis = millis();
    if (currentMillis - lastMillis >= 15000) {   // 15 seconds
        lastMillis = currentMillis;
        LOG("Broadcasting...");
        String data = "AT+SENSOR=MyGO!!!!!";
        String response = aprs.send(data);
        LOG("Response: ");
        printString(response);
    }

    // Read user commands from Serial Monitor and send to APRS
    /*
    if (aprs.available()) {
        String aprs_text = aprs.receive();
        LOG("Received:\n");
        printString(aprs_text);
    }
    if (Serial.available()) {
        String command = Serial.readString();
        String response = aprs.run(command);
        LOG("APRS Command: ");
        printString(command);
        LOG("Response: ");
        printString(response);
    }
    */
}

#elif BOARD_TYPE == 1   // 1: Payload Board

#elif BOARD_TYPE == 2   // 2: Car Board

#endif
