//
// Created by Dung Phan on 9/12/18.
//

#include "ClusterConvexHullEstimator.h"

ClusterConvexHullEstimator::ClusterConvexHullEstimator() {
    kPoints.clear();
    kConvexHull.clear();
    kBoostPoints.clear();
    kBoostConvexHull.clear();
    kConvexHullArea = 0;
}

ClusterConvexHullEstimator::~ClusterConvexHullEstimator() {
}

void ClusterConvexHullEstimator::SetPoints(std::vector<std::pair<double, double> > & points) {
    // Start fresh
    kPoints.clear();
    kConvexHull.clear();
    kBoostPoints.clear();
    kBoostConvexHull.clear();

    // Deep copy
    std::copy(points.begin(), points.end(), std::back_inserter(kPoints));
}

void ClusterConvexHullEstimator::FindConvexHull() {
    // Clear any existing initial polygon
    kBoostPoints.clear();
    kBoostConvexHull.clear();

    // Turn the set of coordinates into polygon
    for (unsigned int i = 0; i < kPoints.size(); i++) {
        double x = kPoints.at(i).first;
        double y = kPoints.at(i).second;
        boost::geometry::append(kBoostPoints, BoostPoint_t(x, y));
    }

    // Calculate the convex hull
    boost::geometry::convex_hull(kBoostPoints, kBoostConvexHull);
}

void ClusterConvexHullEstimator::FindConvexHullPoints() {
    FindConvexHull();
    boost::geometry::for_each_point(kBoostConvexHull, ExtractPointFunctor<BoostPoint_t>(&kConvexHullPointVector));
}

double ClusterConvexHullEstimator::GetConvexHullArea() {
    FindConvexHull();
    return boost::geometry::area(kBoostConvexHull);
}

std::vector<std::pair<double, double> > ClusterConvexHullEstimator::GetConvexHullPoints() {
    FindConvexHullPoints();
    return kConvexHullPointVector;
}



