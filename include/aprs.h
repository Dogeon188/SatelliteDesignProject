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
    bool run(const String &command, bool exceptResponse = true);
    inline String send(const String &command) {
        if (this->run(command)) {
            String response = this->receive();
            return response;
        }
        return "";
    }
};

#endif   // APRS_H
