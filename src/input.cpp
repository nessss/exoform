#include "input.h"
#include "application.h"
#include "graphics.h"

std::set< InputCallbackInterface * > Input::callbacks;
Input *Input::_instance = 0;

Input * Input::Instance()
{
    if( !_instance )
    {
        _instance = new Input;
    }
    return _instance;
}

Input::Input() {}

bool Input::ConnectCallback( InputCallbackInterface *cb )
{
    bool return_value = callbacks.insert( cb ).second;
    return return_value;
}

bool Input::DisconnectCallback( InputCallbackInterface *cb )
{
    return callbacks.erase( cb ) > 0;
}

void Input::Loop()
{
    while( Application::running )
    {
        SDL_Event event;

        /* Check for events */
        while( SDL_PollEvent( &event ) )
        {
            int input_type = 0;

            if( event.type == SDL_QUIT )
            {
                input_type = INPUT_QUIT;
            }
            else if( event.type == SDL_KEYDOWN )
            {
                switch( event.key.keysym.sym )
                {
                    case SDLK_h:
                        input_type = INPUT_CURSOR_LEFT;
                        break;
                    case SDLK_j:
                        input_type = INPUT_CURSOR_DOWN;
                        break;
                    case SDLK_k:
                        input_type = INPUT_CURSOR_UP;
                        break;
                    case SDLK_l:
                        input_type = INPUT_CURSOR_RIGHT;
                        break;
                    case SDLK_y:
                        input_type = INPUT_CURSOR_UP_LEFT;
                        break;
                    case SDLK_u:
                        input_type = INPUT_CURSOR_UP_RIGHT;
                        break;
                    case SDLK_b:
                        input_type = INPUT_CURSOR_DOWN_LEFT;
                        break;
                    case SDLK_n:
                        input_type = INPUT_CURSOR_DOWN_RIGHT;
                        break;
                    case SDLK_w:
                        input_type = INPUT_SEC_CURSOR_UP;
                        break;
                    case SDLK_a:
                        input_type = INPUT_SEC_CURSOR_LEFT;
                        break;
                    case SDLK_s:
                        input_type = INPUT_SEC_CURSOR_DOWN;
                        break;
                    case SDLK_d:
                        input_type = INPUT_SEC_CURSOR_RIGHT;
                        break;
                    case SDLK_RETURN:
                    case SDLK_RETURN2:
                    case SDLK_KP_ENTER:
                        input_type = INPUT_CONFIRM;
                        break;
                    case SDLK_ESCAPE:
                        input_type = INPUT_CANCEL;
                        break;
                }
            }

            for( auto it = callbacks.begin(); it != callbacks.end(); ++it )
            {
                (*it)->InputCallbackFunction( input_type );
            }

            Graphics::Instance()->RenderFrame();
        }
    }
}
