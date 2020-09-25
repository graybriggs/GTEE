#ifndef LAYER_SELECTION_H
#define LAYER_SELECTION_H

#include "tile_map_render.h"



class LayerSelection {

public:
    LayerSelection(TileMapRender& tmr);
    virtual ~LayerSelection();

private:
    TileMapRender& tileMapRender;
};


#endif // LAYER_SELECTION_H
