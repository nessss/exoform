#include <list>
#include <algorithm>

#include "sprite_defines.h"
#include "graphics.h"
#include "application.h"

#include <iostream>

Graphics *Graphics::_instance = 0;

Graphics::Graphics()
{
    SDL_Window *window;

    /* Enable standard application logging */
    SDL_LogSetPriority( SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO );

    if( SDL_CreateWindowAndRenderer(
                WINDOW_CHAR_WIDTH * SPRITE_WIDTH,
                WINDOW_CHAR_HEIGHT * SPRITE_HEIGHT,
                0,
                &window,
                &renderer ) < 0 )
    {
        std::cerr << "SDL_CreateWindowAndRenderer failed: ";
        std::cerr << SDL_GetError() << std::endl;
        Application::Quit( 2 );
    }

    if( LoadSpriteSheet( "sprite_sheet.bmp" ) < 0 )
    {
        std::cerr << "LoadSpriteSheet failed: ";
        std::cerr << SDL_GetError() << std::endl;
        Application::Quit( 2 );
    }

    SetupSheetPositions();

    SetBackgroundColor( 0x30, 0x30, 0x30, 0xff );

    /* TODO: make this a static member of perhaps the Application class
    border_params.x = 0;
    border_params.y = 0;
    border_params.w = WINDOW_CHAR_WIDTH;
    border_params.h = WINDOW_CHAR_HEIGHT;
    border_params.vertical_style = LINE_STYLE_DOUBLE;
    border_params.horizontal_style = LINE_STYLE_SINGLE;
    border_params.background = true;
    // --------------------------------------------------------------*/
}

Graphics * Graphics::Instance()
{
    if( _instance == NULL )
    {
        _instance = new Graphics;
    }

    return _instance;
}

int Graphics::LoadSpriteSheet( const char *file )
{
    SDL_Surface *temp;

    /* Load the sprite sheet */
    temp = SDL_LoadBMP( file );
    if( temp == NULL )
    {
        SDL_LogError(
                SDL_LOG_CATEGORY_APPLICATION,
                "Couldn't load %s: %s\n",
                file, SDL_GetError() );
        return (-1);
    }

    /* Set transparent pixel as the pixel at (0,0) */
    if( temp->format->palette )
    {
        SDL_SetColorKey( temp, SDL_TRUE, *(Uint8 *) temp-> pixels );
    }
    else
    {
        switch( temp->format->BitsPerPixel )
        {
            case 8:
                SDL_SetColorKey(
                        temp,
                        SDL_TRUE,
                        ( *(Uint8 *) temp->pixels ) & 0x000000FF );
                break;
            case 15:
                SDL_SetColorKey(
                        temp,
                        SDL_TRUE,
                        ( *(Uint16 *) temp->pixels ) & 0x00007FFF );
                break;
            case 16:
                SDL_SetColorKey(
                        temp,
                        SDL_TRUE,
                        *(Uint16 *) temp->pixels );
                break;
            case 24:
                SDL_SetColorKey(
                        temp,
                        SDL_TRUE,
                        ( *(Uint32 *) temp->pixels ) & 0x00FFFFFF );
                break;
            case 32:
                SDL_SetColorKey(
                        temp,
                        SDL_TRUE,
                        *(Uint32 *) temp->pixels );
                break;
        }
    }

    /* Create textures from the image */
    sprite_sheet = SDL_CreateTextureFromSurface( renderer, temp );
    if( !sprite_sheet )
    {
        SDL_LogError(
                SDL_LOG_CATEGORY_APPLICATION,
                "Couldn't create texture; %s\n",
                SDL_GetError() );
        SDL_FreeSurface( temp );
        return (-1);
    }

    SDL_FreeSurface( temp );

    return (0);
}

void Graphics::AddRenderable( RenderableInterface *renderable )
{
    for( auto it = renderables.begin(); it != renderables.end(); ++it )
    {
        if( *it == renderable )
        {
            return;
        }
    }

    renderables.push_back( renderable );
    std::sort( renderables.begin(), renderables.end(), Graphics::SortRenderables );
}

void Graphics::LogSortedRenderableNames()
{
    std::string sorted_names;

    for( auto it = renderables.begin(); it != renderables.end(); ++it )
    {
        sorted_names.append( (*it)->GetName() );
        sorted_names.append( " " );
    }

    SDL_LogInfo( SDL_LOG_CATEGORY_TEST, "render order: %s", sorted_names.c_str() );
}

bool Graphics::SortRenderables( RenderableInterface *lhs, RenderableInterface *rhs )
{
    return lhs->GetRenderLayer() < rhs->GetRenderLayer();
}

void Graphics::SetupSheetPositions()
{
    int i;
    for( i = 0; i < NUM_SPRITES; ++i )
    {
        sheet_positions[i].x = ( ( SPRITE_WIDTH * i ) % SHEET_WIDTH );
        sheet_positions[i].y = ( ( SPRITE_HEIGHT ) * ( i / 16 ) );
        sheet_positions[i].w = SPRITE_WIDTH;
        sheet_positions[i].h = SPRITE_HEIGHT;
    }
}

