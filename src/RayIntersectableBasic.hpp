#include "Vector3D.hpp"



struct Intersection
{
    Vector3D normal = {1, 1, 1};
    double distance = 0;
    bool exist = false;
};

class Ray {
public:
    Ray(const Vector3D& base_point, const Vector3D& direction) : base_point(base_point), direction(direction.normalize()) {}
    Vector3D base_point = {0, 0, 0};
    Vector3D direction  = {1, 0, 0};
};



class RayIntersectableBasic {
public:
    virtual double intersect(const Ray&) = 0;
    double a = NAN;
};

