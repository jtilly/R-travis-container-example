[![Build Status](https://travis-ci.org/jtilly/R-travis-container-example.svg?branch=master)](https://travis-ci.org/jtilly/R-travis-container-example) 
[![Coverage Status](https://coveralls.io/repos/jtilly/R-travis-container-example/badge.svg?branch=master&service=github)](https://coveralls.io/github/jtilly/R-travis-container-example?branch=master)

# R-travis-container-example
This repository contains an example `R` package that is built using the container-based infrastructure from [Travis CI](https://travis-ci.org/).

The container-based infrastructure from Travis CI to build `R` packages can be very fast when we cache dependent packages. The main difference between the containerized infrastructure and the "traditional" approach is that with containers we cannot use `sudo` anymore. Therefore, we cannot piece together our favorite version of `R`  using `sudo apt-get install` or rely on binary packages (e.g. from [c2d4u]( https://launchpad.net/~marutter/+archive/ubuntu/c2d4u)). 

To use `R` from within the container I added the following lines to my `.travis.yml`:
```{yml}
addons:
  apt:
    sources:
    - r-packages-precise
    packages:
    - r-base-dev
```
The list of [sources](https://github.com/travis-ci/apt-source-whitelist) and [packages](https://github.com/travis-ci/apt-package-whitelist/blob/master/ubuntu-precise) that Travis is allows is fairly limited. However, [`r-packages-precise`](https://cran.r-project.org/bin/linux/ubuntu/) is white-listed and contains a fairly up-to-date release of `R`. 

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


The obvious shortcoming of this approach is that all dependencies are now cached. Therefore, if some of the dependencies change, we need to manually delete the cache over at Travis to download and compile the changed packages again. 
