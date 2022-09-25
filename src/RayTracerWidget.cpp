#include "RayTracerWidget.hpp"





RayTracerWidget::RayTracerWidget
(
    double FOV, 
    const Rect& rect, 
    const Point& point, 
    Widget* parent=nullptr
):
    Widget(rect, point, parent)
{
    if (is_zero(FOV - M_PI)) throw;
    FOV_ = FOV;
    recalc_view_plane_dist();

}


RayTracerWidget::RayTracerWidget(
    const Rect& rect, 
    const Point& point, 
    Widget* parent=nullptr
): 
    Widget(rect, point, parent)
{
    FOV_ = M_PI / 2;
    recalc_view_plane_dist();
}

// RayTracerWidget::
// RayTracerWidget::
// RayTracerWidget::
// RayTracerWidget::
// RayTracerWidget::
// RayTracerWidget::



double RayTracerWidget::recalc_view_plane_dist() {
    view_plane_dist_ = tan(M_PI - 2.0 * FOV_) * (rect_.p2_.x_ - rect_.p1_.x_);

}