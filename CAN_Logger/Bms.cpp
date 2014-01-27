#include "Bms.h"

/**
 * ==========
 * Bms::Bms
 * ==========
 */
Bms::Bms(){
	// Do nothing
}

/**
 * ==========
 * Bms::send
 * ==========
 */
void Bms::send(BmsRequest& request) {
    TX_CAN_FRAME txFrame;

    txFrame.id = m_rxID;
    txFrame.dlc = request.getDataLength();
    request.fillDataBytes(txFrame.data);

    m_can->sendFrame(txFrame);

    Serial.println("sent");
}