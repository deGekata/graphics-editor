#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <math.h>
#include <iostream>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define SWAP(T, a, b) do { T tmp = a; a = b; b = tmp; } while (0)

#define UNUSED(x) (void)(x)

class PointF {
    public:
    PointF(double x = 0, double y = 0) : x_(x), y_(y) {
        // std::cout << "constr " << x << "  " << y << '\n';
    };

    PointF rotate(double rotation_angle) {
        double cos_angle = cos(rotation_angle);
        double sin_angle = sin(rotation_angle);
        return PointF(x_ * cos_angle - y_ * sin_angle, x_ * sin_angle + y_ * cos_angle);
    }

    PointF move(double dx, double dy) {
        x_ += dx;
        y_ += dy;
        return *this;
    }

    PointF operator+(const PointF& rht) const {
        return PointF(x_ + rht.x_, y_ + rht.y_);
    }

    PointF operator-(const PointF& rht) const {
        return PointF(x_ - rht.x_, y_ - rht.y_);
    }

    PointF operator*(double rht) const {
        return PointF(x_ * rht, y_ * rht);
    }

    PointF operator/(double rht) const {
        return PointF(x_ / rht, y_ / rht);
    }

    PointF normalize() {
        double norm = sqrt(x_ * x_ + y_ * y_);
        return PointF (x_ / norm, y_ / norm);
    }

    double len() {
        return sqrt(x_ * x_ + y_ * y_);
    }

    friend PointF operator-(const PointF& point);
    friend PointF operator+(const PointF& point);

    friend std::ostream& operator<<(std::ostream& out, const PointF& point);

    ~PointF() = default;
    double x_, y_;
};

std::ostream& operator<<(std::ostream& out, const PointF& point);

PointF operator-(const PointF& point);

PointF operator+(const PointF& point);

class Point {
    public:
    Point(int x = 0, int y = 0) : x_(x), y_(y) {
        // std::cout << "constr " << x << "  " << y << '\n';
    };

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

    Point operator+(const Point& rht) const {
        return Point(x_ + rht.x_, y_ + rht.y_);
    }

    Point operator-(const Point& rht) const {
        return Point(x_ - rht.x_, y_ - rht.y_);
    }

    Point operator*(int rht) const {
        return Point(x_ * rht, y_ * rht);
    }

    Point operator/(int rht) const {
        return Point(x_ / rht, y_ / rht);
    }

    Point normalize() {
        int norm = sqrt(x_ * x_ + y_ * y_);
        return Point (x_ / norm, y_ / norm);
    }

    double len() {
        return sqrt(x_ * x_ + y_ * y_);
    }

    friend Point operator-(const Point& point);
    friend Point operator+(const Point& point);

    friend std::ostream& operator<<(std::ostream& out, const Point& point);

    ~Point() = default;
    int x_, y_;
};

std::ostream& operator<<(std::ostream& out, const PointF& point);

Point operator-(const Point& point);

Point operator+(const Point& point);

class RectF {
public:
    RectF() {};
    RectF(PointF point, PointF size) : RectF(point.x_, point.y_, size.x_, size.y_) {};
    RectF(double x, double y, double width, double height) {
        point_ = {x, y};
        size_  = {fabs(width), fabs(height)};
    }
    
    // static RectF min_rect(const RectF& bounds, RectF sample, PointF move_rect) {
    //     RectF res;
    //     if (move_rect.x_ < 0 || move_rect.x_ > bounds.p2_.x_) {
    //         move_rect.x_ = 0;
    //     }

    //     if (move_rect.y_ < 0 || move_rect.y_ > bounds.p2_.y_) {
    //         move_rect.y_ = 0;
    //     }

    //     sample.p1_ = sample.p1_ + move_rect;
    //     sample.p2_ = sample.p2_ + move_rect;

    //     if (sample.p1_.x_ < bounds.p1_.x_ ||  bounds.p2_.x_ < sample.p1_.x_) {
    //         res.p1_.x_ = bounds.p1_.x_;
    //     }

    //     if (sample.p2_.x_ < bounds.p1_.x_ ||  bounds.p2_.x_ < sample.p2_.x_) {
    //         res.p2_.x_ = bounds.p2_.x_;
    //     }

    //     if (sample.p1_.y_ < bounds.p1_.y_ ||  bounds.p2_.y_ < sample.p1_.y_) {
    //         res.p1_.y_ = bounds.p1_.y_;
    //     }

