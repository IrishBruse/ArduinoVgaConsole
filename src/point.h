#include <Arduino.h>
#include <VGAX.h>

class Point
{
public:
    u8 x = 60;
    u8 y = 30;
    u8 color = 2;

private:
    u8 oldx = 60;
    u8 oldy = 30;

public:
    void loop()
    {
        if (x < 1)
            x = 1;

        if (x > VGAX_WIDTH - 2)
            x = VGAX_WIDTH - 2;

        if (y < 1)
            y = 1;

        if (y > VGAX_HEIGHT - 2)
            y = VGAX_HEIGHT - 2;

        VGAX::putpixel(x, y, color);

        if (x != oldx || y != oldy)
        {
            VGAX::putpixel(oldx, oldy, 0);
        }

        oldx = x;
        oldy = y;
    }
};
