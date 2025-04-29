#pragma once

struct Sprite
{
    int srcX;
    int srcY;
    int width;
    int height;

    Sprite(int x = 0, int y = 0, int w = 0, int h = 0)
        : srcX(x), srcY(y), width(w), height(h) {
    }
};
