#include "aprs.h"

#include "log.h"
#include "util.h"

const String APRS::startupCommands[] = {
    "AT+HELP=1",
    "AT+DEMO=1",
    "AT+UBLOX=1",
    "AT+CALL=BX3AAO",     // Callsign
    "AT+SSID=10",         // ID after the callsign
    "AT+MODE=APRS",       // APRS or CW
    "AT+CW=ON",           // Continuous Wave, as Morse code
    "AT+CWWPM=30",        // CW Word Per Minute
    "AT+CWMSG=VVV VVV",   // CW Message
    "AT+RADIO=ON",
    "AT+DIGI=OFF",
    "AT+PWR=H",
    "AT+GPSPWR=ON",
    "AT+TX=ON",
    "AT+FRE=1",
    "AT+TIME=60",
    "AT+BEACON=1,!,2447.62N,/,12059.72E,O,MyGO",
    "AT+DMOSETGROUP=1,144.640,144.640,0,3,0,0"
};

void APRS::setup() {
    LOG("Setting up APRS module...");
    delay(1000);   // Wait for the module to initialize
    for (const String &command : startupCommands) {
        LOG("Sending command: " + command);
        aprsSerial.print(command + "\r\n");
        while (!aprsSerial.available());
        String response = aprsSerial.readString();
        // LOG("Response: " + response);
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
