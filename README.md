# Pico MAX7219 Driver
This is a simple driver for the MAX7219 LED dot matrix display, designed to work with the Raspberry Pi Pico C SDK. The driver allows you to control the display using SPI communication.

## Features
- Allows to use multi instance of MAX7219
- Supports multiple displays in a daisy chain configuration
- Instance to hold data for each display
- Set or reset individual LEDs
- Display characters (currently only supports 0-9)

## Hardware Connections
| Pico | MAX7219 | Description |
|------|---------|-------------|
| VSYS | VCC | 5V Power Supply |
| Selected MOSI Pin | DIN | Data Input |
| Selected SCK Pin | CLK | Clock Input |
| GPIO Pin for CS | CS | Chip Select;  **Must initialize CS pin as `GPIO_OUT`** and not `gpio_set_function(CS, GPIO_FUNC_SPI)` |
| GND | GND | Ground |

## API Description
The driver provides the following functions:
| Function | Description | Example usage |
|---------|-------------|----------------|
| `max7219_t` | Structure representing the MAX7219 device. Contains the SPI port instance, CS gpio pin, and number of displays in the daisy chain. | `max7219_t mx;` |
| `display_t` | Instance containing the data for a display. | `display_t disp0;` |
| `max7219_init()` | Initializes the MAX7219 device with `No decode mode`, `Scan limit to all digits`, and `minimum intensity`. | `max7219_init(&mx, SPI_PORT, SPI_CS, 4);` |
| `max7219_send_cmd()` | Sends a command by choosing mode, value and display(s) to use. | `max7219_send_cmd(mx, Intensity, 0x03, 0b1010);` |
| `max7219_clear_display()` | Clears the `display_t` instance. | `max7219_clear_display(&disp0);` |
| `max7219_set_LED()` | Sets or resets individual bits(LEDs) based on the x, y coordinates on `display_t` instance. | `max7219_set_LED(&disp0, 2, 3, true);` `max7219_set_LED(&disp0, 4, 5, false);` |
| `max7219_update_display()` | Updates display(s) with the data from `display_t` instance. | `max7219_update_display(mx, &disp0, 0b0101);` |
| `max7219_display_char()` | Displays a character on display(s) | `max7219_display_char(mx, '5', 0b0011);` |

