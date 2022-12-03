#ifndef GRAPHICS_GEOMETRY_ITEM_HPP
#define GRAPHICS_GEOMETRY_ITEM_HPP

#include "GraphicsItem.hpp"
#include "Utilities/Utilities.hpp""
//CRINGE
class GraphicsGeometryItem : public GraphicsItem {
public:
    GraphicsGeometryItem(GraphicsItem* item = NULL) : GraphicsItem(item) {};
    virtual ~GraphicsGeometryItem() {};

    // virtual bool hasCollision(const GraphicsGeometryItem& other);
    
    
    
    PointF rel_pos_ = {0, 0};


};


#endif