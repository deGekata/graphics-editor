#include "Utilities.hpp"



PointF operator-(const PointF& point) {
    return PointF(-point.x_, -point.y_);
}

PointF operator+(const PointF& point) {
    return point;
}


std::ostream& operator<<(std::ostream& out, const PointF& point) {
    out << '\t' << point.x_ << '\t' << point.y_;
    return out;
}

Point operator-(const Point& point) {
    return Point(-point.x_, -point.y_);
}

Point operator+(const Point& point) {
    return point;
}


std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << '\t' << point.x_ << '\t' << point.y_;
    return out;
}

Transformation operator*(double num, const Transformation& m) {
    return Transformation(
        m.m11_ * num, m.m12_ * num, m.m13_ * num,
        m.m21_ * num, m.m22_ * num, m.m23_ * num,
        m.m31_ * num, m.m32_ * num, m.m33_ * num
    );
}

std::ostream& operator<<(std::ostream& out, const Transformation& other) {
    out << '\t' << other.m11_ << '\t' << other.m12_ << '\t' << other.m13_ << '\n';
    out << '\t' << other.m21_ << '\t' << other.m22_ << '\t' << other.m23_ << '\n';
    out << '\t' << other.m31_ << '\t' << other.m32_ << '\t' << other.m33_;
    return out;
}

Transformation transformOnParent(const PointF& parent_delta_coords, double rotation_angle) {
    return Transformation(parent_delta_coords, -rotation_angle);
}

PointF mapOnParent(const PointF& point, const PointF& parent_delta_coords, double rotation_angle) {
    Transformation transformation(parent_delta_coords, -rotation_angle);
    return transformation * point;
}