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

    printf("Starting\n");

    max7219_send_cmd(mx, Digit0, 0b11110000, 0b1000);
    max7219_send_cmd(mx, Digit0, 0b10101010, 0b0001);

    sleep_ms(1000);

    while (true) {
        // tight_loop_contents();
        max7219_display_test(mx, 0b1000, true);
        printf("display test on\n");
        sleep_ms(1000);
        max7219_display_test(mx, 0b1000, false);
        printf("display test off\n");
        sleep_ms(1000);

    }
}
