#include <Arduino.h>
#include <ezButton.h>
#include <VGAX.h>
#include "point.h"
// #include "images.h"

#define JoyX A5
#define JoyY A4
typedef unsigned long long u64;

byte col = 0;

ezButton joyButton(2);

Point player;
Point enemies[16];

u8 oldx = 0;
u8 oldy = 0;

unsigned int lastMove = 0;

void setup()
{

    VGAX::begin();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, 0);

    joyButton.setDebounceTime(50);

    for (int y = 0; y != VGAX_HEIGHT; y++)
    {
        for (int x = 0; x != VGAX_WIDTH; x++)
        {
            if (x == 0 || x == VGAX_WIDTH - 1 || y == 0 || y == VGAX_HEIGHT - 1)
            {
                VGAX::putpixel(x, y, 1);
            }
            else
            {
                VGAX::putpixel(x, y, 0);
            }
        }
    }
}

void loop()
{
    u16 jx = analogRead(JoyX);
    u16 jy = analogRead(JoyY);

    if (VGAX::millis() - lastMove > 16)
    {
        if (jx > 512 + 256)
        {
            lastMove = VGAX::millis();
            player.x--;
        }
        else if (jx < 512 - 256)
        {
            lastMove = VGAX::millis();
            player.x++;
        }

        if (jy > 512 + 256)
        {
            lastMove = VGAX::millis();
            player.y++;
        }
        else if (jy < 512 - 256)
        {
            lastMove = VGAX::millis();
            player.y--;
        }
    }

    player.loop();
}

static u32 rand_next = 1;

u32 rng()
{
    rand_next = rand_next * 1103515245UL + 12345;
    return rand_next + ((unsigned)(rand_next / 65536) % 32768);
}

u8 rng(u8 range)
{
    return (u8)(random() % range);
}
