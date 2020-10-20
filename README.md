
<!-- README.md is generated from README.Rmd. Please edit that file -->

# euclid <a href='https://euclid.data-imaginist.com'><img src="man/figures/logo.png" align="right" height="138.5"/></a>

<!-- badges: start -->

[![Codecov test
coverage](https://codecov.io/gh/thomasp85/euclid/branch/master/graph/badge.svg)](https://codecov.io/gh/thomasp85/euclid?branch=master)
[![R build
status](https://github.com/thomasp85/euclid/workflows/R-CMD-check/badge.svg)](https://github.com/thomasp85/euclid/actions)

<!-- badges: end -->

The purpose of euclid is to provide a new unified foundation for
computational geometry in R. It provides new data types for common low
level geometric concepts such as lines, planes, points, triangles, etc.
as well as a core of functionality relates to these primitives.
Specialised geometric algorithms are intended to extend this package so
that e.g. Tessellation will live in it’s own package but use the
foundation laid out in euclid.

At its core euclid is an interface to the CGAL library for computational
geometry. More specifically, it provides access to the functionality in
the [2D and 3D Linear Geometry
Kernel](https://doc.cgal.org/4.14.3/Kernel_23/index.html). The CGAL
foundation means that computations with euclid are exact and free of the
imprecision attached to working with floating point numbers. This is
very important for geometry since floating point errors can compound and
lead to failures in geometric predicates at the core of many geometric
algorithms. To achieve this, data in euclid is never converted to R data
structures but remain as pointers to CGAL structures unless specifically
converted to numerics (in which case the floating point world kicks in)

## Installation

For now, euclid can be installed from github using remotes:

``` r
# install.packages("remotes")
remotes::install_github("thomasp85/euclid")
```

## Data types

The core of euclid is a set of new primitive vector types that model 2
and 3 dimensional geometric objects. The following types are present:

### 2 and 3 dimensions

  - Circles

  - Directions

  - Lines

  - Points

  - Weighted Points

  - Rays

  - Segments

  - Triangles

  - Vectors

### 2 dimensions

  - Iso rectangles

### 3 dimensions

  - Iso cubes

  - Planes

  - Spheres

  - Tetrahedrons

### Special vector types

In addition to the geometric data types, euclid also provides these
primitive vector types:

  - Exact numerics

  - Bounding boxes

  - Affine transformation matrices

## Example

The following example shows how to work with the different data types:

``` r
library(euclid)

# Construct some exact numbers
random_num <- exact_numeric(rnorm(20))

# Exact numbers behave much like R numerics (though not everything is possible)
random_num[1:5]
#> <Vector of exact numerics>
#> [1] -0.6264538  0.1836433 -0.8356286  1.5952808  0.3295078
max(random_num)
#> <Vector of exact numerics>
#> [1] 1.595281
random_num[2] * 10
#> <Vector of exact numerics>
#> [1] 1.836433
random_num[5] + random_num[16]
#> <Vector of exact numerics>
#> [1] 0.2845742
sum(random_num)
#> <Vector of exact numerics>
#> [1] 3.810478

# With exact numbers we can construct our geometries
p <- point(random_num[1:10], random_num[11:20])
p
#> <Vector of points in 2 dimensions>
#>  [1] <x:-0.626, y:1.51>   <x:0.184, y:0.39>    <x:-0.836, y:-0.621>
#>  [4] <x:1.6, y:-2.21>     <x:0.33, y:1.12>     <x:-0.82, y:-0.0449>
#>  [7] <x:0.487, y:-0.0162> <x:0.738, y:0.944>   <x:0.576, y:0.821>  
#> [10] <x:-0.305, y:0.594>

# Create a line based on a vector, going through the origin
l <- line(point(0, 0), vec(3, 7))

# Which points lies on the positive side of the line?
has_on_positive_side(l, p)
#>  [1]  TRUE FALSE  TRUE FALSE  TRUE  TRUE FALSE FALSE FALSE  TRUE

# Project points to line
p1 <- project(p, l)

# Do the projected points lie on the line?
p1 %is_on% l
#>  [1] TRUE TRUE TRUE TRUE TRUE TRUE TRUE TRUE TRUE TRUE

# Construct a triangle from a random point to the extremes of the projected points
t <- triangle(point(rnorm(1), rnorm(1)), min(p1), max(p1))
t
#> <Vector of triangles in 2 dimensions>
#> [1] [<x:0.919, y:0.782>, <x:-0.554, y:-1.29>, <x:0.458, y:1.07>]

# Which points lies inside the triangle?
p %is_inside% t
#>  [1] FALSE  TRUE FALSE FALSE FALSE FALSE FALSE FALSE  TRUE FALSE

# Area of t (cannot be given exact for all geometries so is returned as numerics)
approx_area(t)
#> [1] -0.6897651
```

## Code of Conduct

Please note that the euclid project is released with a [Contributor Code
of
Conduct](https://contributor-covenant.org/version/2/0/CODE_OF_CONDUCT.html).
By contributing to this project, you agree to abide by its terms.
