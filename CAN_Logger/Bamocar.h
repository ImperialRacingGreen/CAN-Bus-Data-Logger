#ifndef Bamocar_h
#define Bamocar_h

#include "Arduino.h"
#include <due_can.h>

class Bamocar
{
public:
	Bamocar();
	~Bamocar();

	void set_ndrive_options(uint8_t txID, uint8_t rxID, uint32_t baudrate);

	void setup_can_hardware();
	void setup_can_sniffer_for_debugging();
	void set_debug_serial(HardwareSerial& rSerial);

	void set_primary_can(CANRaw& rCan);
	void set_sniffer_can(CANRaw& rCan);
	void init_primary_can();

	void abort_transfer(uint8_t regID);
	void request_transfer(uint8_t regID, uint8_t interval);

	void print_can_frame(RX_CAN_FRAME frame);
	void parse_response(RX_CAN_FRAME frame);
private:
	CANRaw& m_can;
	CANRaw& m_canSniffer;
	HardwareSerial& m_serialDebug;

	uint8_t m_txID;
	uint8_t m_rxID;
	uint32_t m_bps;
};

#endif