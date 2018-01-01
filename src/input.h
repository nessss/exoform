#ifndef __INPUT_H
#define __INPUT_H

#include <set>

#include "SDL.h"

class InputCallbackInterface {
    public:
        virtual void InputCallbackFunction( int ) = 0;
};

#define INPUT_CURSOR_UP             0x01
#define INPUT_CURSOR_DOWN           0x02
#define INPUT_CURSOR_LEFT           0x03
#define INPUT_CURSOR_RIGHT          0x04
#define INPUT_CURSOR_UP_LEFT        0x05
#define INPUT_CURSOR_UP_RIGHT       0x06
#define INPUT_CURSOR_DOWN_LEFT      0x07
#define INPUT_CURSOR_DOWN_RIGHT     0x08

#define INPUT_SEC_CURSOR_UP         0x09
#define INPUT_SEC_CURSOR_DOWN       0x0a
#define INPUT_SEC_CURSOR_LEFT       0x0b
#define INPUT_SEC_CURSOR_RIGHT      0x0c
#define INPUT_SEC_CURSOR_UP_LEFT    0x0d
#define INPUT_SEC_CURSOR_UP_RIGHT   0x0e
#define INPUT_SEC_CURSOR_DOWN_LEFT  0x0f
#define INPUT_SEC_CURSOR_DOWN_RIGHT 0x10

#define INPUT_CONFIRM               0x11
#define INPUT_CANCEL                0x12

#define INPUT_QUIT                  0x13

class Input {
    public:
        static Input *Instance();
        static bool ConnectCallback( InputCallbackInterface *cb );
        static bool DisconnectCallback( InputCallbackInterface *cb );
        static void Loop();

    private:
        Input();
        static Input *_instance;
        static std::set< InputCallbackInterface * > callbacks;
};

class InputTest : public InputCallbackInterface {
    public:
        int return_value;
        void InputCallbackFunction( int input_type )
        {
            switch( input_type )
            {
                case INPUT_CURSOR_UP:
                    SDL_Log( "input: cursor up" );
                    break;
                case INPUT_CURSOR_DOWN:
                    SDL_Log( "input: cursor down" );
                    break;
                case INPUT_CURSOR_LEFT:
                    SDL_Log( "input: cursor left" );
                    break;
                case INPUT_CURSOR_RIGHT:
                    SDL_Log( "input: cursor right" );
                    break;
                case INPUT_CONFIRM:
                    SDL_Log( "input: confirm" );
                    break;
                case INPUT_CANCEL:
                    SDL_Log( "input: cancel" );
                    break;

            }
        }
};

#endif
