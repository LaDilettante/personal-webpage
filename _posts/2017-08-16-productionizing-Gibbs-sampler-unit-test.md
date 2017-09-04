---
title: "Unit test for your Gibbs sampler"
excerpt: "Making your MCMC code ready for production."
---

In [Part 1]({{ site.baseurl }}{% post_url 2017-08-15-productionizing-Gibbs-sampler-integration-test %}), I discussed how to integration test a fast, no-frill Gibbs sampler. In essence, the integration test checks if the posterior estimates are "close enough" to the true values. Unfortunately, such a test can be misleading. Indeed:

- We can pass the test with wrong code. This happens when our model uses regularization or informative prior, causing the posterior estimates to be "close enough" even though the Gibbs sampler is wrong.
- We can fail the test with correct code. If the posterior density has weird geometry, our Gibbs sampler may not converge in time. In this case, the posterior estimates are not "close enough" even though the Gibbs sampler is correct.

Furthermore, the current implementation lacks maintainability:

- The integration test can take hours to derive the posterior samples, discouraging engineers from making incremental improvements to the code.
- The environment within the loop is littered with variables, making it difficult to make small changes without downstream effects.

To solve these problems, [Grosse and Duvenaud (2014)](https://arxiv.org/abs/1412.5218) demonstrates a unit-testing approach for MCMC code. In essence, a unit test requires our code to have an easy-to-check expected behavior. Such a behavior for the full conditional \\(p(\theta \| x)\\) is the following identity:[^1]

$$
\begin{align}
\frac{p(\theta_1 | x)}{p(\theta_2 | x)} &= \frac{p(\theta_1) p(x|\theta_1)}{p(\theta_2)p(x|\theta_2)} \qquad \forall \theta_1, \theta_2
\end{align}
$$

where \\(\theta_1, \theta_2\\) are two arbitrary values of \\(\theta\\).

This identity is perfect for a unit test for three reasons:
- The identity must hold *exactly*, so we don't rely on testing "close enough" behavior.
- The identity must hold for any two arbitrary values of \\(\theta\\), so mocking and setting up is minimal.
- The right-hand side contains only terms that are easy to derive. Specifically, \\(p(\theta)\\) is the prior, which is whatever the distribution we choose. \\(p(x \| \theta)\\) is the likelihood, which comes directly from the model with no extra work.

To facilitate unit testing, we modularize the Gibbs sampler as follows. First, we have a `State` class that contains the current state of the parameters.


```python
import numpy as np
import scipy.stats

class State(object):
    def __init__(self, theta, sigma2):
        self.theta = theta
        self.sigma2 = sigma2
```

Second, we have a `Model` class that describes the model.


```python
class Model(object):
    def __init__(self, theta_prior, sigma2_prior, rng=None):
        self.theta_prior = theta_prior
        self.sigma2_prior = sigma2_prior
        self.rng = rng

    # Full Conditional for theta
    def cond_theta(self, state, data):
        n = len(data)
        mean_prior = self.theta_prior.args[0]
        variance_prior = self.theta_prior.args[1] ** 2

        variance_post = 1 / (1 / variance_prior + n / state.sigma2)
        mean_post = variance_post * (mean_prior / variance_prior + n * data.mean() / state.sigma2)
        return scipy.stats.norm(mean_post, np.sqrt(variance_post))
    
    # Full Conditional for sigma2
    def cond_sigma2(self, state, data):
        n = len(data)
        shape_prior = self.sigma2_prior.kwds['a']
        scale_prior = self.sigma2_prior.kwds['scale']

        shape_post = shape_prior + n / 2
        scale_post = scale_prior + np.sum((data - state.theta) ** 2) / 2
        return scipy.stats.invgamma(shape_post, scale=scale_post)
    
    # A gibbs step iterate through theta, sigma2 and update them
    def gibbs_step(self, state, data):
        state.theta = self.cond_theta(state, data).rvs(random_state=self.rng)
        state.sigma2 = self.cond_sigma2(state, data).rvs(random_state=self.rng)

    # Joint density, used as the right hand side in the identity to be used in the unit test
    def joint_log_p(self, state, data):
        return self.theta_prior.logpdf(state.theta) + \
               self.sigma2_prior.logpdf(state.sigma2) + \
               (scipy.stats.norm(loc=state.theta, scale=np.sqrt(state.sigma2))
                .logpdf(data).sum())
```

We can then test the identity above as follows. Note the use of `pytest`'s fixture to DRY. We randomize our model, state, and data to be extra sure that our Gibbs sampler is always correct.


```python
import pytest
import copy

@pytest.fixture
def random_model():
    theta_prior = scipy.stats.norm(np.random.uniform(), np.random.uniform())
    sigma2_prior = scipy.stats.invgamma(a=np.random.uniform(),
                                        scale=np.random.uniform())
    return Model(theta_prior=theta_prior,
                 sigma2_prior=sigma2_prior)

@pytest.fixture
def random_state():
    return State(np.random.uniform(), np.random.uniform())

@pytest.fixture
def random_data():
    return np.random.normal(size=10)

def test_cond_theta(random_model, random_state, random_data):
    cond = random_model.cond_theta(random_state, random_data)
    new_state = copy.deepcopy(random_state)
    new_state.theta = np.random.uniform()

    assert np.allclose(cond.logpdf(new_state.theta) - cond.logpdf(random_state.theta),
                       random_model.joint_log_p(new_state, random_data) - \
                       random_model.joint_log_p(random_state, random_data))

def test_cond_sigma2(random_model, random_state, random_data):
    cond = random_model.cond_sigma2(random_state, random_data)
    new_state = copy.deepcopy(random_state)
    new_state.sigma2 = np.random.uniform()

    assert np.allclose(cond.logpdf(new_state.sigma2) - cond.logpdf(random_state.sigma2),
                       random_model.joint_log_p(new_state, random_data) - \
                       random_model.joint_log_p(random_state, random_data))
```

Running `$ pytest` in the terminal from the project root folder will check whether we have implemented the Gibbs sampler correctly. Check out [my Github repo](https://github.com/LaDilettante/productionized-mcmc) to see how I arrange this code with to be tested with `pytest`.

## Check the no-frill Gibbs sampler against the modular Gibbs sampler

The modular Gibbs sampler is very legible and easy to test. However, due to various overhead with creating classes and objects, it can be slower that the no-frill Gibbs sampler that relies exclusively on `numpy`. Therefore, my preferred approach is 

1. Optimize for legibility while writing the modular Gibbs
2. Optimize for performance while writing the no-frill Gibbs
3. Check that the no-frill Gibbs produces the same result as the modular Gibbs (by running both using the same seed)
4. Use the no-frill Gibbs in production

This way, we get the best of both worlds. Below I show how to carry out step (3), checking the no-frill Gibbs against the modular Gibbs.


```python
# Generate the data from known parameters
true_theta = 2
true_sigma2 = 3.5
y = np.random.normal(true_theta, np.sqrt(true_sigma2), size = 1000)

# Specify the prior
prior = {'mu_0': 10, 'tau2_0': 10000, 'nu_0': 1, 'sigma2_0': 10}
```


```python
# Run the modular Gibbs and store its result
class Storage(object):
    def __init__(self, S=0):
        self.states = [None] * S
        
    def add_state(self, state, i):
        self.states[i] = copy.copy(state)
        
    def __getattr__(self, param):
        return np.array([getattr(state, param) for state in self.states])

# Specify the Model, noticing the seed
my_model = Model(theta_prior=scipy.stats.norm(prior['mu_0'], np.sqrt(prior['tau2_0'])), 
                 sigma2_prior=scipy.stats.invgamma(a=prior['nu_0'] / 2, 
                                                   scale=(prior['nu_0'] * prior['sigma2_0']) / 2),
                 rng=42)

samples_gibbs_modular = Storage(2)
my_state = State(theta=y.mean(), sigma2=y.var())
samples_gibbs_modular.add_state(my_state, 0)
for i in range(1, 2):
    my_model.gibbs_step(my_state, y)
    samples_gibbs_modular.add_state(my_state, i)
```


```python
# Run the no-frill Gibbs and store its result
def gibbs_simple(S, y, prior, rng=None):
    """
    A no-frill Gibbs sampler
    
    Parameters
    ----------
    S : int, the number of samples
    y : data vector
    prior : dict, prior parameters
    rng : int, random seed
    """
    n = len(y)
    ybar = y.mean()

    # Initialize storage
    theta_samples = np.empty(S)
    sigma2_samples = np.empty(S)

    # Starting value as the sample variance and mean
    sigma2_samples[0] = y.var()
    theta_samples[0] = ybar

    # Big loop
    for s in range(1, S):
        # Update theta
        tau2_n = 1 / (1 / prior['tau2_0'] + n / sigma2_samples[s - 1])
        mu_n = tau2_n * (prior['mu_0'] / prior['tau2_0'] + n * ybar / sigma2_samples[s - 1])
        theta_samples[s] = scipy.stats.norm(mu_n, np.sqrt(tau2_n)).rvs(random_state=rng)

        # Update sigma2
        nu_n = prior['nu_0'] + n
        nu_sigma2_n = prior['nu_0'] * prior['sigma2_0'] + sum((y - theta_samples[s]) ** 2)
        sigma2_samples[s] = scipy.stats.invgamma(nu_n / 2, scale=nu_sigma2_n / 2).rvs(random_state=rng)
        
    return {'theta': theta_samples, 'sigma2': sigma2_samples}

# Notice that we set the same seed here as above
samples_gibbs_simple = gibbs_simple(2, y, prior, rng=42)
```


```python
assert np.allclose(samples_gibbs_simple['theta'], samples_gibbs_modular.theta)
assert np.allclose(samples_gibbs_simple['sigma2'], samples_gibbs_modular.sigma2)
```

In a real production environment, all these tests should be put in an automated test framework. (See [my Github repo](https://github.com/LaDilettante/productionized-mcmc) as an example).

## Postcript: Some tips for legible MCMC code

As mentioned above, while writing the modular Gibbs sampler, I optimize for legibility. Below are some tips on doing so.

### 1. Use Python `@property` to compute functions of your parameters

In our MCMC code, we frequently need to compute functions of our parameters. For example, while we parameterize our normal distribution with the variance parameter, `numpy`'s normal distribution may ask for scale, or we may want to extract the precision to monitor. In a simple program it's easy enough to write `sigma = np.sqrt(state.sigma2)` or `tau = 1 / state.sigma2` every time. But in a larger program we want to DRY ("Don't Repeat Yourself") and simply write `state.sigma` or `state.tau`. Besides all [the usual benefits of DRY](https://softwareengineering.stackexchange.com/questions/103233/why-is-dry-important), this also lets our code reads more like its statistical intent.

To create an instance variable (i.e. `sigma`) that is a function of another instance variable (i.e. `sigma2`), we take advantage of Python's `@property` decorator as follows.


```python
class State(object):
    def __init__(self, sigma2):
        self.sigma2 = sigma2
        
    @property
    def sigma(self):
        return np.sqrt(self.sigma2)
    
    @property
    def tau(self):
        return 1 / self.sigma2
```

We can set the value of `sigma2` ...


```python
my_state = State(sigma2 = 0.5 ** 2)
print("sigma2: {}".format(my_state.sigma2))
```

    sigma2: 0.25


... and `sigma` and `tau` will be automatically available


```python
print("sigma:  {}".format(my_state.sigma))
print("tau:    {}".format(my_state.tau))
```

    sigma:  0.5
    tau:    4.0


### 2. Wrap `scipy.stats` distributions into classes for flexibility in parameterization

A lot of the times `scipy.stats` distributions don't have the parameterization that I'd like to use. For example, in most Bayesian books, the [Gamma distribution](https://en.wikipedia.org/wiki/Gamma_distribution) uses the shape/rate parameterization, while `scipy.stats` uses the shape/scale parameterization.

In these cases, I like to wrap the `scipy.stats` distributions in a class so that I can pick my own parameterization and naming convention. For example, I wrap the Gamma distribution as follows:


```python
class GammaDist(object):
    def __init__(self, shape, rate, rng=None):
        self.shape = shape
        self.rate = rate
        self.rng = rng
        
    def rvs(self):
        return scipy.stats.gamma(a=self.shape, scale=1/self.rate).rvs(random_state=self.rng)
```

This way, in my code I can draw a new sample as:


```python
my_gamma = GammaDist(1, 2)
my_gamma.rvs()
```




    0.91282599799158526



Furthermore, I can also easily refer to the Gamma hyperparameters as `my_gamma.shape` and `my_gamma.rate`, which is more legible than `scipy_gamma.kwds['a']` and `1 / scipy_gamma.kwds['scale']`.

[^1]: We obtain this identity by multiplying both the numerator and the denominator with \\( p(x) \\)

