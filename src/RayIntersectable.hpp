#ifndef RAY_INTERSECTABLE_HPP
#define RAY_INTERSECTABLE_HPP
#include "RayIntersectableBasic.hpp"



class Plane: public RayIntersectableBasic {
public:
    Vector3D base_point = {0, 0, 0};
    Vector3D normal_vec = {1, 0, 0};
    Plane(const Vector3D& base_point, const Vector3D& normal_vec) : base_point(base_point), normal_vec(normal_vec.normalize()) {}
    Plane() {};
    static Plane planeByTriangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);
    
    double   intersect(const Ray& ray);
    Vector3D get_normal(const Ray& ray, double distance);
    Vector3D projectionPointPlane(const Vector3D& point, const Plane& plane);
    double   distance_to_base_point(const Vector3D& vec);

};

class Triangle: public RayIntersectableBasic {
public:
    Vector3D v1_, v2_, base_point_, normal_;
            
    Triangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);

    double   intersect(const Ray& ray);
    Vector3D get_normal(const Ray& ray, double distance);

    double area();
    bool     is_in_triangle(Vector3D vec);
    double   distance_to_base_point(const Vector3D& vec);
    double   distToPlane(const Vector3D& vec);
};

class Sphere: public RayIntersectableBasic {
    Vector3D base_point =  {0, 0, 0};
    double radius = 1;
    Sphere(const Vector3D& base_point, double radius) : base_point(base_point), radius(radius) {}

    double   intersect(const Ray& ray);
    Vector3D get_normal(const Ray& ray, double distance);
    double   distance_to_base_point(const Vector3D& vec);
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