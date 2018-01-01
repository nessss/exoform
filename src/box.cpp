#include "box.h"
#include "sprite_defines.h"

Box::Box()
{
    bounds = Rect( 0, 0, 0, 0 );
    border_color = Color( 0xff, 0xff, 0xff );
    fill_color = Color( 0x90, 0x90, 0x90 );
    bg_color = Color( 0x30, 0x30, 0x30 );
    needs_render = true;
}

Box::Box(
        Rect bounds,
        Color border_color,
        Color fill_color,
        Color bg_color,
        int fill,
        int vertical_style,
        int horizontal_style )
{
    this->bounds = bounds;
    this->border_color = border_color;
    this->fill_color = fill_color;
    this->bg_color = bg_color;
    this->fill = fill;
    this->vertical_style = vertical_style;
    this->horizontal_style = horizontal_style;
    this->needs_render = true;
}

Box::Box(
        int x,
        int y,
        int w,
        int h,
        Color border_color,
        Color fill_color,
        Color bg_color,
        int fill,
        int vertical_style,
        int horizontal_style )
{
    this->bounds = Rect( x, y, w, h );
    this->border_color = border_color;
    this->fill_color = fill_color;
    this->bg_color = bg_color;
    this->fill = fill;
    this->vertical_style = vertical_style;
    this->horizontal_style = horizontal_style;
    this->needs_render = true;
}

bool Box::NeedsRenderCallback()
{
    bool r_val = needs_render;
    needs_render = false;
    return r_val;
}