void Graphics::DrawSpriteAtPosition( int sprite_index, int x, int y, Color color )
{
    SDL_Rect position;

    position.x = x * SPRITE_WIDTH;
    position.y = y * SPRITE_HEIGHT;

    position.w = SPRITE_WIDTH;
    position.h = SPRITE_HEIGHT;

    SetDrawColor( color );

    SDL_RenderCopy( renderer, sprite_sheet, &sheet_positions[sprite_index], &position );
}

/*
void Graphics::DrawBox( BoxParameters *params )
{
    DrawBox( params, &draw_color );
}

void Graphics::DrawBox( BoxParameters *params, Color *color )
{

    SDL_SetTextureColorMod( sprite_sheet, draw_color.r, draw_color.g, draw_color.b );
}
*/

/*
void Graphics::DrawBorder()
{
    DrawBox( &border_params );
}
*/

/*
void Graphics::DrawString( const char *content, BoxParameters *box_params, Color *box_color, Color *text_color )
{
    std::string s ( content );
    DrawString( &s, box_params, box_color, text_color );
}

void Graphics::DrawString( std::string *content, BoxParameters *box_params, Color *box_color, Color *text_color )
{
    int text_x, text_y, text_w, text_h;

    // text should print at the edges of the box, so if there are borders,
    // set up the text box position and size so it won't overlap them, but
    // if there are no edges, print text at the edge of the box.
    if( box_params->vertical_style == LINE_STYLE_NONE )
    {
        text_x = box_params->x;
        text_w = box_params->w;
    }
    else
    {
        text_x = box_params->x + 1;
        text_w = box_params->w - 2;
    }

    if( box_params->horizontal_style == LINE_STYLE_NONE )
    {
        text_y = box_params->y;
        text_h = box_params->h;
    }
    else
    {
        text_y = box_params->y + 1;
        text_h = box_params->h - 2;
    }

    DrawBox( box_params, box_color );

    // break the text into lines, preserving word boundaries so words aren't
    // split between lines
    std::list< std::string > lines;
    std::string word;
    std::string line;

    for( auto it = content->begin(); it != content->end(); ++it )
    {
        if( *it == ' ' )
        {
            if( word.length() > 0 )
            {
                if( (int) (line.length() + word.length() + 1) > text_w )
                {
                    lines.push_back( line );
                    line.clear();
                }
                if( line.size() > 0 )
                {
                    line.append( " " );
                }
                line.append( word );
                word.clear();
            }
        }
        else
        {
            word.append( 1, *it );
            ++it;
            if( it == content->end() )
            {
                if( (int) (line.length() + word.length() + 1) > text_w )
                {
                    lines.push_back( line );
                    line.clear();
                }
                if( line.size() > 0 )
                {
                    line.append( " " );
                }
                line.append( word );
                word.clear();
            }
            --it;
        }
    }

    // append the last line if we haven't already
    if( line != lines.back() )
    {
        lines.push_back( line );
    }

    // draw the text
    SDL_SetTextureColorMod( sprite_sheet, text_color->r, text_color->g, text_color->b );
    int line_number = 0;
    for( auto line_it = lines.begin(); line_it != lines.end(); ++line_it )
    {
        for( int char_number = 0; char_number < (int) (*line_it).length(); ++char_number )
        {
            DrawSpriteAtPosition(
                    (int) (*line_it)[char_number],
                    text_x + char_number,
                    text_y + line_number );
        }
        ++line_number;
    }
}
*/

int Graphics::CharToSpriteIndex( char c )
{
    // turns out it's as simple as this
    return (int) c;
}

void Graphics::SetBackgroundColor( Color color )
{
    bg_color = color;
}

void Graphics::SetBackgroundColor( int r, int g, int b, int a )
{
    bg_color.r = r;
    bg_color.g = g;
    bg_color.b = b;
    bg_color.a = a;
}

Color Graphics::GetBackgroundColor()
{
    return bg_color;
}

void Graphics::SetDrawColor( Color color )
{
    draw_color = color;
    SDL_SetTextureColorMod( sprite_sheet, color.r, color.g, color.b );
}

void Graphics::SetDrawColor( int r, int g, int b, int a )
{
    draw_color.r = r;
    draw_color.g = g;
    draw_color.b = b;
    draw_color.a = a;

    SDL_SetTextureColorMod( sprite_sheet, r, g, b );
}

Color Graphics::GetDrawColor()
{
    return draw_color;
}

void Graphics::ClearScreen()
{
    SDL_SetRenderDrawColor( renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a );
    SDL_RenderClear( renderer );
}

void Graphics::RenderFrame()
{
    bool needs_redraw = false;

    for( auto it = renderables.begin(); it != renderables.end(); ++it )
    {
        if( (*it)->NeedsRenderCallback() )
        {
            needs_redraw = true;
            break;
        }
    }

    if( !needs_redraw ) return;

    ClearScreen();

    for( auto it = renderables.begin(); it != renderables.end(); ++it )
    {
        (*it)->DrawCallback();
    }

    SDL_RenderPresent( renderer );
}
