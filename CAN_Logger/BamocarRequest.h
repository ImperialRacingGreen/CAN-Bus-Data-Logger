#ifndef BamocarRequest_h
#define BamocarRequest_h

#include "Arduino.h"
#include <due_can.h>

class BamocarRequest
{
public:
    BamocarRequest(uint8_t regID, uint8_t interval);

    uint8_t get_data_length();
    uint8_t get_regID();
    uint8_t get_interval();
    void set_interval(uint8_t interval);

    void fill_data_bytes(uint8_t* data);

private:
    uint8_t m_data_length;
    uint8_t m_regID;
    uint8_t m_interval;
};

class BamocarAbortRequest : public BamocarRequest
{
public:
    BamocarAbortRequest(uint8_t regID);
};

#endif