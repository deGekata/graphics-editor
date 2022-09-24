#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <cmath>
#include <iostream>

#define EPS 1e-6

class Vector3D {
public:

    Vector3D() {}
    Vector3D(double x, double y, double z) : x_(x), y_(y), z_(z) {
        update_length();
    };

    Vector3D(const Vector3D& sample) : x_(sample.x_), y_(sample.y_), z_(sample.z_), length_(sample.length_) {}
    
    double length() const {
        return length_;
    }

    Vector3D normalize() const {
        if (length_ == 0) throw;
        return Vector3D(x_ / length_, y_ / length_, z_ / length_);
    }

    const Vector3D& operator=(const Vector3D& sample) {
        x_ = sample.x_;
        y_ = sample.y_;
        z_ = sample.z_; 
        length_ = sample.length_;
        return *this;
    }

    const Vector3D& operator+=(const Vector3D& sample) {
        x_ += sample.x_;
        y_ += sample.y_;
        z_ += sample.z_;
        update_length();
        return *this;
    }    

    const Vector3D& operator-=(const Vector3D& sample) {
        x_ -= sample.x_;
        y_ -= sample.y_;
        z_ -= sample.z_;
        update_length();
        return *this;
    }    

    const Vector3D& operator*=(double num) {
        x_ *= num;
        y_ *= num;
        z_ *= num;
        update_length();
        return *this;
    }


    
    const Vector3D& operator/=(double num) {
        if (num == 0) throw;
        x_ /= num;
        y_ /= num;
        z_ /= num;
        update_length();
        return *this;
    }

    friend Vector3D operator+(const Vector3D& lft, const Vector3D& rht);

    friend Vector3D operator-(const Vector3D& lft, const Vector3D& rht);

    friend Vector3D operator*(const Vector3D& lft, double num);
    friend Vector3D operator*(double num, const Vector3D& lft);

    friend Vector3D operator/(const Vector3D& lft, double num);
    friend Vector3D operator/(double num, const Vector3D& lft);

    ~Vector3D() {};
    double x_ = 0, y_ = 0, z_ = 0, length_ = 0;

private:
    void update_length() {
        length_ = sqrt(x_*x_ + y_*y_ + z_*z_);
    }
};

Vector3D operator+(const Vector3D& lft, const Vector3D& other);

Vector3D operator-(const Vector3D& lft, const Vector3D& other);

Vector3D operator*(const Vector3D& vec, double num);
Vector3D operator*(double num, const Vector3D& vec);

Vector3D operator/(const Vector3D& vec, double num);
Vector3D operator/(double num, const Vector3D& vec);

bool is_zero(double num);

struct Intersection
{
    Vector3D normal = {1, 1, 1};
    double distance = 0;
    bool exist = false;
};

struct Line {
    Vector3D base_point = {0, 0, 0};
    Vector3D direction  = {1, 0, 0};
    Line(const Vector3D& base_point, const Vector3D& direction) : base_point(base_point), direction(direction.normalize()) {}
};

struct Plane {
    Vector3D base_point = {0, 0, 0};
    Vector3D normal_vec = {1, 0, 0};
    Plane(const Vector3D& base_point, const Vector3D& normal_vec) : base_point(base_point), normal_vec(normal_vec.normalize()) {}
    Plane() {};
};

struct Triangle {
    Vector3D v1, v2, v3;
};

struct Sphere {
    Vector3D base_point =  {0, 0, 0};
    double radius = 1;
    Sphere(const Vector3D& base_point, double radius) : base_point(base_point), radius(radius) {}
};

double scalarMult(const Vector3D& lft, const Vector3D& rht);

double distToLine(const Vector3D& point, const Line& line);

double triangleArea(const Vector3D& v1, const Vector3D& v2);

Plane planeByTriangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);

double distToPlane(const Vector3D& point, const Plane& plane);

Vector3D projectionPointPlane(const Vector3D& point, const Plane& plane);

Intersection intersectLinePlane(const Line& line, const Plane& plane);

Intersection intersectLineTriangle(const Line& line, const Triangle& triangle);

Intersection intersectLineSphere(const Line& line, const Sphere& sphere);


double distToSphere(const Vector3D& point, const Vector3D& radius, const Vector3D& base_point);




#endif