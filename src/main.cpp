#include <Arduino.h>
#include <VGAX.h>
#include <VGAXUtils.h>
#include "rng.h"
#include "sprites.h"

#define JoyX A5
#define JoyY A4

struct V2
{
    int8_t x = 0;
    int8_t y = 0;
};

constexpr u8 BLACK = 0;
constexpr u8 RED = 1;
constexpr u8 GREEN = 2;
constexpr u8 YELLOW = 3;

static int8_t vy = 1;
static V2 player;
static V2 prev;

constexpr int EnemiesCount = 1;
static V2 enemies[EnemiesCount] = {};

void setup()
{
    player.x = 5;
    player.y = 10;
    for (size_t i = 0; i < EnemiesCount; i++)
    {
        enemies[i].x = rng(VGAX_WIDTH - 20) + 20;
        enemies[i].y = 5;
    }

    VGAX::begin();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, 0);

    pinMode(12, INPUT_PULLUP);

    VGAXUtils::draw_row(VGAX_HEIGHT - 1, 0, VGAX_WIDTH, GREEN);
}

static u32 last = 0;
static u8 oldstate = 0;

void loop()
{
    u8 state = digitalRead(12);
    prev.x = player.x;
    prev.y = player.y;

    if (VGAX::millis() - last > 200)
    {
        for (size_t i = 0; i < EnemiesCount; i++)
        {
            VGAXUtils::draw_line(enemies[i].x + 9, 0, enemies[i].x + 9, 20, BLACK);

            enemies[i].x--;
        }

        player.y += vy;

        vy++;
        if (vy > 5)
        {
            vy = 5;
        }

        if (player.y > VGAX_HEIGHT - IMG_BIRD_HEIGHT - 1)
        {
            player.y = 5;
        }
        if (player.y < 0)
        {
            player.y = 0;
        }

        for (size_t i = 0; i < EnemiesCount; i++)
        {
            VGAX::fillrect(enemies[i].x, 0, 8, 20, GREEN);
        }

        VGAX::fillrect(prev.x, prev.y, IMG_BIRD_WIDTH, IMG_BIRD_HEIGHT, BLACK);
        VGAX::blitwmask((byte *)(img_bird_data[0]), (byte *)(img_bird_mask_data[0]), IMG_BIRD_WIDTH, IMG_BIRD_HEIGHT, player.x, player.y);

        last = VGAX::millis();
    }

    if (state == 1 && oldstate == 0)
    {
        vy = -5;
    }

    oldstate = state;
    VGAX::delay(10);
}
