# R-travis-container-example
Example R package that is built using the container-based infrastructure from Travis

Using the container-based infrastructure from Travis to build R packages is straightforward and can be very fast when we make use of the caching functions that the containers provide. 

To use R from within the container I add the following lines to `.travis.yml`:
```{yml}
addons:
  apt:
    sources:
    - r-packages-precise
    packages:
    - r-base-dev
```
I then store all installed `R` packages in the folder `~/Rlib` that is then going be cached. 
```{yml}
cache:
  directories: 
    - ~/Rlib
```
I then install and test the package using Hadley's `devtools` package, which is only installed if needed: 
```{R}
if (!"devtools" %in% rownames(installed.packages())) { 
    install.packages("devtools", dependencies=TRUE, repos="http://cran.rstudio.com/") 
}
```

To illustrate how long all of this takes, I put together a package with lots of "heavy" dependencies: `Rcpp`, `RcppArmadillo`, and `ggplot2`.

|                           | duration          |
|---------------------------|---------------|
| Initial build time without cache: | 9 min 2 sec      |
| All subsequent builds that cache dependencies:    |    |
