#pragma once

#include <CGAL/Regular_triangulation_3.h>
#include <CGAL/Triangulation_vertex_base_with_info_3.h>
#include <vector>

#include "types.h"

template<class K>
class DimensionalTraits_3 {
public:
    static const int dimension = 3;

    using Point   = typename K::Point_3;
    using Vector  = typename K::Vector_3;
    using Sphere  = typename K::Sphere_3;
    using FT      = typename K::FT;

    using Weight  = typename K::FT;
    using Weighted_point = typename K::Weighted_point_3;

    using Vb0 = CGAL::Regular_triangulation_vertex_base_3<K>;
    using Vb  = CGAL::Triangulation_vertex_base_with_info_3<PIndex, K, Vb0>;
    using Cb  = CGAL::Regular_triangulation_cell_base_3<K>;
    using Tds = CGAL::Triangulation_data_structure_3<Vb, Cb>;
    using Regular_triangulation = CGAL::Regular_triangulation_3<K, Tds>;

    // Iterator helpers: use auto so we don't need typedefs
    static auto get_finite_cells_begin(const Regular_triangulation& T) {
        return T.finite_cells_begin();
    }
    static auto get_finite_cells_end(const Regular_triangulation& T) {
        return T.finite_cells_end();
    }

    // Circumsphere of points with given indices
    static Sphere circumsphere(const CVertex& pids,
                               const std::vector<Point>& bpoints) {
        if (pids.size() == 4) {
            return Sphere(bpoints[pids[0]], bpoints[pids[1]],
                          bpoints[pids[2]], bpoints[pids[3]]);
        } else if (pids.size() == 3) {
            return Sphere(bpoints[pids[0]], bpoints[pids[1]], bpoints[pids[2]]);
        } else if (pids.size() == 2) {
            return Sphere(bpoints[pids[0]], bpoints[pids[1]]);
        } else {
            return Sphere(Point(CGAL::ORIGIN));
        }
    }

    // Make a point with the given coordinates
    static Point make_point(const std::vector<double>& coords) {
        if (coords.size() == 3) {
            return Point(coords[0], coords[1], coords[2]);
        } else {
            return Point(CGAL::ORIGIN);
        }
    }
};

