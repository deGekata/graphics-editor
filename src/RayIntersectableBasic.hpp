#ifndef RAY_INTERSECTABLE_BASIC_HPP
#define RAY_INTERSECTABLE_BASIC_HPP
#include "Vector3D.hpp"
#include "Utilities.hpp"
#include "Material.h"

class Ray {
public:
    Ray(const Vector3D& base_point, const Vector3D& direction) : base_point_(base_point), direction_(direction.normalize()) {}
    Ray(Ray&& other) : base_point_(other.base_point_), direction_(other.direction_) {}
    Vector3D base_point_ = {0, 0, 0};
    Vector3D direction_  = {1, 0, 0};
};



class RayIntersectableBasic {
public:
    RayIntersectableBasic(const Vector3D& base_point) : base_point_(base_point) {};
    virtual double   intersect(const Ray& ray) = 0;
    virtual double   distance_to_base_point(const Vector3D& vec) = 0;
    virtual Vector3D get_normal(const Ray& ray, double distance) = 0;
    virtual Vector3D get_direction(Vector3D point) = 0;
    virtual bool     is_inside(const Vector3D& point) = 0;
    bool is_light_source_ = false;
    Material material;
    double intensity = 1; 
    // double spread_ = 

    Vector3D base_point_ = {0, 0, 0};
};  

struct Intersection
{
    RayIntersectableBasic* obj_ptr = nullptr;
    double distance = INFINITY;
};

#endif