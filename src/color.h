#ifndef __COLOR_H
#define __COLOR_H

class Color {
    public:
        Color();
        Color( int r, int g, int b, int a );
        Color( int r, int g, int b );
        int r, g, b, a;
        int Value();
};

#endif
