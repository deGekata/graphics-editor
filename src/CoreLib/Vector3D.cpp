#include "Vector3D.hpp"

Vector3D operator+(const Vector3D& lft, const Vector3D& other) { return Vector3D(lft) += other; }

Vector3D operator-(const Vector3D& lft, const Vector3D& other) { return Vector3D(lft) -= other; }

Vector3D operator*(const Vector3D& vec, double num) { return Vector3D(vec) *= num; }
Vector3D operator*(double num, const Vector3D& vec) { return Vector3D(vec) *= num; }

Vector3D operator/(const Vector3D& vec, double num) { return Vector3D(vec) /= num; }
Vector3D operator/(double num, const Vector3D& vec) { return Vector3D(vec) /= num; }


bool is_zero(double num) {
    return fabs(num) < EPS;
}

double scalarMult(const Vector3D& lft, const Vector3D& rht) {
    return lft.x_*rht.x_ + lft.y_*rht.y_ + lft.z_*rht.z_;
}

Vector3D vectorMult(const Vector3D& a, const Vector3D& b) {
    return Vector3D(
         (a.y_*b.z_) - (a.z_*b.y_),
        -(a.x_*b.z_) + (a.z_*b.x_),
         (a.x_*b.y_) - (a.y_*b.x_)
    );
}

// double distToLine(const Vector3D& point, const Line& line) {
//     return  (line.base_point - point - line.direction * (scalarMult(line.base_point, line.direction) - scalarMult(point, line.direction)) / scalarMult(line.direction, line.direction)).length();
// }

double triangleArea(const Vector3D& v1, const Vector3D& v2) {
    return Vector3D(v1.y_*v2.z_ - v1.z_*v2.y_, -(v1.x_*v2.z_) + (v1.z_*v2.x_), (v1.x_*v2.y_ - v1.y_*v2.x_)).length();
}

// Plane planeByTriangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3) {
//     Vector3D normal_vec = {
//         (v2.y_ - v1.y_) * (v3.z_ - v1.z_) - (v2.z_ - v1.z_) * (v3.y_ - v1.y_),
//        -(v2.x_ - v1.x_) * (v3.z_ - v1.z_) + (v2.z_ - v1.z_) * (v3.x_ - v1.x_),
//         (v2.x_ - v1.x_) * (v3.y_ - v1.y_) - (v2.y_ - v1.y_) * (v3.x_ - v1.x_)
//     };

//     return Plane(v1, normal_vec);
// }

// double distToPlane(const Vector3D& point, const Plane& plane) {
//     return fabs(scalarMult(point - plane.base_point, plane.normal_vec));
// }

// Vector3D projectionPointPlane(const Vector3D& point, const Plane& plane) {
//     return point - plane.normal_vec / plane.normal_vec.length() * distToPlane(point, plane);
// }

// Intersection intersectLinePlane(const Line& line, const Plane& plane) {
//     if (is_zero(scalarMult(line.direction, plane.normal_vec))) return {Vector3D(), 0, .exist = false};
//     double dist_to_plane = distToPlane(line.base_point, plane);
//     double scale =  dist_to_plane / fabs(scalarMult(line.direction, plane.normal_vec));
//     if (distToPlane(line.base_point + line.direction * scale / 2, plane) > dist_to_plane) {
//         return {Vector3D(), 0, false};
//     }

//     return {
//         plane.normal_vec * -scalarMult(line.direction, plane.normal_vec),
//         scale,
//         true
//     };
// }

// Intersection intersectLineTriangle(const Line& line, const Triangle& triangle) {
//     Intersection intersect = intersectLinePlane(line, planeByTriangle(triangle.v1, triangle.v2, triangle.v3));
//     Vector3D inter_point = line.base_point + line.direction * intersect.distance;
//     if (intersect.exist) {
//         Vector3D p1 = inter_point - triangle.v1;
//         Vector3D p2 = inter_point - triangle.v2;
//         Vector3D p3 = inter_point - triangle.v3;
//         double area = triangleArea(triangle.v1 - triangle.v2, triangle.v1 - triangle.v3) - triangleArea(p1, p2) - triangleArea(p2, p3) - triangleArea(p3, p1);
//         if (is_zero(area)) {
//             return intersect;
//         }
//     }
//     intersect.exist = false;
//     return intersect;
// }

// Intersection intersectLineSphere(const Line& line, const Sphere& sphere) {
//     Vector3D base_point_to_center = sphere.base_point - line.base_point;
//     double dist_to_height = scalarMult(base_point_to_center, line.direction); // dist from line begin to intersection of height and line
//     double dist_to_line = scalarMult(base_point_to_center, base_point_to_center) - dist_to_height*dist_to_height;//square dist from sphere center to line
//     if (dist_to_line > sphere.radius*sphere.radius) {
//         return {Vector3D(), 0, false};
//     }

//     double inside_sphere_dist = sqrt(sphere.radius*sphere.radius - dist_to_line);

//     if ((dist_to_height - inside_sphere_dist) > 0.001) return {
//         line.direction * (dist_to_height - inside_sphere_dist) - base_point_to_center,
//                 ,
//         true
//     };

//     if ((dist_to_height + inside_sphere_dist) > 0.001) return {
//         line.direction * (dist_to_height + inside_sphere_dist) - base_point_to_center,
//         inside_sphere_dist,
//         true
//     };

//     return {Vector3D(), 0, false};
// }

// double distToSphere(const Vector3D& point, const Vector3D& radius, const Vector3D& base_point);
