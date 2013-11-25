#include "Arduino.h"
#include <due_can.h>
#include "Bamocar.h"

void Bamocar::set_transmit_id(uint8_t txid)
{
	m_txid = txid;
}

void Bamocar::set_receive_id(uint8_t rxid)
{
	m_rxid = rxid;
}

void Bamocar::set_primary_can(CANRaw* pCan)
{
	m_pCan = pCan;
}

void Bamocar::set_sniffer_can(CANRaw* pCan)
{
	m_pCanSniffer = pCan;
}


void Bamocar::abort_transfer(uint8_t regid)
{
  TX_CAN_FRAME txFrame;

  txFrame.id = m_rxid;
  txFrame.dlc = 3;
  txFrame.data[0] = 0x3d;
  txFrame.data[1] = regid;
  txFrame.data[2] = 0xff;

  m_pCan->sendFrame(txFrame);
}

void Bamocar::request_transfer(uint8_t regid, uint8_t interval)
{
  TX_CAN_FRAME txFrame;

  txFrame.id = m_rxid;
  txFrame.dlc = 3;
  txFrame.data[0] = 0x3d;
  txFrame.data[1] = regid;
  txFrame.data[2] = interval;

  m_pCan->sendFrame(txFrame);
}

void Bamocar::init_primary_can()
{
  m_pCan->reset_all_mailbox();

  m_pCan->mailbox_set_mode(0, CAN_MB_RX_MODE);
  m_pCan->mailbox_set_accept_mask(0, 0x1FFFFFFF, false);
  m_pCan->mailbox_set_id(0, m_txid, false);

  m_pCan->mailbox_set_mode(1, CAN_MB_TX_MODE);
  m_pCan->mailbox_set_priority(1, 15);                   //15 is the CAN0 transmit priority
  m_pCan->mailbox_set_accept_mask(1, 0x1FFFFFFF, false);
  m_pCan->mailbox_set_id(1, m_rxid, false);

  m_pCan->enable_interrupt(CAN_IER_MB0);
}