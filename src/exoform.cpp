#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include "SDL.h"

#include "sprite_defines.h"
#include "graphics.h"
#include "application.h"
#include "input.h"
#include "cursor.h"
#include "box.h"

int main( int /* argc */, char ** /* argv[] */ )
{

    Graphics::Instance();
    Input::Instance();
    Application::Instance();

    Cursor cursor;
    Rect cursor_bounds;
    cursor_bounds.x = 1;
    cursor_bounds.y = 1;
    cursor_bounds.w = WINDOW_CHAR_WIDTH - 2;
    cursor_bounds.h = WINDOW_CHAR_HEIGHT - 2;

    cursor.SetBounds( &cursor_bounds );

    cursor.SetRenderLayer( 1 );

    Graphics::Instance()->AddRenderable( &cursor );

    /*
    InputTest input_test_1;
    input_test_1.return_value = 1;
    Input::ConnectCallback( &input_test_1 ); 
    */

    Graphics::Instance()->ClearScreen();

    //Graphics::Instance()->SetDrawColor( 0x90, 0x90, 0x90, 0xff );

    //Graphics::Instance()->DrawBorder();

    Box test_box_1 (
            5,
            5,
            5,
            5,
            Color( 0xff, 0xff, 0xff ),
            Color( 0x90, 0x90, 0x90 ),
            Color( 0x30, 0x30, 0x30 ),
            SPRITE_LIGHT_SHADE,
            LINE_STYLE_DOUBLE,
            LINE_STYLE_DOUBLE );

    test_box_1.SetRenderLayer( 0 );

    Graphics::Instance()->AddRenderable( &test_box_1 );

    Box test_box_2 (
            15,
            5,
            10,
            10,
            Color( 0x80, 0x20, 0x00 ),
            Color( 0x80, 0x20, 0x00 ),
            Color( 0x30, 0x30, 0x30 ),
            SPRITE_LIGHT_SHADE,
            LINE_STYLE_SINGLE,
            LINE_STYLE_DOUBLE );

    test_box_1.SetRenderLayer( 0 );

    Graphics::Instance()->AddRenderable( &test_box_2 );

    /*
    Graphics::Instance()->SetDrawColor( 0x80, 0x20, 0x00, 0xff );

    BoxParameters test_box_2;

    test_box_2.x = 15;
    test_box_2.y = 5;
    test_box_2.w = 10;
    test_box_2.h = 10;
    test_box_2.horizontal_style = LINE_STYLE_DOUBLE;
    test_box_2.vertical_style = LINE_STYLE_SINGLE;
    test_box_2.fill = SPRITE_LIGHT_SHADE;

    Graphics::Instance()->DrawBox( &test_box_2 );

    Graphics::Instance()->SetDrawColor( 0x20, 0xa0, 0x70, 0xff );

    BoxParameters test_box_3;

    test_box_3.x = 20;
    test_box_3.y = 10;
    test_box_3.w = 10;
    test_box_3.h = 10;
    test_box_3.horizontal_style = LINE_STYLE_SINGLE;
    test_box_3.vertical_style = LINE_STYLE_DOUBLE;
    test_box_3.fill = SPRITE_LIGHT_SHADE;
    test_box_3.background = true;

    Graphics::Instance()->DrawBox( &test_box_3 );

    BoxParameters test_box_4;

    test_box_4.x = 40;
    test_box_4.y = 10;
    test_box_4.w = 15;
    test_box_4.h = 10;
    test_box_4.horizontal_style = LINE_STYLE_SINGLE;
    test_box_4.vertical_style = LINE_STYLE_DOUBLE;
    test_box_4.fill = SPRITE_BLANK;
    test_box_4.background = true;

    Color text_box_color;
    text_box_color.r = 0x90;
    text_box_color.g = 0x90;
    text_box_color.b = 0x90;

    Color text_color;
    text_color.r = 0x30;
    text_color.g = 0xb0;
    text_color.b = 0x30;

    Graphics::Instance()->DrawString( "This is a test. This string should print in a box.", &test_box_4, &text_box_color, &text_color );
    */

    Input::Loop();

    return 0;
}
