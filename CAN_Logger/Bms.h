#ifndef Bms_h
#define Bms_h

#include "Arduino.h"
#include "BmsRequest.h"
#include <due_can.h>

class Bms(){
public:
	Bms();

	void send(BamocarRequest& request);
}

#endif