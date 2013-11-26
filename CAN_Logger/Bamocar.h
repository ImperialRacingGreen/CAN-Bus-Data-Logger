#ifndef Bamocar_h
#define Bamocar_h

#include "Arduino.h"
#include "BamocarRequest.h"
#include <due_can.h>

#define REG_N_ACTUAL 0x30

class Bamocar
{
public:
    Bamocar();
    /**
     * Initialise the transmit id, receive id, and baudrate of the class
     * @param txID     Transmit CAN ID
     * @param rxID     Receive CAN ID
     * @param baudRate CAN Bus baud rate
     */
    void begin(uint8_t txID, uint8_t rxID, uint32_t baudRate);
    /**
     * Set up Serial for outputting debugging messages
     */
    void set_serial_debug(Stream& rSerial);
    /**
     * Set up primary CAN bus to transmit and receive messages
     */
    void init_primary_can(CANRaw& rCan);
    /**
     * Set up CAN2 to act as a sniffer between bamocar and arduino
     */
    void init_sniffer_can(CANRaw& rCan);
    /**
     * Send CAN message
     */
    void send(BamocarRequest& request);

    void print_can_frame(RX_CAN_FRAME frame);            //prints the can frame
    void parse_response(RX_CAN_FRAME frame);            //parses the information held in can frame

    bool can_frame_available();
private:
    CANRaw* m_can;                        //can
    CANRaw* m_canSniffer;                //can sniffer
    Stream* m_serialDebug;        //serial for debugging purposes

    uint8_t  m_txID;        //transmit id for can
    uint8_t  m_rxID;        //receive id for can
    uint32_t m_baudRate;        //baudrate for can

    RX_CAN_FRAME m_rxFrame;
};

#endif