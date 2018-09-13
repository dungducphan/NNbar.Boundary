#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <iterator>
#include <cmath>

#include "../ClusterConvexHullEstimator.h"

int main() {
    ClusterConvexHullEstimator* convecHullFinder = new ClusterConvexHullEstimator();

    std::vector< std::pair<double, double> > PointSet;
    PointSet.push_back(std::make_pair(0.25, 0.25));
    PointSet.push_back(std::make_pair(0.00, 1.00));
    PointSet.push_back(std::make_pair(4.00, 0.00));
    PointSet.push_back(std::make_pair(0.00, 0.00));

    convecHullFinder->SetPoints(PointSet);
    double area = convecHullFinder->GetConvexHullArea();
    std::vector< std::pair<double, double> > ConvexSet = convecHullFinder->GetConvexHullPoints();

    for (unsigned int i = 0; i < PointSet.size(); i++) {
        std::cout << "Initial Point " << i << ": x = " << PointSet.at(i).first << ", y = " << PointSet.at(i).second << "." << std::endl;
    }
    std::cout << std::endl;

    for (unsigned int i = 0; i < ConvexSet.size() - 1; i++) {
        std::cout << "Convex Point " << i << ": x = " << ConvexSet.at(i).first << ", y = " << ConvexSet.at(i).second << "." << std::endl;
    }

    if (area == 2) {
        std::cerr << "Test passed" << std::endl;
    } else {
        std::cerr << "Test failed" << std::endl;
    }

    return 0;
}