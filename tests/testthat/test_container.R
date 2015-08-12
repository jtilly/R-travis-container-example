# simple tests

test_that("rcpparma_hello_world", {
    expect_true(identical(rcpparma_hello_world(), structure(c(7, 0, 0, 0, 7, 0, 0, 0, 7), .Dim = c(3L, 3L))))
})

test_that("rcpparma_outerproduct", {
    expect_true(identical(rcpparma_outerproduct(c(1,2,3)), structure(c(1, 2, 3, 2, 4, 6, 3, 6, 9), .Dim = c(3L, 3L))))
})


test_that("rcpparma_innerproduct", {
    expect_true(identical(rcpparma_innerproduct(c(1,2,3)), 14))
})

test_that("rcpparma_bothproducts", {
    res = rcpparma_bothproducts(c(1,2,3))
    expect_true(identical(res$inner, 14))
    expect_true(identical(res$outer, structure(c(1, 2, 3, 2, 4, 6, 3, 6, 9), .Dim = c(3L, 3L))))
})

test_that("this tests nothing", {
    sink("~/debug.txt")
    print(.libPaths())
    print(list.files(.libPaths()[1]))
    sink()
    expect_true(TRUE)
})