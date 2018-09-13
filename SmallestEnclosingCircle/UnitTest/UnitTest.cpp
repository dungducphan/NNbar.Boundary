#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <iterator>
#include <cmath>

#include "../ClusterMinimalEnclosingCircle.h"

int main() {
    ClusterMinimalEnclosingCircle* minimalEnclosingCircleFinder = new ClusterMinimalEnclosingCircle();

    std::vector< std::pair<double, double> > PointSet;
    PointSet.push_back(std::make_pair(0.25, 0.25));
    PointSet.push_back(std::make_pair(0.00, 1.00));
    PointSet.push_back(std::make_pair(1.00, 0.00));
    PointSet.push_back(std::make_pair(0.00,-1.00));

    minimalEnclosingCircleFinder->SetPoints(PointSet);
    double area = minimalEnclosingCircleFinder->GetMinimalEnclosingCircleArea();

    if (area - minimalEnclosingCircleFinder->Pi == 0) {
        std::cerr << "Test passed" << std::endl;
    } else {
        std::cerr << "Test failed" << std::endl;
    }

    return 0;
}