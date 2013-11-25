#ifndef Bamocar_h
#define Bamocar_h

#include "Arduino.h"
#include <due_can.h>

class Bamocar
{
public:
	Bamocar();
	~Bamocar();

	void set_transmit_id(uint8_t txID);
	void set_receive_id(uint8_t rxID);
	void set_primary_can(CANRaw& rCan);
	void set_sniffer_can(CANRaw& rCan);
	void init_primary_can();

	void abort_transfer(uint8_t regID);
	void request_transfer(uint8_t regID, uint8_t interval);
private:
	CANRaw& m_can;
	CANRaw& m_canSniffer;
	uint8_t m_txID;
	uint8_t m_rxID;
};

#endif