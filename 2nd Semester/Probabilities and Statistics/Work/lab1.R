variance = function (x, p) {
  expectation = sum(p*x);
  variance = sum(p*(x-expectation) ^ 2);
  return (variance)
}

y = c( 234, 512, 12, 123, 51, 123)
q = c(1/2, 1/2, 1/5, 1/1234, 1/23, 1/213)

variance(y, q)

