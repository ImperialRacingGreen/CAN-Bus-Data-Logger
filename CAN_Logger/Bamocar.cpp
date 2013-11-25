#include "Arduino.h"
#include <due_can.h>
#include "Bamocar.h"

void Bamocar::set_transmit_id(uint8_t txID)
{
	m_txID = txID;
}

void Bamocar::set_receive_id(uint8_t rxID)
{
	m_rxID = rxID;
}

void Bamocar::set_primary_can(CANRaw& rCan)
{
	m_can = rCan;
}

void Bamocar::set_sniffer_can(CANRaw& rCan)
{
	m_canSniffer = rCan;
}


void Bamocar::abort_transfer(uint8_t regID)
{
  TX_CAN_FRAME txFrame;

  txFrame.id = m_rxID;
  txFrame.dlc = 3;
  txFrame.data[0] = 0x3d;
  txFrame.data[1] = regID;
  txFrame.data[2] = 0xff;

  m_can.sendFrame(txFrame);
}

void Bamocar::request_transfer(uint8_t regID, uint8_t interval)
{
  TX_CAN_FRAME txFrame;

  txFrame.id = m_rxID;
  txFrame.dlc = 3;
  txFrame.data[0] = 0x3d;
  txFrame.data[1] = regID;
  txFrame.data[2] = interval;

  m_can.sendFrame(txFrame);
}