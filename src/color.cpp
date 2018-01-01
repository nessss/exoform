#include "color.h"

Color::Color()
{
    this->r = 0xff;
    this->g = 0xff;
    this->b = 0xff;
    this->a = 0xff;
}

Color::Color( int r, int g, int b, int a )
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color( int r, int g, int b )
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 0xff;
}

int Color::Value()
{
    return ( r << 24 ) + ( g << 16 ) + ( b << 8 ) + a;
}
