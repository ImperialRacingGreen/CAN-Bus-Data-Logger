#ifndef Bamocar_h
#define Bamocar_h

#include "Arduino.h"
#include <due_can.h>

class Bamocar
{
public:
	Bamocar();
	~Bamocar();
	void set_primary_can(CANRaw* pCan);
	void set_sniffer_can(CANRaw* pCan);
private:
	CANRaw* m_pCan;
	CANRaw* m_pCanSniffer;
};

#endif