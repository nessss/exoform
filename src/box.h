#ifndef __BOX_H
#define __BOX_H

#include <string>

#include "graphics.h"
#include "rect.h"

class Box : public RenderableInterface {
    public:
        Box();
        Box(
                Rect bounds,
                Color border_color,
                Color fill_color,
                Color bg_color,
                int fill,
                int vertical_style,
                int horizontal_style );

        Box( int x,
                int y,
                int w,
                int h,
                Color border_color,
                Color fill_color,
                Color bg_color,
                int fill,
                int vertical_style,
                int horizontal_style );

        Rect bounds;
        Color border_color, fill_color, bg_color;
        int fill;
        int vertical_style;
        int horizontal_style;
        bool background;

        bool NeedsRenderCallback();
        void DrawCallback();
        int GetRenderLayer();
        int SetRenderLayer( int render_layer );
        std::string GetName();
    private:
        bool needs_render;
        int render_layer;
};

#endif
