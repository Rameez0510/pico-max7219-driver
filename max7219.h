#include "pico/stdlib.h"
#include "hardware/spi.h"

//Registers
#define No_Op 0x00
#define Digit0 0x01
#define Digit1 0x02
#define Digit2 0x03
#define Digit3 0x04
#define Digit4 0x05
#define Digit5 0x06
#define Digit6 0x07
#define Digit7 0x08
#define Decode_Mode 0x09
#define Intensity 0x0A
#define Scan_Limit 0x0B
#define Shutdown_Mode 0x0C
#define Display_Test 0x0F
