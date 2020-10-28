test_that("validate_constructor_input works", {
  num <- runif(10)
  exact_num <- exact_numeric(num)
  geo2 <- point(num, num)
  geo3 <- sphere(point(num, num, num), num)

  expect_error(validate_constructor_input(geo2, geo3))
  expect_error(validate_constructor_input(geo2, num[1:4]))

  res <- validate_constructor_input(num)
  expect_true(all(res[[1]] == exact_num))

  res <- validate_constructor_input(num, .convert_numerics = FALSE)
  expect_true(all(res[[1]] == num))

  res <- validate_constructor_input(geo2, num[2])
  expect_equal(lengths(res), c(10, 10))
})

test_that("check_geometry_input works", {
  num <- runif(10)
  geo2 <- point(num, num)
  geo3 <- sphere(point(num, num, num), num)
  expect_error(check_geometry_input(geo2, geo3))
  expect_error(check_geometry_input(geo2, num))
  expect_silent(check_geometry_input(geo2, NULL, geo2))
})
