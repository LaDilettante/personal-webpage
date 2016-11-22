---
title: "Mutable state in R"
excerpt: "Implements an OOP behavior in R to test MCMC code."

---



The main goal of this post is to implement an OOP-like behavior in R, especially a mutable state. The motivation for this approach is to test MCMC code, but you can skip straight to the next paragraph where I discuss the R implementation.

(If you are from Reddit, feel free to comment here or in the Reddit thread -- I'll monitor both for your insights!)

# Motivation

As my MCMC code grows unwieldy, I've grown increasingly paranoid about its correctness. It didn't help that [the StackOverflow answer to "How to debug MCMC"](http://stats.stackexchange.com/questions/524/is-there-a-standard-technique-to-debug-mcmc-programs) is essentially *very carefully*. The central problem is that:

1. MCMC result is stochastic, so there isn't an exact expected result to compare against
2. MCMC code takes a long time to run, so it's not feasible to test often
3. MCMC code involves a big loop updating each parameter, so it's hard to isolate the bug

To debug MCMC, [Grosse & Duvenaud](https://arxiv.org/abs/1412.5218) proposes isolating the big loop into smaller functions, each drawing a new parameter value conditional on other parameters' values. We can then unit test the correctness of these functions one by one. 

Their Python implemention includes two classes: `Model`, which characterizes the model, and `State`, which stores the parameter values in the current MCMC step.

```python
class Model:
  def __init__(self, alpha, K, sigma_sq_mu_prior, sigma_sq_n_prior):
    self.alpha = alpha # Parameter for Dirichlet prior over mixture probabilities
    self.K = K # Number of components
    self.sigma_sq_mu_prior = sigma_sq_mu_prior
    self.sigma_sq_n_prior = sigma_sq_n_prior
    
    def cond_pi(self, state):
      counts = np.bincount(state.z)
      counts.resize(self.K)
      return DirichletDistribution(self.alpha + counts)
    
    # Other conditional distributions here
    
class State:
  def __init__(self, z, mu, sigma_sq_mu, sigma_sq_n, pi):
    self.z = z # Assignments (represented as an array of integers)
    self.mu = mu # Cluster centers
    self.sigma_sq_mu = sigma_sq_mu # Between-cluster variance
    self.sigma_sq_n = sigma_sq_n # Within-cluster variance
    self.pi = pi # Mixture probabilities
```

Using `Model`'s methods like `cond_pi`, we can draw new values in each MCMC step like so:

```python
class Model:
  ...
  
  def gibbs_step(self, state, X):
    state.pi = self.cond_pi(state).sample()
    state.z = self.cond_z(state, X).sample()
    state.mu = self.cond_mu(state, X).sample()
    state.sigma_sq_mu = self.cond_sigma_sq_mu(state).sample()
    state.sigma_sq_n = self.cond_sigma_sq_n(state, X).sample()
```

# Mutable state in R

How to translate this implementation in R? Crucially, we need a *mutable state* that stores the current parameter values. While it's possible to accomplish this with S3, storing "instance variables" as elements in a list, searching for "mutable state R" leads me to [Hadley's discussion of functional programming](http://adv-r.had.co.nz/Functional-programming.html).

It thus occurs to me that I can use functional programming to implement an OOP-like behavior. Let's say we want to create a class `Dog`, which has instance variables `name` & `speech`, getters and setters methods, and a method `bark`.

The implementation using closure in functional programming looks like so:


{% highlight r %}
dog <- function(name, speech) {
  # instance variables
  name <- name
  speech <- speech
  
  # getter methods
  get <- function(param = c("name", "speech")) {
    param <- match.arg(param)
    switch(param,
           name = name,
           speech = speech)
  }
  
  # setter methods
  set_name <- function(value) name <<- value
  set_speech <- function(value) speech <<- value
  
  # method
  bark <- function() print(paste0(speech, "!"))
  
  return(list(get = get, 
              set_name = set_name, 
              set_speech = set_speech,
              bark = bark))
}
{% endhighlight %}

We can create a dog, give it a name, or make it bark.


{% highlight r %}
# Create a dog
my_dog <- dog(name = "Dodger", speech = "woof")
my_dog$get("name")
{% endhighlight %}



{% highlight text %}
## [1] "Dodger"
{% endhighlight %}



{% highlight r %}
# Make it bark
my_dog$bark()
{% endhighlight %}



{% highlight text %}
## [1] "woof!"
{% endhighlight %}



{% highlight r %}
# Change it speech
my_dog$set_speech("roof")
my_dog$bark()
{% endhighlight %}



{% highlight text %}
## [1] "roof!"
{% endhighlight %}

It feels very weird to me that functional programming can be used to accomplish an OOP-like behavior like this, which actually looks closer to classic OOP than R's class system. 

I did successfully using this approach to test my MCMC code. But should I? I can't get over how weird this looks.