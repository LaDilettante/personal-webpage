#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
List f_gibbsC(NumericVector y, int S,
                       double mu_0, double tau2_0,
                       double sigma2_0, double nu_0) {
  // Sample statistics
  double n = y.size();
  double ybar = mean(y);

  // Initialize storage
  NumericVector res_theta(S);
  NumericVector res_sigma2(S);

  // Starting value as the sample variance and mean
  res_sigma2[0] = var(y);
  res_theta[0] = ybar;

  // Gibbs sampler -- big loop
  // We will have S iterations, with s going from 0 to S - 1
  for (int s = 1; s < S; s++) {
    // Full conditional for theta
    double sigma2 = res_sigma2[s - 1];

    double tau2_n = 1.0 / (1.0 / tau2_0 + n / sigma2); // Note the 1.0
    double mu_n = (mu_0 / tau2_0 + n * ybar / sigma2) / (1.0 / tau2_0 + n / sigma2);

    // Generate and save theta. Note that rnorm takes SD, not variance
    res_theta[s] = rnorm(1, mu_n, sqrt(tau2_n))[0];

    // Full conditional for sigma
    double theta = res_theta[s]; // Get the current value of theta

    double nu_n = nu_0 + n;
    double nu_sigma2_n = nu_0 * sigma2_0 + sum(pow((y - theta), 2));

    // Generate and save sigma2
    res_sigma2[s] = 1.0 / rgamma(1, nu_n / 2.0, 2.0 / nu_sigma2_n)[0]; // Use scale, not rate
  }

  List result; result["theta"] = res_theta ; result["sigma2"] = res_sigma2;
  return result;
}