#ifndef Bamocar_h
#define Bamocar_h

#include "Arduino.h"
#include <due_can.h>

#define REG_N_ACTUAL 0x30

class Bamocar
{
public:
	Bamocar();
	~Bamocar();

	void set_ndrive_options(uint8_t txID, uint8_t rxID, uint32_t baudrate);		//initialises the transmit id, receive id, and baudrate of the class

	void set_debug_serial(HardwareSerial& rSerial);		//sets up serial for debugging purposes
	void init_primary_can(CANRaw& rCan);							//sets up CAN1 mailboxes to receive and transmit messages
	void init_can_sniffer(CANRaw& rCan);				//sets up CAN2 to act as a sniffer between bamocar and arduino

	void abort_transfer(uint8_t regID);								//aborts transfer of value of regid
	void request_transfer(uint8_t regID, uint8_t interval);			//requests transfer of value of regid at every interval, interval

	void print_can_frame(RX_CAN_FRAME frame);			//prints the can frame
	void parse_response(RX_CAN_FRAME frame);			//parses the information held in can frame

	bool can_frame_available();
private:
	CANRaw& m_can;						//can
	CANRaw& m_canSniffer;				//can sniffer
	HardwareSerial& m_serialDebug;		//serial for debugging purposes

	uint8_t m_txID;		//transmit id for can
	uint8_t m_rxID;		//receive id for can
	uint32_t m_bps;		//baudrate for can

	RX_CAN_FRAME m_rxFrame;
};

#endif