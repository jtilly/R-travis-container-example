[![Build Status](https://travis-ci.org/jtilly/R-travis-container-example.svg?branch=master)](https://travis-ci.org/jtilly/R-travis-container-example) 
[![Coverage Status](https://coveralls.io/repos/jtilly/R-travis-container-example/badge.svg?branch=master&service=github)](https://coveralls.io/github/jtilly/R-travis-container-example?branch=master)

# R-travis-container-example
This repository contains an example `R` package that is built using the container-based infrastructure from Travis.

Using the container-based infrastructure from Travis to build R packages is straightforward and can be very fast when we cache dependent packages. 

To use R from within the container I added the following lines to my `.travis.yml`:
```{yml}
addons:
  apt:
    sources:
    - r-packages-precise
    packages:
    - r-base-dev
```
I store all installed `R` packages in the directory `~/Rlib` that is eventually going be cached. 
```{yml}
cache:
  directories: 
    - ~/Rlib
```
I then install my package using `devtools::install`. I use `testthat` to perform unit tests and I use `covr` to report the test coverage. 
```{R}
if (!"devtools" %in% rownames(installed.packages())) { 
    install.packages("devtools", dependencies=TRUE, repos="http://cran.rstudio.com/") 
}
if (!"covr" %in% rownames(installed.packages())) { 
    install.packages("covr", dependencies=TRUE, repos="http://cran.rstudio.com/") 
}
devtools::install(pkg = ".", dependencies = TRUE)
devtools::test()
```

To illustrate how long all of this takes, I put together a package with lots of "heavy" dependencies: `Rcpp`, `RcppArmadillo`, and `ggplot2`.

|                           | Duration          |
|---------------------------|---------------|
| Initial build time without cache ([log file](https://s3.amazonaws.com/archive.travis-ci.org/jobs/73105072/log.txt)) | 9 min 2 sec      |
| All subsequent builds that cache dependencies ([log file](https://s3.amazonaws.com/archive.travis-ci.org/jobs/73106362/log.txt))   | 1 min  0 sec  |


The obvious shortcoming of this approach is that all dependencies are in fact cached. Therefore, if some of the dependent packages change, we need to manually delete the cache over at Travis to download and compile these packages again. 
