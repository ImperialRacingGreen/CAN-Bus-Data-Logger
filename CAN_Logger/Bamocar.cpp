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

void Bamocar::set_debug_serial(HardwareSerial& rSerial)
{
  m_serialDebug = rSerial;
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

void Bamocar::init_primary_can()
{
  m_can.reset_all_mailbox();

  m_can.mailbox_set_mode(0, CAN_MB_RX_MODE);
  m_can.mailbox_set_accept_mask(0, 0x1FFFFFFF, false);
  m_can.mailbox_set_id(0, m_txID, false);

  m_can.mailbox_set_mode(1, CAN_MB_TX_MODE);
  m_can.mailbox_set_priority(1, 15);                   //15 is the CAN0 transmit priority
  m_can.mailbox_set_accept_mask(1, 0x1FFFFFFF, false);
  m_can.mailbox_set_id(1, m_rxID, false);

  m_can.enable_interrupt(CAN_IER_MB0);
}

void Bamocar::print_can_frame(RX_CAN_FRAME frame)
{
  m_serialDebug.print("ID:");
  m_serialDebug.print(frame.id, HEX);
  m_serialDebug.print("\t");
  m_serialDebug.print("FID:");
  m_serialDebug.print(frame.fid, HEX);
  m_serialDebug.print("\t");
  m_serialDebug.print("RTR:");
  m_serialDebug.print(frame.rtr, HEX);
  m_serialDebug.print("\t");
  m_serialDebug.print("IDE:");
  m_serialDebug.print(frame.ide, HEX);
  m_serialDebug.print("\t");
  m_serialDebug.print("DLC:");
  m_serialDebug.print(frame.dlc, HEX);
  m_serialDebug.print("\t");
  m_serialDebug.print("Data:");
  m_serialDebug.print("\t");
  for (int i = 0; i < frame.dlc; i++) {
    m_serialDebug.print(frame.data[i], HEX);
    m_serialDebug.print("\t");
  }
  m_serialDebug.println();
}

void Bamocar::parse_response(RX_CAN_FRAME rxFrame)
{
  //if id==REG_N_ACTUAL = 0x30
  if (rxFrame.data[0] == 0x30) {
    float value = (rxFrame.data[1] | (rxFrame.data[2] << 8)) / 32767.0 * 100;
    m_serialDebug.print(rxFrame.data[1] | (rxFrame.data[2] << 8), HEX);
    m_serialDebug.print("\t");
    m_serialDebug.println(value);
  }  
}