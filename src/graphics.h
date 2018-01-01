#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include <string>
#include <vector>
#include "SDL.h"
#include "color.h"

#define WINDOW_CHAR_WIDTH 60
#define WINDOW_CHAR_HEIGHT 60
#define NUM_SPRITES 256
#define SPRITE_WIDTH 12
#define SPRITE_HEIGHT 12
#define SHEET_WIDTH 192
#define SHEET_HEIGHT 192
#define BG_R 0x30
#define BG_G 0x30
#define BG_B 0x30

#define LINE_STYLE_NONE    0x00
#define LINE_STYLE_SINGLE  0x01
#define LINE_STYLE_DOUBLE  0x02

class RenderableInterface {
    public:
        virtual bool NeedsRenderCallback() = 0;
        virtual void DrawCallback() = 0;
        virtual int GetRenderLayer() = 0;
        virtual int SetRenderLayer( int render_layer ) = 0;
        virtual std::string GetName() = 0;
};

class Graphics {

    private:
        Graphics();
        std::vector< RenderableInterface * > renderables;
        static Graphics *_instance;
        SDL_Renderer *renderer;

        SDL_Texture *sprite_sheet;
        SDL_Rect sheet_positions[NUM_SPRITES];
        
        Color bg_color, draw_color;

        void SetupSheetPositions();
        int CharToSpriteIndex( char c );
        static bool SortRenderables( RenderableInterface *lhs, RenderableInterface *rhs );

        void LogSortedRenderableNames();

    public:
        static Graphics * Instance();
        int LoadSpriteSheet( const char *file );

        void AddRenderable( RenderableInterface *renderable );
        void RemoveRenderable( RenderableInterface *renderable );

        void DrawSpriteAtPosition( int sprite_index, int x, int y, Color color );

        void SetBackgroundColor( Color color );
        void SetBackgroundColor( int r, int g, int b, int a );
        Color GetBackgroundColor();

        void SetDrawColor( Color color );
        void SetDrawColor( int r, int g, int b, int a );
        Color GetDrawColor();

        void ClearScreen();
        void RenderFrame();
};

#endif
