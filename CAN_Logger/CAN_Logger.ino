#include "variant.h"
#include <due_can.h>
#include "Bamocar.h"

#define CAN0_TX_PRIO  15

#define NDRIVE_RXID  0x210
#define NDRIVE_TXID  0x180
#define NDRIVE_BPS   CAN_BPS_250K

#define REG_N_ACTUAL 0x30

#define DEBUG

Bamocar bamocar;

inline void setup_serial() {
  // start serial port at 115200 bps: 
  Serial.begin(115200);
  bamocar.set_debug_serial(Serial);
}

inline void setup_can_sniffer_for_debugging() {
  CAN2.reset_all_mailbox();

  CAN2.mailbox_set_mode(0, CAN_MB_RX_MODE);
  CAN2.mailbox_set_accept_mask(0, 0x1FFFFFFF, false);
  CAN2.mailbox_set_id(0, NDRIVE_RXID, false);

  CAN2.enable_interrupt(CAN_IER_MB0);
}

void setup() {
  setup_serial();

  bamocar.set_ndrive_options(NDRIVE_TXID, NDRIVE_RXID,NDRIVE_BPS);

  bamocar.setup_can_hardware();
  bamocar.init_primary_can();
  
  #ifdef DEBUG
  setup_can_sniffer_for_debugging();
  #endif

  test_1();
}

// Test 1: request "N Actual"
static void test_1(void)
{
  //CAN.global_send_transfer_cmd(CAN_TCR_MB1);
  bamocar.abort_transfer(REG_N_ACTUAL);
  delayMicroseconds(1000);
  bamocar.request_transfer(REG_N_ACTUAL, 100);
  delayMicroseconds(1000);
}

void loop() {
  RX_CAN_FRAME inFrame;

  if (CAN.rx_avail()) {
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
