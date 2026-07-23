#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "max7219.h"

#define SPI_PORT spi0
#define SPI_BAUD_RATE 1*1000*1000 //1 MHz
#define SPI_CLK 2
#define SPI_MOSI 3
#define SPI_MISO 4
#define SPI_CS 5

int main()
{
    stdio_init_all();

    spi_init(SPI_PORT, SPI_BAUD_RATE);

    gpio_set_function(SPI_CLK, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MISO, GPIO_FUNC_SPI);
    gpio_set_function(SPI_CS, GPIO_FUNC_SPI);

    spi_set_format(SPI_PORT, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);


    while (true) {
        tight_loop_contents();
    }
}
