#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "max7219.h"

void max7219_init(max7219_t *mx, spi_inst_t *spi_port, uint8_t cs_pin, uint8_t displays){
    mx->spi_i = spi_port;
    mx->CS_pin = cs_pin;
    mx->displays = displays;

    //reset registers
    max7219_send_cmd(*mx, Decode_Mode, 0x00, 0xFF); //0b1111 --> 0xFF for initialize only
    max7219_send_cmd(*mx, Intensity, 0x00, 0xFF);
    max7219_send_cmd(*mx, Scan_Limit, 0x00, 0xFF);
    max7219_send_cmd(*mx, Display_Test, 0x00, 0xFF); //turn off display test
    max7219_send_cmd(*mx, Digit0, 0x00, 0xFF);
    max7219_send_cmd(*mx, Digit1, 0x00, 0xFF);
    max7219_send_cmd(*mx, Digit2, 0x00, 0xFF);
    max7219_send_cmd(*mx, Digit3, 0x00, 0xFF);
    max7219_send_cmd(*mx, Digit4, 0x00, 0xFF);
    max7219_send_cmd(*mx, Digit5, 0x00, 0xFF);
    max7219_send_cmd(*mx, Digit6, 0x00, 0xFF);
    max7219_send_cmd(*mx, Digit7, 0x00, 0xFF);
    max7219_send_cmd(*mx, Shutdown_Mode, 0x00, 0xFF); //turn on shutdown mode

    //initialize with no decode mode, minimum intensity, scan limit to all digits
    max7219_send_cmd(*mx, Decode_Mode, Decode_Mode_No_Decode, 0xFF);
    max7219_send_cmd(*mx, Intensity, 0x00, 0xFF);
    max7219_send_cmd(*mx, Scan_Limit, 0x07, 0xFF);

    //turn off shutdown mode
    max7219_send_cmd(*mx, Shutdown_Mode, 0x01, 0xFF); 
    
}

void max7219_send_cmd(max7219_t mx, uint8_t mode, uint8_t value, uint8_t display){ //display 0b1010 type

    uint16_t data = (mode<<8) | value;
    uint16_t ignore = No_Op;

    gpio_put(mx.CS_pin, 0);
    for (int i = mx.displays-1; i >= 0; i--)
    {
        if (display & (1<<i))  
        {
            spi_write16_blocking(mx.spi_i, &data, 1);
        }else{
            spi_write16_blocking(mx.spi_i, &ignore, 1);
        }
    }
    gpio_put(mx.CS_pin, 1);
    // printf("Mode: 0x%02X  Value: 0x%02X Data sent: 0x%04X\n", mode, value, data[0]);
}

void max7219_set_intensity(max7219_t mx, uint8_t level, uint8_t display){
    max7219_send_cmd(mx, Intensity, level, display);
}

void max7219_set_decode_mode(max7219_t mx, uint8_t digit, uint8_t display){
    max7219_send_cmd(mx, Decode_Mode, digit, display);
}

void max7219_set_scan_limit(max7219_t mx, uint8_t digits, uint8_t display){
    max7219_send_cmd(mx, Scan_Limit, digits, display);
}

void max7219_shutdown_mode(max7219_t mx, uint8_t display, bool on){
    max7219_send_cmd(mx, Shutdown_Mode, ~on, display);
}

void max7219_display_test(max7219_t mx, uint8_t display, bool on){
    max7219_send_cmd(mx, Display_Test, on, display);
}

void max7219_set_LED(display_t *disp,uint8_t x, uint8_t y, bool set){
    if(set){
        ((uint8_t *)(disp))[y] = ((uint8_t *)(disp))[y] | 1<<(7-x);
    }
    else{
        ((uint8_t *)(disp))[y] = ((uint8_t *)(disp))[y] & ~(1<<(7-x));
    }
}

void max7219_clear_display(display_t *disp){
    for (uint8_t i = 0; i < 8; i++)
    {
        ((uint8_t *)(disp))[i] = 0;
    }
    
}

void max7219_update_display(max7219_t mx, display_t *disp, uint8_t display){
    for (uint8_t i = 0; i < 8; i++)
    {
        max7219_send_cmd(mx, Digit0 + i, ((uint8_t *)(disp))[i], display);
    }
    
}

