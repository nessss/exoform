#include "cursor.h"

Cursor::Cursor()
{
    color = Color( 0xff, 0xff, 0xff );
    Input::Instance()->ConnectCallback( this );
}

std::pair< int, int > Cursor::GetPosition()
{
    return position;
}

std::pair< int, int > Cursor::SetPosition( std::pair< int, int > *new_position )
{
    position = *new_position;
    return position;
}

std::pair< int, int > Cursor::SetPosition( int x, int y )
{
    std::pair< int, int > new_position = std::pair< int, int > ( x, y );
    SetPosition( &new_position );
    return position;
}

Rect * Cursor::GetBounds()
{
    return &bounds;
}

Rect * Cursor::SetBounds( Rect *new_bounds )
{
    bounds = *new_bounds;
    return &bounds;
}

void Cursor::InputCallbackFunction( int input_type )
{
    switch( input_type )
    {
        case INPUT_CURSOR_LEFT:
            MoveX( -1 );
            break;
        case INPUT_CURSOR_DOWN:
            MoveY( 1 );
            break;
        case INPUT_CURSOR_UP:
            MoveY( -1 );
            break;
        case INPUT_CURSOR_RIGHT:
            MoveX( 1 );
            break;
        case INPUT_CURSOR_UP_LEFT:
            MoveX( -1 );
            MoveY( -1 );
            break;
        case INPUT_CURSOR_UP_RIGHT:
            MoveX( 1 );
            MoveY( -1 );
            break;
        case INPUT_CURSOR_DOWN_LEFT:
            MoveX( -1 );
            MoveY( 1 );
            break;
        case INPUT_CURSOR_DOWN_RIGHT:
            MoveX( 1 );
            MoveY( 1 );
            break;
    }

    needs_render = true;
}

bool Cursor::NeedsRenderCallback()
{
    bool r_val = needs_render;
    needs_render = false;
    return r_val;
}

void Cursor::DrawCallback()
{
    Graphics::Instance()->DrawSpriteAtPosition( SPRITE_MEDIUM_SHADE, position.first, position.second, color );
}

int Cursor::GetRenderLayer()
{
    return render_layer;
}

int Cursor::SetRenderLayer( int render_layer )
{
    this->render_layer = render_layer;
    return this->render_layer;
}

std::string Cursor::GetName()
{
    return "cursor";
}

int Cursor::MoveX( int delta )
{
    int original_x = position.first;
    position.first += delta;
    if( position.first + bounds.x > bounds.x + bounds.w )
    {
        position.first = bounds.x + bounds.w;
    }
    else if( position.first + bounds.x < bounds.x )
    {
        position.first = bounds.x;
    }

    return position.first - original_x;
}

int Cursor::MoveY( int delta )
{
    int original_y = position.second;
    position.second += delta;
    if( position.second + bounds.y > bounds.y + bounds.h )
    {
        position.second = bounds.y + bounds.h;
    }
    else if( position.second + bounds.y < bounds.y )
    {
        position.second = bounds.y;
    }

    return position.second - original_y;
}
