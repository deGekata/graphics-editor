#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <math.h>
#include <iostream>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define SWAP(T, a, b) do { T tmp = a; a = b; b = tmp; } while (0)

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

    double len() {
        return sqrt(x_ * x_ + y_ * y_);
    }

    friend Point operator-(const Point& point);
    friend Point operator+(const Point& point);

    friend std::ostream& operator<<(std::ostream& out, const Point& point);

    ~Point() = default;
    double x_, y_;
};


class Rect {
public:
    Rect() {};
    Rect(Point p1, Point p2) : Rect(p1.x_, p1.y_, p2.x_, p2.y_) {};
    Rect(double x1, double y1, double x2, double y2) {
        p1_ = {MIN(x1, x2), MIN(y1, y2)};
        p2_ = {MAX(x1, x2), MAX(y1, y2)};
    }
    
    static Rect min_rect(const Rect& bounds, Rect sample, Point move_rect) {
        Rect res;
        if (move_rect.x_ < 0 || move_rect.x_ > bounds.p2_.x_) {
            move_rect.x_ = 0;
        }

        if (move_rect.y_ < 0 || move_rect.y_ > bounds.p2_.y_) {
            move_rect.y_ = 0;
        }

        sample.p1_ = sample.p1_ + move_rect;
        sample.p2_ = sample.p2_ + move_rect;

        if (sample.p1_.x_ < bounds.p1_.x_ ||  bounds.p2_.x_ < sample.p1_.x_) {
            res.p1_.x_ = bounds.p1_.x_;
        }

        if (sample.p2_.x_ < bounds.p1_.x_ ||  bounds.p2_.x_ < sample.p2_.x_) {
            res.p2_.x_ = bounds.p2_.x_;
        }

        if (sample.p1_.y_ < bounds.p1_.y_ ||  bounds.p2_.y_ < sample.p1_.y_) {
            res.p1_.y_ = bounds.p1_.y_;
        }

        if (sample.p2_.y_ < bounds.p1_.y_ ||  bounds.p2_.y_ < sample.p2_.y_) {
            res.p2_.y_ = bounds.p2_.y_;
        }

        return res;
    }

    ~Rect() = default;
    Point p1_ = {0, 0}, p2_ = {0, 0};
};


std::ostream& operator<<(std::ostream& out, const Point& point);

Point operator-(const Point& point);

Point operator+(const Point& point);

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

    double det() {
        return m11_*m22_*m33_ + m12_*m23_*m31_ + m13_*m21_*m32_ - m13_*m22_*m31_ - m11_*m23_*m32_ - m12_*m21_*m33_;
    }

    Transformation inverse() {
        return (1/det()) * Transformation(m22_*m33_ - m23_*m32_   , -(m12_*m33_ - m13_*m32_), m12_*m23_ - m13_*m22_   ,
                                          -(m21_*m33_ - m23_*m31_), m11_*m33_ - m13_*m31_   , -(m11_*m23_ - m13_*m21_),
                                          m21_*m32_ - m22_*m31_   , -(m11_*m32_ - m12_*m31_),  m11_*m22_ - m12_*m21_);
    }

    Transformation operator*(const Transformation& other) {
        return Transformation(
            m11_ * other.m11_ + m12_ * other.m21_ + m13_ * other.m31_, m11_ * other.m12_ + m12_ * other.m22_ + m13_ * other.m32_, m11_ * other.m13_ + m12_ * other.m23_ + m13_ * other.m33_,
            m21_ * other.m11_ + m22_ * other.m21_ + m23_ * other.m31_, m21_ * other.m12_ + m22_ * other.m22_ + m23_ * other.m32_, m21_ * other.m13_ + m22_ * other.m23_ + m23_ * other.m33_,
            m31_ * other.m11_ + m32_ * other.m21_ + m33_ * other.m31_, m31_ * other.m12_ + m32_ * other.m22_ + m33_ * other.m32_, m31_ * other.m13_ + m32_ * other.m23_ + m33_ * other.m33_
        );
    }

    Transformation operator*(double num) {
        return Transformation(
            m11_ * num, m12_ * num, m13_ * num,
            m21_ * num, m22_ * num, m23_ * num,
            m31_ * num, m32_ * num, m33_ * num
        );
    }

    friend Transformation operator*(double num, const Transformation& m);

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

Transformation operator*(double num, const Transformation& m);

std::ostream& operator<<(std::ostream& out, const Transformation& other);

Transformation transformOnParent(const Point& parent_delta_coords, double rotation_angle);

Point mapOnParent(const Point& point, const Point& parent_delta_coords, double rotation_angle);


class ColorF {
public:
    explicit ColorF(double r, double g, double b, double a=1) {
        r = fabs(r), r =  r > 1.0 ? 1 : r;
        g = fabs(g), g =  g > 1.0 ? 1 : g;
        b = fabs(b), b =  b > 1.0 ? 1 : b;
        a = fabs(a), a =  a > 1.0 ? 1 : a;
        r_=r, g_=g, b_=b, a_=a;
    }

    ColorF(int r, int g, int b, int a=255) {
        r_ = (r & 255) / 255;
        g_ = (g & 255) / 255;
        b_ = (b & 255) / 255;
        a_ = (a & 255) / 255;
    }

    ColorF(const ColorF& other) {
        r_=other.r_, g_=other.g_, b_=other.b_, a_=other.a_;
    }

    const ColorF& operator*=(const ColorF& other) {
        r_ *= other.r_, g_ *=other.g_, b_ *= other.b_, a_ *= other.a_;
        return *this;
    }

    ColorF operator*(const ColorF& other) {
        return ColorF(*this) *= other;
    }

    const ColorF& operator+=(const ColorF& other) {
        r_ += other.r_, g_ +=other.g_, b_ += other.b_, a_ += other.a_;
        return *this;
    }

    ColorF operator+(const ColorF& other) {
        return ColorF(*this) += other;
    }

    const ColorF& operator*=(double num) {
        r_ *= num, g_ *= num, b_ *= num, a_ *= num;
        return *this;
    }

    ColorF operator*(double num) {
        return ColorF(*this) *= num;
    }


    double r_=0, g_=0, b_=0, a_=1;
};


#endif