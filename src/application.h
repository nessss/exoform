#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "input.h"

class Application : InputCallbackInterface {
    public:
        static Application * Instance();
        static bool running;
        static void Quit( int return_code );
        void InputCallbackFunction( int input_type );
        
    private:
        Application();
        static Application *_instance;
};

#endif
