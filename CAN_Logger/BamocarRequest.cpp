#include "BamocarRequest.h"

BamocarRequest::BamocarRequest(uint8_t regID, uint8_t interval)
{
    m_regID = regID;
    m_interval = interval;
}

uint8_t BamocarRequest::get_data_length()
{
    return m_data_length;
}

uint8_t BamocarRequest::get_regID()
{
    return m_regID;
}

uint8_t BamocarRequest::get_interval()
{
    return m_interval;
}

void BamocarRequest::set_interval(uint8_t interval)
{
    m_interval = interval;
}

void BamocarRequest::fill_data_bytes(uint8_t* data)
{
    data[0] = 0x3d;
    data[1] = m_regID;
    data[2] = m_interval;
}

BamocarAbortRequest::BamocarAbortRequest(uint8_t regID) : BamocarRequest(regID, 0xff)
{
    // setting interval to 0xff aborts subsequent requests
}