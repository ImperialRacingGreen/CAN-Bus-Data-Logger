#ifndef Bamocar_h
#define Bamocar_h

#include "Arduino.h"
#include <due_can.h>

class Bamocar
{
public:
	Bamocar();
	~Bamocar();
	void set_transmit_id(uint8_t txid);
	void set_receive_id(uint8_t rxid);
	void set_primary_can(CANRaw* pCan);
	void set_sniffer_can(CANRaw* pCan);
	void init_primary_can();

	void abort_transfer(uint8_t regid);
	void request_transfer(uint8_t regid, uint8_t interval);
private:
	CANRaw* m_pCan;
	CANRaw* m_pCanSniffer;
	uint8_t m_txid;
	uint8_t m_rxid;
};

#endif