#include "variant.h"
#include <due_can.h>
#include "Bamocar.h"
#include "BamocarRegisters.h"
#include "BamocarRequest.h"

#define NDRIVE_RXID    0x210
#define NDRIVE_TXID    0x180
#define NDRIVE_BPS     CAN_BPS_250K

#define DEBUG

/**
 * Init bamocar class
 */
Bamocar bamocar;

void setup()
{
    /**
     * Start serial port at 115200 baud
     */
    Serial.begin(115200);
    bamocar.setSerialDebug(Serial);

    /**
     * Set Bamocar addresses
     */
    bamocar.begin(NDRIVE_TXID, NDRIVE_RXID, NDRIVE_BPS);

    /**
     * Attach CAN as primary bus
     */
    bamocar.initCAN(CAN);

    #ifdef DEBUG
    /**
     * Attach CAN2 as secondary bus for debugging
     */
    bamocar.initCANSniffer(CAN2);
    #endif

    /**
     * NVIC: Nested Vectored Interrupt Controller
     */
    NVIC_EnableIRQ(CAN0_IRQn);
    NVIC_EnableIRQ(CAN1_IRQn);

    /**
     * Perform various tests
     */
    test_1();
}

// Test 1: request "N Actual"
static void test_1(void)
{
    BamocarAbortRequest abortRequest = BamocarAbortRequest(REG_N_ACTUAL);
    bamocar.send(abortRequest);
    delayMicroseconds(1000);

    // BamocarRequest request = BamocarRequest(REG_N_ACTUAL, 100);
    // bamocar.send(request);
    // delayMicroseconds(1000);

    BamocarRequest request = BamocarRequest(REG_N_MAX, 100);
    bamocar.send(request);
    delayMicroseconds(1000);
}

void loop()
{
    RX_CAN_FRAME inFrame;

    if (bamocar.getCAN().rx_avail()) {
        bamocar.getCAN().get_rx_buff(&inFrame);

        #ifdef DEBUG
        bamocar.getSerialDebug().print("CAN\t");
        bamocar.print_can_frame(inFrame);
        #endif

        // #ifndef DEBUG
        bamocar.parse_response(inFrame);
        // #endif

        delayMicroseconds(100);
    }

    if (bamocar.getCANSniffer().rx_avail()) { 
        bamocar.getCANSniffer().get_rx_buff(&inFrame);

        #ifdef DEBUG
        bamocar.getSerialDebug().print("CAN2\t");
        bamocar.print_can_frame(inFrame);
        #endif

        delayMicroseconds(100);
    }
}
