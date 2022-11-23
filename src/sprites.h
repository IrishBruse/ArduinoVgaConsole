#include <Arduino.h>

#define IMG_BIRD_WIDTH 6
#define IMG_BIRD_BWIDTH 2
#define IMG_BIRD_HEIGHT 6

const unsigned char img_bird_data[IMG_BIRD_HEIGHT][IMG_BIRD_BWIDTH] PROGMEM={
    {0b00000100,0b00000000},
    {0b00001111,0b00000000},
    {0b00001111,0b10000000},
    {0b01111111,0b11010000},
    {0b00111111,0b00000000},
    {0b00000000,0b00000000},
};

const unsigned char img_bird_mask_data[IMG_BIRD_HEIGHT][IMG_BIRD_BWIDTH] PROGMEM={
    {0b11110011,0b11110000},
    {0b11110000,0b11110000},
    {0b11110000,0b00110000},
    {0b00000000,0b00000000},
    {0b11000000,0b11110000},
    {0b11111111,0b11110000},
};