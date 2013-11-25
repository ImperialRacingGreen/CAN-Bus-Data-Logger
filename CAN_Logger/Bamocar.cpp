#include "Arduino.h"
#include <due_can.h>
#include "Bamocar.h"

void Bamocar::set_primary_can(CANRaw* pCan)
{
	m_pCan = pCan;
}

void Bamocar::set_sniffer_can(CANRaw* pCan)
{
	m_pCanSniffer = pCan;
}
