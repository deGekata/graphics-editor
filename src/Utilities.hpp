#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <math.h>

class Rect {
public:
    Rect(int x = 0, int y = 0) : x_(x), y_(y) {};
    ~Rect() = default;
    int x_, y_ = 0;
};

class Point {
    public:
    Point(int x = 0, int y = 0) : x_(x), y_(y) {};

    Point rotate(double rotation_angle) {
        double cos_angle = cos(rotation_angle);
        double sin_angle = sin(rotation_angle);
        return Point(x_ * cos_angle - y_ * sin_angle, x_ * sin_angle + y_ * cos_angle);
    }

    Point move(int dx, int dy) {
        x_ += dx;
        y_ += dy;
        return *this;
    }

    Point transform(int dx, int dy, double rotation_angle) {
        return rotate(rotation_angle).move(dx, dy);
    }

    Point operator+(const Point& rht) const {
        return Point(x_ + rht.x_, y_ + rht.y_);
    }



    ~Point() = default;
    int x_ = 0, y_ = 0;
};


class Transformation {
public:
    Transformation(int dx, int dy, double rotate_angle) {
        m11_ = cos(rotate_angle) , m12_ = -sin(rotate_angle), m13_ = dx,
        m21_ = -m12_             , m22_ = m11_              , m22_ = dy,
        m31_ = 0                 , m32_ = 0                 , m33_ = 1;        
    };

    Transformation(Point point, double rotate_angle = 0) : Transformation(point.x_,  ){}

    Transformation(double m11, double m12, double m13,
                   double m21, double m22, double m23, 
                   double m31, double m32, double m33):
                    m11_(m11),  m12_(m12),   m13_(m13),
                    m21_(m21),  m22_(m22),   m23_(m23),
                    m31_(m31),  m32_(m32),   m33_(m33) {}

    
    Transformation(int dx, int dy)                      : dx_(dx), dy_(dy)                              {};
    Transformation(double rotate_angle)                 :                   rotate_angle_(rotate_angle) {};


    Transformation operator*(const Transformation& other) {
        return Transformation(
            m11_
        )
    }

    double  m11_, m12_, m13_,
            m21_, m22_, m23_,
            m31_, m32_, m33_;
    int dx_ = 0, dy_ = 0;
};



#endif