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
#define Decode_Mode_No_Decode 0x00
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
 * @brief display_t use to hold the state of a display, used to modify display view
 */
typedef struct{
    uint8_t digit0, digit1, digit2, digit3, digit4, digit5, digit6, digit7; 
}display_t;

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
 * @warning initialize CS pin as general GPIO 
 * @param mx pointer to max7219_t instance
 * @param spi_port instance for SPI communication
 * @param cs_pin CS pin used
 * @param displays Number of displays used
 */
void max7219_init(max7219_t *mx, spi_inst_t *spi_port, uint8_t cs_pin, uint8_t displays);

/**
 * @brief set intestity of display(s)
 * @param mx instance for max7219
 * @param level level of intensity in range `0-15`
 * @param display apply to display(s)
 */
void max7219_set_intensity(max7219_t mx, uint8_t level, uint8_t display);

/**
 * @brief set decode mode for each digit each display
 * @param mx instance for max7219
 * @param digit digits to be set to decode mode (eg. for digit 1, send: `0b00000010`)
 * @param display apply to display(s)
 */
void max7219_set_decode_mode(max7219_t mx, uint8_t digit, uint8_t display);

/**
 * @brief set the scan limit for each display
 * @param mx instance for max7219
 * @param digits scan limit upto digit `0-7`
 * @param display apply to display(s)
 */
void max7219_set_scan_limit(max7219_t mx, uint8_t digits, uint8_t display);

/**
 * @brief turn on/off shutdown mode (turn on/off display(s))
 * @param mx instance for max7219
 * @param display apply to display(s)
 * @param on turn ON - `true` ; turn OFF - `false`
 */
void max7219_shutdown_mode(max7219_t mx, uint8_t display, bool on);

/**
 * @brief test all LEDs of display(s)
 * @param mx instance for max7219
 * @param display apply to display(s)
 * @param on turn ON - `true` ; turn OFF - `false`
 */
void max7219_display_test(max7219_t mx, uint8_t display, bool on);

/**
 * @brief set the state of LEDs using x,y coordinates on `display_t`
 * @warning update display after setting LEDs
 * @param disp display_t pointer
 * @param x set led
 * @param y choose digit
 * @param set set or reset LED
 */
void max7219_set_LED(display_t *disp, uint8_t x, uint8_t y, bool set);
/**
 * @brief clear the LEDs state on `display_t`
 * @warning update display after clearing LEDs
 * @param disp display_t pointer
 */
void max7219_clear_display(display_t *disp);

/**
 * @brief update display(s) based on the LEDs state on `display_t` variable
 * @param mx instance for max7219
 * @param disp display_t pointer to the variable holding the state
 * @param display apply to display(s)
 */
void max7219_update_display(max7219_t mx, display_t *disp, uint8_t display);

/**
 * @brief display a character on display(s)
 * @param mx instance for max7219
 * @param c char type character to be displayed
 * @param display apply to display(s)
 */
void max7219_display_char(max7219_t mx, char c, uint8_t display);