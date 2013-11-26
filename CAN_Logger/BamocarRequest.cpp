#include "BamocarRequest.h"

BamocarRequest::BamocarRequest(uint8_t regID, uint8_t interval)
{
    m_dataLength = 3;
    m_regID = regID;
    m_interval = interval;
}

uint8_t BamocarRequest::getDataLength()
{
    return m_dataLength;
}

uint8_t BamocarRequest::getRegID()
{
    return m_regID;
}

uint8_t BamocarRequest::getInterval()
{
    return m_interval;
}

void BamocarRequest::setInterval(uint8_t interval)
{
    m_interval = interval;
}

void BamocarRequest::fillDataBytes(uint8_t* data)
{
    data[0] = 0x3d;
    data[1] = m_regID;
    data[2] = m_interval;
}

BamocarAbortRequest::BamocarAbortRequest(uint8_t regID) : BamocarRequest(regID, 0xff)
{
    // setting interval to 0xff aborts subsequent requests
}