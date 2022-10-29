#ifndef RAY_INTERSECTABLE_HPP
#define RAY_INTERSECTABLE_HPP
#include "RayIntersectableBasic.hpp"



class Plane: public RayIntersectableBasic {
public:
    Vector3D normal_ = {1, 0, 0};
    
    Plane(const Vector3D& base_point, const Vector3D& normal_vec) : RayIntersectableBasic(base_point), normal_(normal_vec.normalize()) {}

    static Plane planeByTriangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);
    
    double   intersect(const Ray& ray);
    Vector3D get_normal(const Ray& ray, double distance);
    Vector3D get_direction(Vector3D point);
    Vector3D projectionPointPlane(const Vector3D& point, const Plane& plane);
    double   distance_to_base_point(const Vector3D& vec);
    bool     is_inside(const Vector3D& point);
};

class Triangle: public RayIntersectableBasic {
public:
    Vector3D v1_, v2_, normal_;
            
    Triangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);

    double   intersect(const Ray& ray);
    Vector3D get_normal(const Ray& ray, double distance);
    Vector3D get_direction(Vector3D point);

    double area();
    bool     is_in_triangle(Vector3D vec);
    double   distance_to_base_point(const Vector3D& vec);
    double   distToPlane(const Vector3D& vec);
    bool     is_inside(const Vector3D& point);
};

class Sphere: public RayIntersectableBasic {
public:
    // Vector3D base_point_ =  {0, 0, 0};
    double radius = 1;
    Sphere(const Vector3D& base_point, double radius) : RayIntersectableBasic(base_point), radius(radius) {}

    double   intersect(const Ray& ray);
    Vector3D get_normal(const Ray& ray, double distance);
    Vector3D get_direction(Vector3D point);
    double   distance_to_base_point(const Vector3D& vec);
    bool     is_inside(const Vector3D& point    );
};


double scalarMult(const Vector3D& lft, const Vector3D& rht);

// double distToLine(const Vector3D& point, const Line& line);

double triangleArea(const Vector3D& v1, const Vector3D& v2);

// Plane planeByTriangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);

// double distToPlane(const Vector3D& point, const Plane& plane);

// Vector3D projectionPointPlane(const Vector3D& point, const Plane& plane);

// Intersection intersectLinePlane(const Line& line, const Plane& plane);

// Intersection intersectLineTriangle(const Line& line, const Triangle& triangle);

// Intersection intersectLineSphere(const Line& line, const Sphere& sphere);


double distToSphere(const Vector3D& point, const Vector3D& radius, const Vector3D& base_point);



#endif