#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <math.h>
#include <iostream>


class Point {
    public:
    Point(double x = 0, double y = 0) : x_(x), y_(y) {
        // std::cout << "constr " << x << "  " << y << '\n';
    };

    Point rotate(double rotation_angle) {
        double cos_angle = cos(rotation_angle);
        double sin_angle = sin(rotation_angle);
        return Point(x_ * cos_angle - y_ * sin_angle, x_ * sin_angle + y_ * cos_angle);
    }

    Point move(double dx, double dy) {
        x_ += dx;
        y_ += dy;
        return *this;
    }

    Point operator+(const Point& rht) const {
        return Point(x_ + rht.x_, y_ + rht.y_);
    }

    Point operator-(const Point& rht) const {
        return Point(x_ - rht.x_, y_ - rht.y_);
    }

    Point operator*(double rht) const {
        return Point(x_ * rht, y_ * rht);
    }

    Point operator/(double rht) const {
        return Point(x_ / rht, y_ / rht);
    }

    Point normalize() {
        double norm = sqrt(x_ * x_ + y_ * y_);
        return Point (x_ / norm, y_ / norm);
    }

    friend Point operator-(const Point& point);
    friend Point operator+(const Point& point);

    friend std::ostream& operator<<(std::ostream& out, const Point& point);

    ~Point() = default;
    double x_, y_;
};


class Rect {
public:
    Rect(Point p1, Point p2) : Rect(p1.x_, p1.y_, p2.x_, p2.y_) {};
    Rect(double x1, double y1, double x2, double y2) {
        p1_ = {x1, y1};
        p2_ = {x2, y2};
    }
    
    ~Rect() = default;
    Point p1_ = {0, 0}, p2_ = {0, 0};
};


std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << '\t' << point.x_ << '\t' << point.y_;
    return out;
}



Point operator-(const Point& point) {
    return Point(-point.x_, -point.y_);
}

Point operator+(const Point& point) {
    return point;
}

class Transformation {
public:
    Transformation() {
        m12_ = m13_ = m21_ = m23_ = m31_ = m32_ = 0;
        m11_ = m22_ = m33_ = 1;
    }
    Transformation(int dx, int dy, double rotate_angle) {
        m11_ = cos(rotate_angle) , m12_ = -sin(rotate_angle), m13_ = dx,
        m21_ = -m12_             , m22_ = m11_              , m23_ = dy,
        m31_ = 0                 , m32_ = 0                 , m33_ = 1;        
    };

    Transformation(const Point& delta, double rotate_angle): Transformation(delta.x_, delta.y_, rotate_angle) {}

    // Transformation(Point point, double rotate_angle = 0) : Transformation(point.x_,   {}

    Transformation(double m11, double m12, double m13,
                   double m21, double m22, double m23, 
                   double m31 = 0, double m32 = 0, double m33 = 1):
                    m11_(m11),  m12_(m12),   m13_(m13),
                    m21_(m21),  m22_(m22),   m23_(m23),
                    m31_(m31),  m32_(m32),   m33_(m33) {}

    
    Transformation(int dx, int dy)                      : m13_(dx), m23_(dy)                              {};
    // Transformation(double rotate_angle)                 :                   rotate_angle_(rotate_angle) {};


    Transformation operator*(const Transformation& other) {
        return Transformation(
            m11_ * other.m11_ + m12_ * other.m21_ + m13_ * other.m31_, m11_ * other.m12_ + m12_ * other.m22_ + m13_ * other.m32_, m11_ * other.m13_ + m12_ * other.m23_ + m13_ * other.m33_,
            m21_ * other.m11_ + m22_ * other.m21_ + m23_ * other.m31_, m21_ * other.m12_ + m22_ * other.m22_ + m23_ * other.m32_, m21_ * other.m13_ + m22_ * other.m23_ + m23_ * other.m33_,
            m31_ * other.m11_ + m32_ * other.m21_ + m33_ * other.m31_, m31_ * other.m12_ + m32_ * other.m22_ + m33_ * other.m32_, m31_ * other.m13_ + m32_ * other.m23_ + m33_ * other.m33_
        );
    }

    Point operator*(const Point& other) {
        return Point(m11_ * other.x_ + m12_ * other.y_ + m13_, m21_ * other.x_ + m22_ * other.y_ + m23_);
    }

    void print() {
        printf("\t%lf\t%lf\t%lf\n", m11_, m12_, m13_);
        printf("\t%lf\t%lf\t%lf\n", m21_, m22_, m23_);
        printf("\t%lf\t%lf\t%lf", m31_, m32_, m33_);
        return;
    }

    friend std::ostream& operator<<(std::ostream& out, const Transformation& other);

    double  m11_, m12_, m13_,
            m21_, m22_, m23_,
            m31_, m32_, m33_;
};

std::ostream& operator<<(std::ostream& out, const Transformation& other) {
    out << '\t' << other.m11_ << '\t' << other.m12_ << '\t' << other.m13_ << '\n';
    out << '\t' << other.m21_ << '\t' << other.m22_ << '\t' << other.m23_ << '\n';
    out << '\t' << other.m31_ << '\t' << other.m32_ << '\t' << other.m33_;
    return out;
}




#endif