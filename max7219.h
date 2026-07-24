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

//modes
#define No_Decode 0x00
#define Shutdown_Mode_ON 0x00
#define Shutdown_Mode_OFF 0x01

/**
 * @brief Holds info about the max7219 device
 */
typedef struct{
    spi_inst_t *spi_i; /**< SPI instance */
    uint8_t CS_pin;
    uint8_t displays;

}max7219_t;


/**
 * @brief send command by choosing mode, value and display to use
 * @brief choose display in bit format (eg. 0b1010)
 * @param mx instance for max7219
 * @param mode choose mode or digit register to use
 * @param value value associated with the command
 * @param display choose display(s) to be affected by this command, choose display in bit format (eg. 0b1010)
 */
void max7219_send_cmd(max7219_t mx, uint8_t mode, uint8_t value, uint8_t display);

/**
 * @brief initialize the max7219 device with no decode mode, minimum intensity, scan limit to all digits
 * @param mx pointer to max7219_t instance
 * @param spi_port instance for SPI communication
 * @param cs_pin CS pin used
 * @param displays Number of displays used
 */
void max7219_init(max7219_t *mx, spi_inst_t *spi_port, uint8_t cs_pin, uint8_t displays);