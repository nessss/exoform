#ifndef __CURSOR_H
#define __CURSOR_H

#include <utility>
#include <string>
#include "input.h"
#include "graphics.h"
#include "rect.h"
#include "sprite_defines.h"

class Cursor : public InputCallbackInterface, public RenderableInterface {
    public:
        Cursor();
        std::pair< int, int > GetPosition();
        std::pair< int, int > SetPosition( std::pair< int, int > *new_position );
        std::pair< int, int > SetPosition( int x, int y );
        Rect * GetBounds();
        Rect * SetBounds( Rect *new_bounds );
        void InputCallbackFunction( int input_type );
        bool NeedsRenderCallback();
        Color color;

        void DrawCallback();
        int GetRenderLayer();
        int SetRenderLayer( int render_layer );
        std::string GetName();
    private:
        int MoveX( int delta );
        int MoveY( int delta );
        std::pair< int, int > position;
        Rect bounds;
        bool needs_render;
        int render_layer;
};

#endif
