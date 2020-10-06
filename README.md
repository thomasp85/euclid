
<!-- README.md is generated from README.Rmd. Please edit that file -->

# euclid <a href='https://euclid.data-imaginist.com'><img src='man/figures/logo.png' align="right" height="138.5" /></a>

<!-- badges: start -->

[![Codecov test
coverage](https://codecov.io/gh/thomasp85/euclid/branch/master/graph/badge.svg)](https://codecov.io/gh/thomasp85/euclid?branch=master)
[![R build
status](https://github.com/thomasp85/euclid/workflows/R-CMD-check/badge.svg)](https://github.com/thomasp85/euclid/actions)
<!-- badges: end -->

**WIP**

euclid aims to provide a comprehensive interface to the CGAL library for
computational geometry. At its core it provides new vector types for all
of the geometric primitives defined for the 2 and 3 dimensional kernel.
These vector types maps directly into C++ structures ensuring that no
conversion back and forth between R and C++ takes place. This, in turn,
ensures that geometric calculations remain exact and free of any
rounding errors or issues with floating point arithmetic.

The plan is to gradually expand the algorithms that euclid support once
the vector foundation is established

## Installation

For now, euclid can be installed from github using remotes:

``` r
# install.packages("remotes")
remotes::install_github("thomasp85/euclid")
```

## Example

The package is still quite shallow but have rudimentary support for
points and circles

``` r
library(euclid)
#> 
#> Attaching package: 'euclid'
#> The following object is masked from 'package:stats':
#> 
#>     line

# Construct some exact numbers
random_num <- exact_numeric(runif(20, max = 10))

# Exact numbers behave much like R numerics (though not everything is possible)
random_num[1:5]
#> <Vector of exact numerics>
#> [1] 2.655087 3.721239 5.728534 9.082078 2.016819
max(random_num)
#> <Vector of exact numerics>
#> [1] 9.919061
sort(random_num)
#> <Vector of exact numerics>
#>  [1] 0.6178627 1.7655675 2.0168193 2.0597457 2.6550866 3.7212390 3.8003518
#>  [8] 3.8410372 4.9769924 5.7285336 6.2911404 6.6079779 6.8702285 7.1761851
#> [15] 7.6984142 7.7744522 8.9838968 9.0820779 9.4467527 9.9190609
random_num[2] * 10
#> <Vector of exact numerics>
#> [1] 37.21239
random_num[5] + random_num[16]
#> <Vector of exact numerics>
#> [1] 6.993812
cumsum(random_num)
#> <Vector of exact numerics>
#>  [1]   2.655087   6.376326  12.104859  21.186937  23.203756  32.187653
#>  [7]  41.634406  48.242384  54.533524  55.151387  57.211133  58.976700
#> [13]  65.846929  69.687966  77.386380  82.363373  89.539558  99.458619
#> [19] 103.258970 111.033423

# With exact numbers we can construct our geometries

# 2 dimensions
p1 <- point(random_num[1:5], random_num[6:10])
p1
#> <Vector of points in 2 dimensions>
#> [1] <x:2.66, y:8.98>  <x:3.72, y:9.45>  <x:5.73, y:6.61>  <x:9.08, y:6.29> 
#> [5] <x:2.02, y:0.618>

# circle based on center and radius
circle(p1, random_num[11:15])
#> <Vector of circles in 2 dimensions>
#> [1] <x:2.66, y:8.98, r2:4.24>  <x:3.72, y:9.45, r2:3.12> 
#> [3] <x:5.73, y:6.61, r2:47.2>  <x:9.08, y:6.29, r2:14.8> 
#> [5] <x:2.02, y:0.618, r2:59.3>

# circle based on 2 points
circle(p1, point(random_num[11:15], random_num[16:20]))
#> <Vector of circles in 2 dimensions>
#> [1] <x:2.36, y:6.98, r2:4.1>  <x:2.74, y:8.31, r2:2.25>
#> [3] <x:6.3, y:8.26, r2:3.07>  <x:6.46, y:5.05, r2:8.42>
#> [5] <x:4.86, y:4.2, r2:20.9>

# 3 dimensions
point(random_num[1:5], random_num[6:10], random_num[11:15])
#> <Vector of points in 3 dimensions>
#> [1] <x:2.66, y:8.98, z:2.06> <x:3.72, y:9.45, z:1.77> <x:5.73, y:6.61, z:6.87>
#> [4] <x:9.08, y:6.29, z:3.84> <x:2.02, y:0.618, z:7.7>
```

## Code of Conduct

Please note that the euclid project is released with a [Contributor Code
of
Conduct](https://contributor-covenant.org/version/2/0/CODE_OF_CONDUCT.html).
By contributing to this project, you agree to abide by its terms.
