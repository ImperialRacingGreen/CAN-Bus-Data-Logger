#include "BmsRequest.h"

BmsRequest::BmsRequest(){
	m_dataLength = 3;
	m_rxID = 0x745;			//not sure which version [1.xx = 0x745 OR 2.xx = 0x7E0]
	m_regID = regID;
}

void BmsRequest::fillDataBytes(uint8_t* data) {
    data[0] = 3;
    data[1] = 0x10;		//request mode
    data[2] = m_regID;
}

uint8_t BmsRequest::getDataLength() {
    return m_dataLength;
}