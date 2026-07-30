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

    display_t disp0, disp1;
    printf("Starting\n");


    max7219_clear_display(&disp0);
    max7219_clear_display(&disp1);
    
#define DELAY 100

    // max7219_display_char(mx, '0', 0b1111);

    

    while (true) {
        tight_loop_contents();
        // for (uint8_t i = 0; i < 8; i++)
        // {
        //     max7219_set_LED(&disp0, i, i, true);
        //     max7219_set_LED(&disp1, i, 7-i, false);
        //     max7219_update_display(mx, &disp0, 0b1000);
        //     max7219_update_display(mx, &disp1, 0b0001);
        //     sleep_ms(DELAY);
        // }
        // for (uint8_t i = 0; i < 8; i++)
        // {
        //     max7219_set_LED(&disp0, i, i, false);
        //     max7219_set_LED(&disp1, i, 7-i, true);
        //     max7219_update_display(mx, &disp0, 0b1000);
        //     max7219_update_display(mx, &disp1, 0b0100);
        //     sleep_ms(DELAY);
        // }
        // for (uint8_t i = 0; i < 8; i++)
        // {
        //     max7219_set_LED(&disp0, i, i, true);
        //     max7219_set_LED(&disp1, i, 7-i, false);
        //     max7219_update_display(mx, &disp0, 0b0010);
        //     max7219_update_display(mx, &disp1, 0b0100);
        //     sleep_ms(DELAY);
        // }
        // for (uint8_t i = 0; i < 8; i++)
        // {
        //     max7219_set_LED(&disp0, i, i, false);
        //     max7219_set_LED(&disp1, i, 7-i, true);
        //     max7219_update_display(mx, &disp0, 0b0010);
        //     max7219_update_display(mx, &disp1, 0b0001);
        //     sleep_ms(DELAY);
        // }
        for (uint8_t i = '0'; i <= '9'; i++){
            max7219_display_char(mx, i, 0b1000);
            for (uint8_t j = '0'; j <= '9'; j++){
                max7219_display_char(mx, j, 0b0100);
                for (uint8_t k = '0'; k <= '9'; k++){
                    max7219_display_char(mx, k, 0b0010);
                    for (uint8_t l = '0'; l <= '9'; l++){
                        max7219_display_char(mx, l, 0b0001);
                        sleep_ms(DELAY);
                    }
                }
            }
        }
        
    }
}
