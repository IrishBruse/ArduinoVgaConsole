#include <Arduino.h>
static u32 rand_next = 53451;

static u32 rng()
{
    rand_next = rand_next * 1103515245UL + 12345;
    return rand_next + ((unsigned)(rand_next / 65536) % 32768);
}

static u8 rng(u8 range)
{
    return (u8)(rng() % range);
}
