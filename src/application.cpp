#include "SDL.h"

#include "application.h"

bool Application::running = true;
Application *Application::_instance = 0;

Application::Application() {}

Application * Application::Instance()
{
    if( !_instance )
    {
        _instance = new Application;
        Input::Instance()->ConnectCallback( _instance );
    }
    return _instance;
}

/* Call this instead of exit(), so we can clean up SDL: atexit() is evil. */
void Application::Quit( int return_code )
{
    running = false;
    exit( return_code );
}

void Application::InputCallbackFunction( int input_type )
{
    if( input_type == INPUT_QUIT )
    {
        Quit( 0 );
    }
}