    //     if (sample.p2_.y_ < bounds.p1_.y_ ||  bounds.p2_.y_ < sample.p2_.y_) {
    //         res.p2_.y_ = bounds.p2_.y_;
    //     }

    //     return res;
    // }

    ~RectF() = default;
    PointF point_ = {0, 0}, size_ = {0, 0};
};

class Rect {
public:
    Rect() {};
    Rect(Point point, Point size) : Rect(point.x_, point.y_, size.x_, size.y_) {};
    Rect(int x, int y, int width, int height) {
        point_ = {x, y};
        size_ = {abs(width), abs(height)};
    }

    bool inRect(Point point) {
        if (point_.x_ <= point.x_ && 
            point_.y_ <= point.y_ && 
            (point_.x_ + size_.x_) >= point.x_ && 
            (point_.y_ + size_.y_) >= point.y_) 
        {
            return true;
        }
        return false;
    }
    
    /*static Rect min_rect(const Rect& bounds, Rect sample, Point move_rect) {
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
    }*/

    ~Rect() = default;
    Point point_ = {0, 0}, size_ = {0, 0};
};





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

    Transformation(const PointF& delta, double rotate_angle): Transformation(delta.x_, delta.y_, rotate_angle) {}

    // Transformation(PointF point, double rotate_angle = 0) : Transformation(point.x_,   {}

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

    PointF operator*(const PointF& other) {
        return PointF(m11_ * other.x_ + m12_ * other.y_ + m13_, m21_ * other.x_ + m22_ * other.y_ + m23_);
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

Transformation transformOnParent(const PointF& parent_delta_coords, double rotation_angle);

Transformation transformOnParent(const Point& parent_delta_coords, double rotation_angle);

PointF mapOnParent(const PointF& point, const PointF& parent_delta_coords, double rotation_angle);
PointF mapOnParent(const Point&  point, const Point&  parent_delta_coords, double rotation_angle);


class ColorF {
public:
    explicit ColorF() {};

    ColorF(double r, double g, double b, double a=1) {
        // r = fabs(r), r =  r_ > 1.0 ? 1 : r_;
        // g = fabs(g), g =  g_ > 1.0 ? 1 : g_;
        // b = fabs(b), b =  b_ > 1.0 ? 1 : b_;
        // a = fabs(a), a =  a_ > 1.0 ? 1 : a_;
        r_=r, g_=g, b_=b, a_=a;
    }

    explicit ColorF(int r, int g, int b, int a=255) {
        r_ = r / 255.0;
        g_ = g / 255.0;
        b_ = b / 255.0;
        a_ = a / 255.0;
    }

    ColorF(const ColorF& other) {
        r_=other.r_, g_=other.g_, b_=other.b_, a_=other.a_;
    }

    ColorF& operator=(const ColorF& other) {
        r_=other.r_, g_=other.g_, b_=other.b_, a_=other.a_;
        return *this;
    }

    ColorF& operator*=(const ColorF& other) {
        r_ *= other.r_, g_ *=other.g_, b_ *= other.b_, a_ *= other.a_;
        return *this;
    }

    ColorF operator*(const ColorF& other) {
        return ColorF(*this) *= other;
    }

    ColorF& operator+=(const ColorF& other) {
        r_ += other.r_, g_ +=other.g_, b_ += other.b_, a_ += other.a_;
        return *this;
    }

    ColorF operator+(const ColorF& other) {
        return ColorF(*this) += other;
    }

    ColorF& operator*=(double num) {
        r_ *= num, g_ *= num, b_ *= num, a_ *= num;
        return *this;
    }

    ColorF operator*(double num) {
        return ColorF(*this) *= num;
    }

    const ColorF& operator/=(double num) {
        r_ /= num, g_ /= num, b_ /= num, a_ /= num;
        return *this;
    }

    ColorF operator/(double num) {
        return ColorF(*this) /= num;
    }

    ColorF normalize() {
        return ColorF(
            sqrt(sqrt(r_ > 1.0 ? 1 : r_)),
            sqrt(sqrt(g_ > 1.0 ? 1 : g_)),
            sqrt(sqrt(b_ > 1.0 ? 1 : b_)),
            sqrt(sqrt(a_ > 1.0 ? 1 : a_))
        );
        // return ColorF(sqrt(r_), sqrt(g_), sqrt(b_));
    }

    ColorF inverse() {
        return ColorF(1- r_, 1 - g_, 1 - b_);
    }

    double r_=0, g_=0, b_=0, a_=1;
};


#endif