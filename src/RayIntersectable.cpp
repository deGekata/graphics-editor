#include <cmath>
#include <iostream>
#include <math.h>
#include "RayIntersectable.hpp"

#define EPS 1e-6



double Plane::intersect(const Ray& ray) {
    if (is_zero(scalarMult(ray.direction_, normal_))) return NAN;
    double dist_to_plane = distance_to_base_point(ray.base_point_);
    double scale =  dist_to_plane / fabs(scalarMult(ray.direction_, normal_));
    if (distance_to_base_point(ray.base_point_ + ray.direction_ * scale / 2) > dist_to_plane) {
        return NAN;
    }

    return scale;
}

double Plane::distance_to_base_point(const Vector3D& point) {
    return fabs(scalarMult(point - base_point_, normal_));
}

Vector3D Plane::get_normal(const Ray& ray, double distance) {
    if (isnan(distance)) return Vector3D();

    return normal_ * - scalarMult(ray.direction_, normal_);
}

Vector3D Plane::get_direction(Vector3D point) {
    return normal_ * scalarMult(base_point_ - point, normal_);
}

bool Plane::is_inside(const Vector3D& point) {
    return false;
}


Triangle::Triangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3) : RayIntersectableBasic(v1) {
    normal_ = {
        (v2.y_ - v1.y_) * (v3.z_ - v1.z_) - (v2.z_ - v1.z_) * (v3.y_ - v1.y_),
       -(v2.x_ - v1.x_) * (v3.z_ - v1.z_) + (v2.z_ - v1.z_) * (v3.x_ - v1.x_),
        (v2.x_ - v1.x_) * (v3.y_ - v1.y_) - (v2.y_ - v1.y_) * (v3.x_ - v1.x_)
    };
    normal_ = normal_.normalize();

    v1_ = v2 - v1;
    v2_ = v3 - v1;
}




double Triangle::intersect(const Ray& ray) {
    if (is_zero(scalarMult(ray.direction_, normal_))) return NAN;
    
    double dist_to_plane = distToPlane(ray.base_point_);
    double scale =  dist_to_plane / fabs(scalarMult(ray.direction_, normal_));
    if (is_in_triangle(ray.base_point_ + ray.direction_ * scale)) 
        return scale;

    return NAN;
}

double Triangle::distance_to_base_point(const Vector3D& vec) {
    Vector3D projection =  vec - normal_ * distToPlane(vec);
    return is_in_triangle(projection) ? distToPlane(vec) : NAN;
}

double Triangle::distToPlane(const Vector3D& vec) {
    return fabs(scalarMult(vec - base_point_, normal_));
}



Vector3D Triangle::get_normal(const Ray& ray, double distance) {
    if (isnan(distance)) return Vector3D();

    return normal_ * - scalarMult(ray.direction_, normal_);
}

Vector3D Triangle::get_direction(Vector3D point) {
    return normal_ * scalarMult(base_point_ - point, normal_);
}

bool Triangle::is_in_triangle(Vector3D vec) {
    vec = vec - base_point_;
    double vec_area = area() - triangleArea(vec, v1_) - triangleArea(vec, v2_) - triangleArea(v2_ - vec, v1_ - vec);
    if (is_zero(vec_area)) {
        return true;
    }
    return false;
}

double Triangle::area() {
    return triangleArea(v1_, v2_);
}

bool Triangle::is_inside(const Vector3D& point) {
    return false;
}


double Sphere::intersect(const Ray& ray) {
    Vector3D base_point_to_center = base_point_ - ray.base_point_;
    double dist_to_height = scalarMult(base_point_to_center, ray.direction_); // dist from line begin to intersection of height and line
    double dist_to_line = scalarMult(base_point_to_center, base_point_to_center) - dist_to_height*dist_to_height;//square dist from sphere center to line
    if (dist_to_line > radius*radius) {
        return NAN;
    }

    double inside_sphere_dist = sqrt(radius*radius - dist_to_line);

    if ((dist_to_height - inside_sphere_dist) > 0.001) return dist_to_height - inside_sphere_dist;

    if ((dist_to_height + inside_sphere_dist) > 0.001) return dist_to_height + inside_sphere_dist;

    return NAN;
}

double Sphere::distance_to_base_point(const Vector3D& vec) {
    return (vec - base_point_).length_ - radius;
}

Vector3D Sphere::get_normal(const Ray& ray, double distance) {
    if (isnan(distance)) return Vector3D();
    Vector3D norm = (ray.direction_ * distance - (base_point_ - ray.base_point_)).normalize();
    return norm * -scalarMult(norm, ray.direction_);
}

Vector3D Sphere::get_direction(Vector3D point) {
    return base_point_ - point;
}

bool Sphere::is_inside(const Vector3D& point) {
    return fabs((base_point_ - point).length()) < radius;
}

bool is_zero(double num);

// struct Intersection
// {
//     Vector3D normal = {1, 1, 1};
//     double distance = 0;
//     bool exist = false;
// };