void Box::DrawCallback()
{
    // these refer to the directions the lines point, not the positions,
    // so ul_char will end up in the bottom right corner
    Uint8 ul_char, ur_char, dl_char, dr_char, h_char, v_char;

    switch( horizontal_style )
    {
        case LINE_STYLE_NONE:
            h_char = fill;
            break;
        case LINE_STYLE_SINGLE:
            h_char = SPRITE_BOX_LIGHT_H;
            break;
        case LINE_STYLE_DOUBLE:
            h_char = SPRITE_BOX_LIGHT_HH;
            break;
    }

    switch( vertical_style )
    {
        case LINE_STYLE_NONE:
            v_char = fill;
            switch( horizontal_style )
            {
                case LINE_STYLE_NONE:
                    ul_char = fill;
                    ur_char = fill;
                    dl_char = fill;
                    dr_char = fill;
                    break;
                case LINE_STYLE_SINGLE:
                    ul_char = SPRITE_BOX_LIGHT_H;
                    ur_char = SPRITE_BOX_LIGHT_H;
                    dl_char = SPRITE_BOX_LIGHT_H;
                    dr_char = SPRITE_BOX_LIGHT_H;
                    break;
                case LINE_STYLE_DOUBLE:
                    ul_char = SPRITE_BOX_LIGHT_HH;
                    ur_char = SPRITE_BOX_LIGHT_HH;
                    dl_char = SPRITE_BOX_LIGHT_HH;
                    dr_char = SPRITE_BOX_LIGHT_HH;
                    break;
            }
            break;
        case LINE_STYLE_SINGLE:
            v_char = SPRITE_BOX_LIGHT_V;
            switch( horizontal_style )
            {
                case LINE_STYLE_NONE:
                    dr_char = SPRITE_BOX_LIGHT_V;
                    dl_char = SPRITE_BOX_LIGHT_V;
                    ur_char = SPRITE_BOX_LIGHT_V;
                    ul_char = SPRITE_BOX_LIGHT_V;
                    break;
                case LINE_STYLE_SINGLE:
                    dr_char = SPRITE_BOX_LIGHT_D_R;
                    dl_char = SPRITE_BOX_LIGHT_D_L;
                    ur_char = SPRITE_BOX_LIGHT_U_R;
                    ul_char = SPRITE_BOX_LIGHT_U_L;
                    break;
                case LINE_STYLE_DOUBLE:
                    dr_char = SPRITE_BOX_LIGHT_D_RR;
                    dl_char = SPRITE_BOX_LIGHT_D_LL;
                    ur_char = SPRITE_BOX_LIGHT_U_RR;
                    ul_char = SPRITE_BOX_LIGHT_U_LL;
                    break;
            }
            break;
        case LINE_STYLE_DOUBLE:
            v_char = SPRITE_BOX_LIGHT_VV;
            switch( horizontal_style )
            {
                case LINE_STYLE_NONE:
                    ul_char = SPRITE_BOX_LIGHT_VV;
                    ur_char = SPRITE_BOX_LIGHT_VV;
                    dl_char = SPRITE_BOX_LIGHT_VV;
                    dr_char = SPRITE_BOX_LIGHT_VV;
                    break;
                case LINE_STYLE_SINGLE:
                    dr_char = SPRITE_BOX_LIGHT_DD_R;
                    dl_char = SPRITE_BOX_LIGHT_DD_L;
                    ur_char = SPRITE_BOX_LIGHT_UU_R;
                    ul_char = SPRITE_BOX_LIGHT_UU_L;
                    break;
                case LINE_STYLE_DOUBLE:
                    dr_char = SPRITE_BOX_LIGHT_DD_RR;
                    dl_char = SPRITE_BOX_LIGHT_DD_LL;
                    ur_char = SPRITE_BOX_LIGHT_UU_RR;
                    ul_char = SPRITE_BOX_LIGHT_UU_LL;
                    break;
            }
            break;
    }

    int i, j;
    if( background )
    {
        for( i = 0; i < bounds.w; ++i )
        {
            for( j = 0; j < bounds.h; ++j )
            {
                Graphics::Instance()->DrawSpriteAtPosition( SPRITE_FULL_BLOCK, bounds.x + i, bounds.y + j, bg_color );
            }
        }
    }

    /* UL corner */
    Graphics::Instance()->DrawSpriteAtPosition( dr_char, bounds.x, bounds.y, border_color );
    /* UR corner */
    Graphics::Instance()->DrawSpriteAtPosition( dl_char, bounds.x + bounds.w - 1, bounds.y, border_color );
    /* DL corner */
    Graphics::Instance()->DrawSpriteAtPosition( ur_char, bounds.x, bounds.y + bounds.h - 1, border_color );
    /* DR corner */
    Graphics::Instance()->DrawSpriteAtPosition( ul_char, bounds.x + bounds.w - 1, bounds.y + bounds.h - 1, border_color );

    /* top edge */
    for( i = 1; i < bounds.w - 1; ++i )
    {
        Graphics::Instance()->DrawSpriteAtPosition( h_char, bounds.x + i, bounds.y, border_color );
    }

    /* bottom edge */
    for( i = 1; i < bounds.w - 1; ++i )
    {
        Graphics::Instance()->DrawSpriteAtPosition( h_char, bounds.x + i, bounds.y + bounds.h - 1, border_color );
    }

    /* left edge */
    for( i = 1; i < bounds.h - 1; ++i )
    {
        Graphics::Instance()->DrawSpriteAtPosition( v_char, bounds.x, bounds.y + i, border_color );
    }

    /* right edge */
    for( i = 1; i < bounds.h - 1; ++i )
    {
        Graphics::Instance()->DrawSpriteAtPosition( v_char, bounds.x + bounds.w - 1, bounds.y + i, border_color );
    }

    for( i = 1; i < bounds.w - 1; ++i )
    {
        for( j = 1; j < bounds.h - 1; ++j )
        {
            Graphics::Instance()->DrawSpriteAtPosition( fill, bounds.x + i, bounds.y + j, fill_color );
        }
    }
}

int Box::GetRenderLayer()
{
    return render_layer;
}

int Box::SetRenderLayer( int render_layer )
{
    this->render_layer = render_layer;
    return render_layer;
}

std::string Box::GetName()
{
    return "box";
}
