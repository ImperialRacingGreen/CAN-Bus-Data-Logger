#ifndef BamocarRequest_h
#define BamocarRequest_h

#include "Arduino.h"
#include <due_can.h>

class BamocarRequest
{
public:
    BamocarRequest(uint8_t regID, uint8_t interval);

    uint8_t getDataLength();
    uint8_t getRegID();
    uint8_t getInterval();
    void setInterval(uint8_t interval);

    void fillDataBytes(uint8_t* data);

private:
    uint8_t m_dataLength;
    uint8_t m_regID;
    uint8_t m_interval;
};

class BamocarAbortRequest : public BamocarRequest
{
public:
    BamocarAbortRequest(uint8_t regID);
};

#endif