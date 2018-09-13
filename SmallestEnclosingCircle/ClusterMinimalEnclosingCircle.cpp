//
// Created by Dung Phan on 9/12/18.
// Copyright ® https://www.nayuki.io/page/smallest-enclosing-circle
//

#include "ClusterMinimalEnclosingCircle.h"

//-------------------------------------------------------------------------------------------------------
Point Point::subtract(const Point &p) const {
    return Point{x - p.x, y - p.y};
}

double Point::distance(const Point &p) const {
    return std::hypot(x - p.x, y - p.y);
}

double Point::cross(const Point &p) const {
    return x * p.y - y * p.x;
}

//-------------------------------------------------------------------------------------------------------
const Circle Circle::INVALID{Point{0, 0}, -1};

const double Circle::MULTIPLICATIVE_EPSILON = 1 + 1e-14;

bool Circle::contains(const Point &p) const {
    return c.distance(p) <= r * MULTIPLICATIVE_EPSILON;
}

bool Circle::contains(const std::vector<Point> &ps) const {
    for (const Point &p : ps) {
        if (!contains(p))
            return false;
    }
    return true;
}

//-------------------------------------------------------------------------------------------------------
ClusterMinimalEnclosingCircle::ClusterMinimalEnclosingCircle() {
    kPoints.clear();
}

// Initially: No boundary points known
Circle ClusterMinimalEnclosingCircle::MakeSmallestEnclosingCircle(const std::vector<Point> &points) {
    static std::default_random_engine randGen((std::random_device())());

    // Clone list to preserve the caller's data, randomize order
    std::vector<Point> shuffled = points;
    std::shuffle(shuffled.begin(), shuffled.end(), randGen);

    // Progressively add points to circle or recompute circle
    Circle c(Circle::INVALID);
    for (size_t i = 0; i < shuffled.size(); i++) {
        const Point &p = shuffled.at(i);
        if (c.r < 0 || !c.contains(p))
            c = MakeSmallestEnclosingCircleOnePoint(shuffled, i + 1, p);
    }
    return c;
}

// One boundary point known
Circle ClusterMinimalEnclosingCircle::MakeSmallestEnclosingCircleOnePoint(const std::vector<Point> &points, size_t end, const Point &p) {
    Circle c{p, 0};
    for (size_t i = 0; i < end; i++) {
        const Point &q = points.at(i);
        if (!c.contains(q)) {
            if (c.r == 0)
                c = MakeDiameter(p, q);
            else
                c = MakeSmallestEnclosingCircleTwoPoints(points, i + 1, p, q);
        }
    }
    return c;
}

// Two boundary points known
Circle ClusterMinimalEnclosingCircle::MakeSmallestEnclosingCircleTwoPoints(const std::vector<Point> &points, size_t end, const Point &p, const Point &q) {
    Circle circ = MakeDiameter(p, q);
    Circle left = Circle::INVALID;
    Circle right = Circle::INVALID;

    // For each point not in the two-point circle
    Point pq = q.subtract(p);
    for (size_t i = 0; i < end; i++) {
        const Point &r = points.at(i);
        if (circ.contains(r))
            continue;

        // Form a circumcircle and classify it on left or right side
        double cross = pq.cross(r.subtract(p));
        Circle c = MakeCircumcircle(p, q, r);
        if (c.r < 0)
            continue;
        else if (cross > 0 && (left.r < 0 || pq.cross(c.c.subtract(p)) > pq.cross(left.c.subtract(p))))
            left = c;
        else if (cross < 0 && (right.r < 0 || pq.cross(c.c.subtract(p)) < pq.cross(right.c.subtract(p))))
            right = c;
    }

    // Select which circle to return
    if (left.r < 0 && right.r < 0)
        return circ;
    else if (left.r < 0)
        return right;
    else if (right.r < 0)
        return left;
    else
        return left.r <= right.r ? left : right;
}

Circle ClusterMinimalEnclosingCircle::MakeDiameter(const Point &a, const Point &b) {
    Point c{(a.x + b.x) / 2, (a.y + b.y) / 2};
    return Circle{c, std::max(c.distance(a), c.distance(b))};
}


Circle ClusterMinimalEnclosingCircle::MakeCircumcircle(const Point &a, const Point &b, const Point &c) {
    // Mathematical algorithm from Wikipedia: Circumscribed circle
    double ox = (std::min(std::min(a.x, b.x), c.x) + std::max(std::min(a.x, b.x), c.x)) / 2;
    double oy = (std::min(std::min(a.y, b.y), c.y) + std::max(std::min(a.y, b.y), c.y)) / 2;
    double ax = a.x - ox, ay = a.y - oy;
    double bx = b.x - ox, by = b.y - oy;
    double cx = c.x - ox, cy = c.y - oy;
    double d = (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)) * 2;
    if (d == 0)
        return Circle::INVALID;
    double x = ((ax * ax + ay * ay) * (by - cy) + (bx * bx + by * by) * (cy - ay) + (cx * cx + cy * cy) * (ay - by)) / d;
    double y = ((ax * ax + ay * ay) * (cx - bx) + (bx * bx + by * by) * (ax - cx) + (cx * cx + cy * cy) * (bx - ax)) / d;
    Point p{ox + x, oy + y};
    double r = std::max(std::max(p.distance(a), p.distance(b)), p.distance(c));
    return Circle{p, r};
}

void ClusterMinimalEnclosingCircle::SetPoints(std::vector<std::pair<double, double> > &points) {
    kPoints.clear();
    for (unsigned int i = 0; i < points.size(); i++) {
        double x = points.at(i).first;
        double y = points.at(i).second;
        kPoints.push_back(Point{x, y});
    }
}

double ClusterMinimalEnclosingCircle::GetMinimalEnclosingCircleArea() {
    kMinimalEnclosingCircle = MakeSmallestEnclosingCircle(kPoints);
    double radius = kMinimalEnclosingCircle.r;

    return Pi * radius * radius;
}

std::pair<double, double> ClusterMinimalEnclosingCircle::GetCircleOrigin() {
    kMinimalEnclosingCircle = MakeSmallestEnclosingCircle(kPoints);
    Point origin = kMinimalEnclosingCircle.c;

    return std::pair<double, double>(std::make_pair(origin.x, origin.y));
}

double ClusterMinimalEnclosingCircle::GetCircleRadius() {
    kMinimalEnclosingCircle = MakeSmallestEnclosingCircle(kPoints);

    return kMinimalEnclosingCircle.r;
}
