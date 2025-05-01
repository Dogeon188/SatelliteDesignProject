#ifndef APRS_H
#define APRS_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class APRS {
private:
    SoftwareSerial &aprsSerial;
    const static String startupCommands[];

public:
    APRS(SoftwareSerial &serial) : aprsSerial(serial) {
    }
    void setup();
    inline bool available() {
        return aprsSerial.available();
    }
    String receive();
    inline String run(String &command) {
        aprsSerial.print(command + "\r\n");
        return receive();
    }
    inline String send(String &command) {
        return run("AT+SENSOR=" + command);
    }
};

#endif   // APRS_H
