#include "variant.h"
#include <due_can.h>
#include "Bamocar.h"
#include "BamocarRequest.h"

#define NDRIVE_RXID    0x210
#define NDRIVE_TXID    0x180
#define NDRIVE_BPS     CAN_BPS_250K

#define DEBUG

Bamocar bamocar;

void setup() {
    // start serial port at 115200 bps
    Serial.begin(115200);
    bamocar.set_serial_debug(Serial);

    bamocar.begin(NDRIVE_TXID, NDRIVE_RXID, NDRIVE_BPS);

    bamocar.init_primary_can(CAN);

    #ifdef DEBUG
    bamocar.init_sniffer_can(CAN2);
    #endif

    test_1();
}

// Test 1: request "N Actual"
static void test_1(void)
{
    BamocarRequest request = BamocarRequest(REG_N_ACTUAL, 100);
    bamocar.send(request);
    delayMicroseconds(1000);

    BamocarAbortRequest abortRequest = BamocarAbortRequest(REG_N_ACTUAL);
    bamocar.send(abortRequest);
    delayMicroseconds(1000);
}

void loop() {
    RX_CAN_FRAME inFrame;

    if (bamocar.can_frame_available()) {
        CAN.get_rx_buff(&inFrame);

        #ifdef DEBUG
        Serial.print("CAN\t");
        bamocar.print_can_frame(inFrame);
        #endif

        #ifndef DEBUG
        bamocar.parse_response(inFrame);
        #endif

        delayMicroseconds(100);
    }

    if (CAN2.rx_avail()) { 
        CAN2.get_rx_buff(&inFrame);

        #ifdef DEBUG
        Serial.print("CAN2\t");
        bamocar.print_can_frame(inFrame);
        #endif

        delayMicroseconds(100);
    }
}
