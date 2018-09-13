//
// Created by Dung Phan on 9/12/18.
//

#ifndef CONVEXHULL_CLUSTERCONVEXHULLESTIMATOR_H
#define CONVEXHULL_CLUSTERCONVEXHULLESTIMATOR_H

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <iterator>
#include <cmath>

// BOOST
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)

// BOOST data type
typedef boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian> BoostPoint_t;
typedef boost::geometry::model::polygon<BoostPoint_t> BoostMultiPoint_t;


template <typename Point>
class ExtractPointFunctor {
private:
    std::vector< std::pair<double, double> > * pointVector;
public :
    ExtractPointFunctor(std::vector< std::pair<double, double> > * ConvexHullPointVector)
        : pointVector(ConvexHullPointVector)
    {}

    inline void operator()(Point& p) {
        double x = boost::geometry::get<0>(p);
        double y = boost::geometry::get<1>(p);
        pointVector->push_back(std::make_pair(x, y));
    }
};

class ClusterConvexHullEstimator {
public:
    ClusterConvexHullEstimator();
    virtual ~ClusterConvexHullEstimator();
    void SetPoints(std::vector< std::pair<double, double> > & points);

    // GETs
    double GetConvexHullArea();
    std::vector< std::pair<double, double> > GetConvexHullPoints();

private:
    std::vector< std::pair<double, double> > kPoints;
    std::vector< std::pair<double, double> > kConvexHullPointVector;
    std::vector< std::pair<double, double> > kConvexHull;
    BoostMultiPoint_t kBoostPoints;
    BoostMultiPoint_t kBoostConvexHull;

    double kConvexHullArea;

    // Executions
    virtual void FindConvexHull();
    virtual void FindConvexHullPoints();
};

#endif //CONVEXHULL_CLUSTERCONVEXHULLESTIMATOR_H
