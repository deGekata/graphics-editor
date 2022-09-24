#ifndef GRAPHICS_SCENE_HPP
#define GRAPHICS_SCENE_HPP

#include "Painter.hpp"
#include "GraphicsItem.hpp"
#include <vector> //FIX: delete this shiiiiiiit

// is Used for storing graphical objects and painting them with Painter

class GraphicsScene {
public:
    std::vector<GraphicsItem*> items;
    int repaint(Painter* painter) {
        if (painter == NULL) return 1;
        
        for (size_t it = 0; it < items.size(); ++it) {
            items[it]->paint(painter);
        }

        return 0;
    }
};



#endif