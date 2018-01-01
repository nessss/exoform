#include "rect.h"

Rect::Rect()
{
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
}

Rect::Rect( int x, int y, int w, int h )
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}
