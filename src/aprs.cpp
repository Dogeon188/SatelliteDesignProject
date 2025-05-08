#include "aprs.h"

#include "led.h"
#include "log.h"
#include "util.h"

const String APRS::startupCommands[] = {
    "AT+HELP=1",
    "AT+DEMO=1",
    "AT+UBLOX=1",
    "AT+CALL=BX3AAO",   // Callsign
    "AT+SSID=11",       // ID after the callsign
    "AT+MODE=APRS",     // APRS or CW
    "AT+CW=OFF",        // Continuous Wave, as Morse code
    "AT+RADIO=ON",
    "AT+DIGI=OFF",
    "AT+PWR=H",
    "AT+GPSPWR=ON",
    "AT+CWWPM=30",   // CW Word Per Minute
    "AT+FRE=1",
    "AT+TIME=60",
    "AT+BEACON=1,!,2447.62N,/,12059.72E,O,YUSAT",
    "AT+CWMSG=VVV VVV",   // CW Message
    "AT+DMOSETGROUP=1,144.640,144.640,0,3,0,0",
    "AT+TX=ON",
};

void APRS::setup() {
    LOG("Setting up APRS module...");
    delay(1000);   // Wait for the module to initialize

    for (const String &command : startupCommands) {
        LOG("Sending command: " + command);
        bool success = this->run(command);
        if (success) {
            String response = this->receive();
        }
        led_blink(50);
    }
    delay(1000);   // Wait for the module to process the commands
    LOG("APRS module setup complete.");
}

String APRS::receive() {
    String response = "";
    while (aprsSerial.available()) {
        response += aprsSerial.readString();
    }
    return response;
}

const int MAX_TRIES = 3;
const int WAIT_TIME_MS = 1000;

bool APRS::run(const String &command, bool exceptResponse) {
    bool success = false;
    aprsSerial.print(command + "\r\n");
    if (!exceptResponse) return true;

    for (int tries = 0; tries < MAX_TRIES; tries++) {
        auto lastSentTime = millis();
        while (millis() - lastSentTime < WAIT_TIME_MS) {
            if (aprsSerial.available()) {
                success = true;
                break;
            }
        }
        if (success) break;
        LOG("Failed to send command, retrying: " + command);
    }
    return success;
}
