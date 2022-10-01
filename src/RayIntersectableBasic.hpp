#ifndef RAY_INTERSECTABLE_BASIC_HPP
#define RAY_INTERSECTABLE_BASIC_HPP
#include "Vector3D.hpp"
#include "Utilities.hpp"


class Ray {
public:
    Ray(const Vector3D& base_point, const Vector3D& direction) : base_point_(base_point), direction_(direction.normalize()) {}
    Ray(Ray&& other) : base_point_(other.base_point_), direction_(other.direction_) {}
    Vector3D base_point_ = {0, 0, 0};
    Vector3D direction_  = {1, 0, 0};
};



class RayIntersectableBasic {
public:
    virtual double   intersect(const Ray& ray) = 0;
    virtual double   distance_to_base_point(const Vector3D& vec) = 0;
    virtual Vector3D get_normal(const Ray& ray, double distance) = 0;
    bool is_light_source_ = false;
    double albedo_ = 1.0;   
    // double spread_ = 
    ColorF color_ = ColorF(255, 255, 255, 255);
};

struct Intersection
{
    RayIntersectableBasic* obj_ptr = nullptr;
    double distance = INFINITY;
};

#endif