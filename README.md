[![Build Status](https://travis-ci.org/jtilly/R-travis-container-example.svg?branch=master)](https://travis-ci.org/jtilly/R-travis-container-example) 
[![Coverage Status](https://coveralls.io/repos/jtilly/R-travis-container-example/badge.svg?branch=master&service=github)](https://coveralls.io/github/jtilly/R-travis-container-example?branch=master)

# Building R packages with Travis CI containers
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
The list of [sources](https://github.com/travis-ci/apt-source-whitelist) and [packages](https://github.com/travis-ci/apt-package-whitelist/blob/master/ubuntu-precise) that Travis allows is fairly limited. However, [`r-packages-precise`](https://cran.r-project.org/bin/linux/ubuntu/) is white-listed and contains an up-to-date release of `R`. 

I store all installed `R` packages in the directory `~/Rlib` that is eventually going be cached. 
```{yml}
cache:
  directories: 
    - ~/Rlib
```

To illustrate how long all of this takes, I put together a package with lots of "heavy" dependencies: `Rcpp`, `RcppArmadillo`, and `ggplot2`.

|                           | Duration          |
|---------------------------|---------------|
| Initial build time without cache ([log file](https://s3.amazonaws.com/archive.travis-ci.org/jobs/73105072/log.txt)) | 9 min 2 sec      |
| All subsequent builds that cache dependencies ([log file](https://s3.amazonaws.com/archive.travis-ci.org/jobs/73106362/log.txt))   | 1 min  0 sec  |

# See also
[Yihui Xie](https://github.com/yihui/) also uses the container based infrastructure to build R packages on travis, e.g. for [knitr](https://github.com/yihui/knitr) and [rmarkdown](https://github.com/yihui/rmarkdown). His build script looks very similar to what I have in this repository. Yihui resolved issues stemming from old pandoc and texlive versions by putting together precompiled versions of pandox and texlive.
