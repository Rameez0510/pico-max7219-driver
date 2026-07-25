#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "max7219.h"

#define SPI_PORT spi0
#define SPI_BAUD_RATE 1*100*1000 //1 MHz
#define SPI_CLK 2
#define SPI_MOSI 3
#define SPI_MISO 4
#define SPI_CS 5

#define DISPLAYS 4 //add to max7219_t



int main()
{
    stdio_init_all();

    spi_init(SPI_PORT, SPI_BAUD_RATE);

    gpio_set_function(SPI_CLK, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MISO, GPIO_FUNC_SPI);
    // gpio_set_function(SPI_CS, GPIO_FUNC_SPI);
    gpio_init(SPI_CS);
    gpio_set_dir(SPI_CS, GPIO_OUT);

    spi_set_format(SPI_PORT, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    max7219_t mx;
    //initialize max7219
    max7219_init(&mx, SPI_PORT, SPI_CS, 4);

    display_t disp0= {
        0b11010000,
        0b11110000,
        0b11110000,
        0b11110000,
        0b11110000,
        0b11110000,
        0b11110000,
        0b11110000
    };

    display_t disp1;
    printf("Starting\n");

    max7219_send_cmd(mx, Digit0, 0b11110000, 0b1000);
    max7219_send_cmd(mx, Digit0, 0b10101010, 0b0001);

    // sleep_ms(2500);
    // max7219_send_cmd(mx, Digit0, disp0.digit0, 0b0100);
    // max7219_send_cmd(mx, Digit1, disp0.digit1, 0b0100);
    // max7219_send_cmd(mx, Digit2, disp0.digit2, 0b0100);
    // max7219_send_cmd(mx, Digit3, disp0.digit3, 0b0100);
    // max7219_send_cmd(mx, Digit4, disp0.digit4, 0b0100);
    // max7219_send_cmd(mx, Digit5, disp0.digit5, 0b0100);
    // max7219_send_cmd(mx, Digit6, disp0.digit6, 0b0100);
    // max7219_send_cmd(mx, Digit7, disp0.digit7, 0b0100);

    // for (uint8_t i = 0; i < 8; i++)
    // {
    //     // printf("digit: %d   LEDs: 0x%02X\t", i, ((uint8_t *)(&disp1))[i]);
    //     // ((uint8_t *)(&disp1))[i] = 1<<i;
    //     // printf("after LEDs: 0x%02X\n", ((uint8_t *)(&disp1))[i]);
    //     // max7219_send_cmd(mx, Digit0 + i, ((uint8_t *)(&disp1))[i], 0b0100);
    //     max7219_set_LED(&disp1, i, i, true);
    //     // sleep_ms(500);
    // }
    // max7219_update_display(mx, &disp1, 0b0100);
    
    max7219_clear_display(&disp1);
    
    // sleep_ms(1000);

    // max7219_send_cmd(mx, Digit0, disp1.digit0, 0b0100);
    // max7219_send_cmd(mx, Digit1, disp1.digit1, 0b0100);
    // max7219_send_cmd(mx, Digit2, disp1.digit2, 0b0100);
    // max7219_send_cmd(mx, Digit3, disp1.digit3, 0b0100);
    // max7219_send_cmd(mx, Digit4, disp1.digit4, 0b0100);
    // max7219_send_cmd(mx, Digit5, disp1.digit5, 0b0100);
    // max7219_send_cmd(mx, Digit6, disp1.digit6, 0b0100);
    // max7219_send_cmd(mx, Digit7, disp1.digit7, 0b0100);

    while (true) {
        // tight_loop_contents();
        // max7219_display_test(mx, 0b1000, true);
        // printf("display test on\n");
        // sleep_ms(1000);
        // max7219_display_test(mx, 0b1000, false);
        // printf("display test off\n");
        // sleep_ms(1000);
        for (uint8_t i = 0; i < 8; i++)
    {
        max7219_set_LED(&disp1, i, i, false);
        max7219_update_display(mx, &disp1, 0b0100);
        sleep_ms(50);
    }
    for (uint8_t i = 0; i < 8; i++)
    {
        max7219_set_LED(&disp1, i, i, true);
        max7219_update_display(mx, &disp1, 0b0100);
        sleep_ms(50);
    }

    }
}
