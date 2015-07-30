// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-

// we only include RcppArmadillo.h which pulls Rcpp.h in for us
#include "RcppArmadillo.h"

// via the depends attribute we tell Rcpp to create hooks for
// RcppArmadillo so that the build process will know what to do
//
// [[Rcpp::depends(RcppArmadillo)]]


//' Hello World
//'
//' simple example of creating two matrices and returning the result of an
//' operation on them
//'
//' @return matrix
// [[Rcpp::export]]
arma::mat rcpparma_hello_world() {
    arma::mat m1 = arma::eye<arma::mat>(3, 3);
    arma::mat m2 = arma::eye<arma::mat>(3, 3);

    return m1 + 3 * (m1 + m2);
}


//' Outer product
//'
//' another simple example: outer product of a vector,
//' returning a matrix
//'
//' @param x column vector
//' @return matrix with the outer product
//'
// [[Rcpp::export]]
arma::mat rcpparma_outerproduct(const arma::colvec & x) {
    arma::mat m = x * x.t();
    return m;
}

//' Inner product
//'
//' another simple example: inner product of a vector,
//' returning a scalar
//'
//' @param x column vector
//' @return scalar with the inner product
//'
// [[Rcpp::export]]
double rcpparma_innerproduct(const arma::colvec & x) {
    double v = arma::as_scalar(x.t() * x);
    return v;
}


//' Return both the inner and outer product
//'
//' Return a list with both the inner and outer product
//'
//' @param x column vector
//' @return list with both the inner and outer product
//'
// [[Rcpp::export]]
Rcpp::List rcpparma_bothproducts(const arma::colvec & x) {
    arma::mat op = x * x.t();
    double    ip = arma::as_scalar(x.t() * x);
    return Rcpp::List::create(Rcpp::Named("outer")=op,
                              Rcpp::Named("inner")=ip);
}
