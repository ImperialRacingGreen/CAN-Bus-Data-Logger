#ifndef BmsRequest_h
#define BmsRequest_h

#include "Arduino.h"
#include <due_can.h>

class BmsRequest {
public:
    BmsRequest(uint8_t regID);

    uint8_t getDataLength();
    void    fillDataBytes(uint8_t* data);

private:
    uint8_t m_dataLength;
    uint8_t m_regID;
    uint16_t m_rxID;
};

#endif