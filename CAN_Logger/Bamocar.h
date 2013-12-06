#ifndef Bamocar_h
#define Bamocar_h

#include "Arduino.h"
#include "BamocarRequest.h"
#include <due_can.h>

class Bamocar {
public:
    Bamocar();
    /**
     * Initialise the transmit id, receive id, and baudrate of the class
     * @param txID     Transmit CAN ID
     * @param rxID     Receive CAN ID
     * @param baudRate CAN Bus baud rate
     */
    void         begin(uint16_t txID, uint16_t rxID, uint32_t baudRate);
    /**
     * Serial Debug getter
     */
    Stream&      getSerialDebug();
    /**
     * Set up Serial for outputting debugging messages
     */
    void         setSerialDebug(Stream& rSerial);
    /**
     * Set up primary CAN bus to transmit and receive messages
     */
    void         initCAN(CANRaw& rCan);
    /**
     * Set up CAN2 to act as a sniffer between bamocar and arduino
     */
    void         initCANSniffer(CANRaw& rCan);
    /**
     * Send CAN message
     */
    void         send(BamocarRequest& request);
    /**
     * Primary CAN getter
     */
    CANRaw       getCAN();
    /**
     * CAN Sniffer getter
     */
    CANRaw       getCANSniffer();

    void         print_can_frame(RX_CAN_FRAME frame);            //prints the can frame
    void         parse_response(RX_CAN_FRAME frame);            //parses the information held in can frame
private:
    /**
     * Primary CAN
     */
    CANRaw*      m_can;
    /**
     * Secondary CAN (for debugging)
     */
    CANRaw*      m_canSniffer;
    /**
     * Serial for debugging
     */
    Stream*      m_serialDebug;
    /**
     * Transmit ID of motor controller
     */
    uint16_t      m_txID;
    /**
     * Receive ID of motor controller
     */
    uint16_t      m_rxID;
    /**
     * Buadrate of motor controller
     */
    uint32_t     m_baudRate;
    /**
     * Temporary storage for CAN receive frame
     */
    RX_CAN_FRAME m_rxFrame;
};

#endif