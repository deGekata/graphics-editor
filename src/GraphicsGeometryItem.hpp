#ifndef GRAPHICS_GEOMETRY_ITEM_HPP
#define GRAPHICS_GEOMETRY_ITEM_HPP

#include "GraphicsItem.hpp"
#include "Utilities.hpp"

class GraphicsGeometryItem : public GraphicsItem {
public:
    virtual ~GraphicsGeometryItem() {};

    virtual bool hasCollision(const GraphicsGeometryItem& other);
    
    
    
    


};


#endif