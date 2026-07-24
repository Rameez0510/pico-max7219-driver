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

// int max7219_send_cmd(uint8_t mode, uint8_t value){
//     // uint8_t data[] = {mode, value, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//     // uint8_t data[] = {mode, value};
//     // spi_write_blocking(SPI_PORT, data, 8);
//     // spi_write_blocking(SPI_PORT, data, 2);
    
//     // uint16_t data[] = {0, (mode<<8) | value, 0, 0};
//     uint16_t data[] = {(mode<<8) | value, (mode<<8) | value, (mode<<8) | value, (mode<<8) | value};
//     gpio_put(SPI_CS, 0);
//     spi_write16_blocking(SPI_PORT, data, 4);
//     gpio_put(SPI_CS, 1);
//     printf("Mode: 0x%02X  Value: 0x%02X Data sent: 0x%04X\n", mode, value, data[0]);
//     if (mode == Digit3 || mode == Digit4){
//         sleep_ms(500);
//     }
// }
int max7219_send_cmd(uint8_t mode, uint8_t value, uint8_t display){ //display 0b1010 type

    uint16_t data = (mode<<8) | value;
    uint16_t ignore = No_Op;

    gpio_put(SPI_CS, 0);
    for (int i = DISPLAYS-1; i >= 0; i--)
    {
        if (display & (1<<i))  
        {
            spi_write16_blocking(SPI_PORT, &data, 1);
        }else{
            spi_write16_blocking(SPI_PORT, &ignore, 1);
        }
    }
    gpio_put(SPI_CS, 1);
        
    
    // spi_write16_blocking(SPI_PORT, data, 4);
    // printf("Mode: 0x%02X  Value: 0x%02X Data sent: 0x%04X\n", mode, value, data[0]);
}

int max7219_apply_to_one(uint8_t mode, uint8_t value, uint8_t display){
    uint16_t data[] = {0, 0, 0, 0};
    data[3-display] = (mode << 8) | value;
    gpio_put(SPI_CS, 0);
    spi_write16_blocking(SPI_PORT, data, 4);
    gpio_put(SPI_CS, 1);
    sleep_ms(250);
    printf("Mode: 0x%02X  Value: 0x%02X Data sent: 0x%04X\n", mode, value, data[3-display]);
}

int max7219_send_single_cmd(uint8_t mode, uint8_t value){
    uint16_t data = (mode << 8) | value;
    gpio_put(SPI_CS, 0);
    spi_write16_blocking(SPI_PORT, &data, 1);
    gpio_put(SPI_CS, 1);
}

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

    //initialize max7219
    printf("Starting\n");
    max7219_send_cmd(Decode_Mode, 0x00, 0b1111);
    max7219_send_cmd(Intensity, 0x00, 0b1111);
    max7219_send_cmd(Scan_Limit, 0x00, 0b1111);
    max7219_send_cmd(Display_Test, 0x00, 0b1111); //turn off display test
    // sleep_ms(2000);
    max7219_send_cmd(Digit0, 0x00, 0b1111);
    max7219_send_cmd(Digit1, 0x00, 0b1111);
    max7219_send_cmd(Digit2, 0x00, 0b1111);
    max7219_send_cmd(Digit3, 0x00, 0b1111);
    max7219_send_cmd(Digit4, 0x00, 0b1111);
    max7219_send_cmd(Digit5, 0x00, 0b1111);
    max7219_send_cmd(Digit6, 0x00, 0b1111);
    max7219_send_cmd(Digit7, 0x00, 0b1111);
    max7219_send_cmd(Shutdown_Mode, 0x00, 0b1111); //turn on shutdown mode

    max7219_send_cmd(Decode_Mode, No_Decode, 0b1111);
    max7219_send_cmd(Intensity, 0x00, 0b1111);
    max7219_send_cmd(Scan_Limit, 0x07, 0b1111);

    max7219_send_cmd(Digit3, 0x3C, 0b1001);
    max7219_send_cmd(Digit4, 0xC3, 0b0110);

    max7219_send_cmd(Shutdown_Mode, 0x01, 0b1111); //turn off shutdown mode

    sleep_ms(1000);

    // max7219_send_cmd(Shutdown_Mode, 0x00);
    // max7219_apply_to_one(Digit0, 0xF0, 3);
    sleep_ms(1000);
    // max7219_apply_to_one(Digit0, 0xF0, 1);
    // max7219_send_cmd(Shutdown_Mode, 0x01);
    // printf("0x%02X\n", 0b1010);
    sleep_ms(1000);
    // max7219_send_single_cmd(Digit2, 0xFF);
    // sleep_ms(1000);
    // max7219_send_single_cmd(Digit2, 0xFF);
    // sleep_ms(1000);
    // max7219_send_single_cmd(Digit2, 0xFF);
    // sleep_ms(1000);
    // max7219_apply_to_one(Digit0, 0b00000001, 1);





    while (true) {
        tight_loop_contents();
        // sleep_ms(10);
        // max7219_send_cmd(Display_Test, 0x00);
        // max7219_send_cmd(Shutdown_Mode, 0x00);
        // sleep_ms(1000);
        // max7219_send_cmd(Shutdown_Mode, 0x01);
        // sleep_ms(1000);
    }
}
