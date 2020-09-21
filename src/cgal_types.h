#pragma once

//#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Circle_2.h>
#include <CGAL/Circle_3.h>
#include <CGAL/Direction_2.h>
#include <CGAL/Direction_3.h>
#include <CGAL/Iso_cuboid_3.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Line_3.h>
#include <CGAL/Plane_3.h>
#include <CGAL/Point_2.h>
#include <CGAL/Point_3.h>
#include <CGAL/Ray_2.h>
#include <CGAL/Ray_3.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Segment_3.h>
#include <CGAL/Sphere_3.h>
#include <CGAL/Tetrahedron_3.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/Vector_2.h>
#include <CGAL/Vector_3.h>
#include <CGAL/Weighted_point_2.h>
#include <CGAL/Weighted_point_3.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::FT Exact_number;
typedef Kernel::Circle_2 Circle_2;
typedef Kernel::Circle_3 Circle_3;
typedef Kernel::Direction_2 Direction_2;
typedef Kernel::Direction_3 Direction_3;
typedef Kernel::Iso_cuboid_3 Iso_cuboid;
typedef Kernel::Iso_rectangle_2 Iso_rectangle;
typedef Kernel::Line_2 Line_2;
typedef Kernel::Line_3 Line_3;
typedef Kernel::Plane_3 Plane;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Ray_2 Ray_2;
typedef Kernel::Ray_3 Ray_3;
typedef Kernel::Segment_3 Segment_2;
typedef Kernel::Segment_3 Segment_3;
typedef Kernel::Sphere_3 Sphere;
typedef Kernel::Tetrahedron_3 Tetrahedron;
typedef Kernel::Triangle_3 Triangle_2;
typedef Kernel::Triangle_3 Triangle_3;
typedef Kernel::Vector_3 Vector_2;
typedef Kernel::Vector_3 Vector_3;
typedef Kernel::Weighted_point_2 Weighted_point_2;
typedef Kernel::Weighted_point_3 Weighted_point_3;
