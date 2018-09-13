//
// Created by Dung Phan on 9/12/18.
// Copyright ® https://www.nayuki.io/page/smallest-enclosing-circle
//

#ifndef SMALLESTENCLOSINGCIRCLE_CLUSTERMINIMALENCLOSINGCIRCLE_H
#define SMALLESTENCLOSINGCIRCLE_CLUSTERMINIMALENCLOSINGCIRCLE_H

#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <random>

struct Point final {
    double x;
    double y;

    Point subtract(const Point &p) const;
    double distance(const Point &p) const;

    // Signed area / determinant thing
    double cross(const Point &p) const;
};


struct Circle final {
public:
    static const Circle INVALID;
    Point c;
    double r;

    bool contains(const Point &p) const;
    bool contains(const std::vector<Point> &ps) const;

private:
    static const double MULTIPLICATIVE_EPSILON;
};

class ClusterMinimalEnclosingCircle {
public:
    ClusterMinimalEnclosingCircle();
    virtual ~ClusterMinimalEnclosingCircle() = default;

    const double Pi = 3.1415926535;
    virtual void SetPoints(std::vector< std::pair<double, double> > & points);

    // GETs
    virtual double GetMinimalEnclosingCircleArea();
    virtual std::pair<double, double> GetCircleOrigin();
    virtual double GetCircleRadius();

private:
    std::vector<Point> kPoints;
    Circle kMinimalEnclosingCircle;

    static Circle MakeSmallestEnclosingCircle(const std::vector<Point> &points);
    static Circle MakeSmallestEnclosingCircleOnePoint(const std::vector<Point> &points, size_t end, const Point &p);
    static Circle MakeSmallestEnclosingCircleTwoPoints(const std::vector<Point> &points, size_t end, const Point &p, const Point &q);
    static Circle MakeDiameter(const Point &a, const Point &b);
    static Circle MakeCircumcircle(const Point &a, const Point &b, const Point &c);
};


#endif //SMALLESTENCLOSINGCIRCLE_CLUSTERMINIMALENCLOSINGCIRCLE_H
