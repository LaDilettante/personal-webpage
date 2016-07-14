---
title: "Interaction Term vs Split Sample"
excerpt: "Why you should not use Split Sample to show heterogeneous treatment effect."
---

When an analyst wants to show heterogenous treatment effect (i.e. different treatment effect for different groups), should they 1) run one regression term with an interaction, or 2) run multiple regressions, one for each group (aka split sample)? [A quick Google search shows how common this question is.](https://www.google.com/search?q=split+sample+vs+interaction+term)

In this post, I will show:

1. [Split sample is analogous to running a regression with an interaction term for all predictors](#comparison)

2. [Using split sample to show heterogenous treatment effect is a bad idea](#split-is-bad)

We have outcome $$y$$, independent variable of interest $$X_{\text{int}}$$, an exogenous covariate $$X_{\text{cov}}$$, and group indicator $$G \in \{A, B\}$$. We are interested in estimating the effect of $$X_{\text{int}}$$ on $$y$$, and whether the effect is different across groups $$A$$ and $$B$$. 

<a name="comparison"></a>

## Split sample is analogous to a fully interacted regression

In a split sample analysis, we fit one regression for each group, allowing the coefficients for all $$X$$'s (i.e. both $$X_{\text{int}}$$, and $$\beta_{\text{cov}}$$) to vary. This is equivalent to running a fully interacted regression as I'll show below.

Let the true data-generating process (DGP) be a fully interacted model, i.e. both $$X_\text{int}$$ and $$X_\text{cov}$$ having a different effects on $$y$$ across groups.

Here's the DGP in math:
$$
\begin{align}
y &= \beta_0 + \beta_{int} X_\text{int} + \beta_{cov} X_\text{cov} + \beta_G G + \beta_{intG} X_\text{int} G + \beta_{covG} X_\text{cov} G + \epsilon
\end{align}
$$

Here's the DGP simulated in R:

{% highlight r %}
# Generate the Xs and G
n <- 1000
group <- sample(c("A", "B"), size = n, prob = c(0.5, 0.5), replace = T)
X_int <- rnorm(n)
X_cov <- rnorm(n)

# The DGP that generates y
y <- 1 + 2 * X_int + 3 * X_cov + 4 * (group=="B") + 
  5 * X_int * (group=="B") + 6 * X_cov * (group=="B") + rnorm(n)

data <- data.frame(y, X_int, X_cov, group)
{% endhighlight %}

We then run three regressions, 1) full interaction, 2) split sample (group A only), 3) split sample (group B only).





{% highlight r %}
stargazer(
  lm(y ~ X_int + X_cov + group + X_int:group + X_cov:group, data = data),
  lm(y ~ X_int + X_cov, data = data[data$group == "A", ]),
  lm(y ~ X_int + X_cov, data = data[data$group == "B", ]),
  column.labels = c("fully interacted |", "| group A |",
                    "| group B"),
  keep.stat = c("n", "rsq"), type = "html"
)
{% endhighlight %}


<table style="text-align:center"><tr><td colspan="4" style="border-bottom: 1px solid black"></td></tr><tr><td style="text-align:left"></td><td colspan="3"><em>Dependent variable:</em></td></tr>
<tr><td></td><td colspan="3" style="border-bottom: 1px solid black"></td></tr>
<tr><td style="text-align:left"></td><td colspan="3">y</td></tr>
<tr><td style="text-align:left"></td><td>fully interacted |</td><td>| group A |</td><td>| group B</td></tr>
<tr><td style="text-align:left"></td><td>(1)</td><td>(2)</td><td>(3)</td></tr>
<tr><td colspan="4" style="border-bottom: 1px solid black"></td></tr><tr><td style="text-align:left">X_int</td><td>1.914<sup>***</sup></td><td>1.914<sup>***</sup></td><td>7.010<sup>***</sup></td></tr>
<tr><td style="text-align:left"></td><td>(0.044)</td><td>(0.044)</td><td>(0.050)</td></tr>
<tr><td style="text-align:left"></td><td></td><td></td><td></td></tr>
<tr><td style="text-align:left">X_cov</td><td>3.026<sup>***</sup></td><td>3.026<sup>***</sup></td><td>8.954<sup>***</sup></td></tr>
<tr><td style="text-align:left"></td><td>(0.043)</td><td>(0.043)</td><td>(0.048)</td></tr>
<tr><td style="text-align:left"></td><td></td><td></td><td></td></tr>
<tr><td style="text-align:left">groupB</td><td>3.969<sup>***</sup></td><td></td><td></td></tr>
<tr><td style="text-align:left"></td><td>(0.063)</td><td></td><td></td></tr>
<tr><td style="text-align:left"></td><td></td><td></td><td></td></tr>
<tr><td style="text-align:left">X_int:groupB</td><td>5.096<sup>***</sup></td><td></td><td></td></tr>
<tr><td style="text-align:left"></td><td>(0.066)</td><td></td><td></td></tr>
<tr><td style="text-align:left"></td><td></td><td></td><td></td></tr>
<tr><td style="text-align:left">X_cov:groupB</td><td>5.928<sup>***</sup></td><td></td><td></td></tr>
<tr><td style="text-align:left"></td><td>(0.065)</td><td></td><td></td></tr>
<tr><td style="text-align:left"></td><td></td><td></td><td></td></tr>
<tr><td style="text-align:left">Constant</td><td>1.033<sup>***</sup></td><td>1.033<sup>***</sup></td><td>5.003<sup>***</sup></td></tr>
<tr><td style="text-align:left"></td><td>(0.043)</td><td>(0.043)</td><td>(0.046)</td></tr>
<tr><td style="text-align:left"></td><td></td><td></td><td></td></tr>
<tr><td colspan="4" style="border-bottom: 1px solid black"></td></tr><tr><td style="text-align:left">Observations</td><td>1,000</td><td>533</td><td>467</td></tr>
<tr><td style="text-align:left">R<sup>2</sup></td><td>0.985</td><td>0.927</td><td>0.991</td></tr>
<tr><td colspan="4" style="border-bottom: 1px solid black"></td></tr><tr><td style="text-align:left"><em>Note:</em></td><td colspan="3" style="text-align:right"><sup>*</sup>p<0.1; <sup>**</sup>p<0.05; <sup>***</sup>p<0.01</td></tr>
</table>

We see the all coefficients in `(2) A only` differ from `(3) B only`, not just the $$\beta_{\text{int}}$$ of $$X_{\text{int}}$$. Furthermore, we can calculate the split sample coefficients from the fully interacted model.

$$
\begin{align}
\beta_{intA} &= \beta_{int} \\
\beta_{intB} &= \beta_{int} + \beta_{intG}
\end{align}
$$

**Take-away**: Since it's equivalent to a fully interacted model, split sample analysis shows how *all* coefficients (not just the coefficient of the variable of interest) differ across group.

<a name="split-is-bad"></a>

## Why split sample is a bad way to show heterogenous treatment effect

A very common use of split sample analysis is to run separate regressions and, upon observing that the coefficient $$\beta_{int}$$ for $$X_{\text{int}}$$ is significant for group $$A$$ and insignificant for group $$B$$, conclude that its treatment effect is different across groups. 

This is wrong because the significance of $$X_{int}$$ depends on other covariates as well. For example, if there is high multicollinearity in group A between $$X_{int}$$ and $$X_{cov}$$, then $$X_{int}$$ will be statistically insignificant even if its effect in group $$A$$ is just as strong as its effect in group $$B$$.

For a substantive example, we could imagine that we want to estimate the effect of income ($$X_{int}$$) on happiness ($$y$$) across two groups of people, urban and rural dwellers ($$G$$). It happens that the length of commute ($$X_{cov}$$) matters for happiness too, and the commute is highly correlated with income *only for urban dwellers*. Thus, if we run a split sample analysis, income will have an insignificant coefficient for urban dwellers because of a high multicollinearity, despite having a real impact on happiness.

We simulate that scenario below:

{% highlight r %}
library(mvtnorm)
set.seed(2)

# high multi-collinearity in group A (cor = 0.8)
Xs_A <- rmvnorm(100, mean = c(0, 0), 
                 sigma = matrix(c(1, 0.8, 0.8, 1), nrow = 2))
X_intA <- Xs_A[, 1] ; X_covA <- Xs_A[, 2]

# low multicollinearity in group B (cor = 0)
Xs_B <- rmvnorm(100, mean = c(0, 0),
                 sigma = matrix(c(1, 0, 0, 1), nrow = 2))
X_intB <- Xs_B[, 1] ; X_covB <- Xs_B[, 2]

# Combine the data from two groups
X_int <- c(X_intA, X_intB)
X_cov <- c(X_covA, X_covB)
group = c(rep("A", 100), rep("B", 100))

# True DGP has NO INTERACTION EFFECT
y <- 1 + 2 * X_int + 3 * X_cov + 4 * (group=="B") + rnorm(100, sd = 4)
{% endhighlight %}

Notice that the true DGP has no interaction effect. However, if we use split sample analysis, we will see that $$\beta_{int}$$ is insigificant in group $$A$$, and significant in group $$B$$. Hence, we would wrongly conclude that there is an interaction effect between $$X_{int}$$ and $$G$$.


{% highlight r %}
data <- data.frame(y, X_int, X_cov, group)
stargazer(
  lm(y ~ X_int + X_cov, data = data[data$group == "A", ]),
  lm(y ~ X_int + X_cov, data = data[data$group == "B", ]),
  keep.stat = c("n"), column.labels = c("group A", "group B"), type = 'html'
)
{% endhighlight %}


<table style="text-align:center"><tr><td colspan="3" style="border-bottom: 1px solid black"></td></tr><tr><td style="text-align:left"></td><td colspan="2"><em>Dependent variable:</em></td></tr>
<tr><td></td><td colspan="2" style="border-bottom: 1px solid black"></td></tr>
<tr><td style="text-align:left"></td><td colspan="2">y</td></tr>
<tr><td style="text-align:left"></td><td>group A</td><td>group B</td></tr>
<tr><td style="text-align:left"></td><td>(1)</td><td>(2)</td></tr>
<tr><td colspan="3" style="border-bottom: 1px solid black"></td></tr><tr><td style="text-align:left">X_int</td><td>0.606</td><td>1.801<sup>***</sup></td></tr>
<tr><td style="text-align:left"></td><td>(0.616)</td><td>(0.419)</td></tr>
<tr><td style="text-align:left"></td><td></td><td></td></tr>
<tr><td style="text-align:left">X_cov</td><td>3.691<sup>***</sup></td><td>2.458<sup>***</sup></td></tr>
<tr><td style="text-align:left"></td><td>(0.595)</td><td>(0.394)</td></tr>
<tr><td style="text-align:left"></td><td></td><td></td></tr>
<tr><td style="text-align:left">Constant</td><td>0.504</td><td>4.563<sup>***</sup></td></tr>
<tr><td style="text-align:left"></td><td>(0.393)</td><td>(0.422)</td></tr>
<tr><td style="text-align:left"></td><td></td><td></td></tr>
<tr><td colspan="3" style="border-bottom: 1px solid black"></td></tr><tr><td style="text-align:left">Observations</td><td>100</td><td>100</td></tr>
<tr><td colspan="3" style="border-bottom: 1px solid black"></td></tr><tr><td style="text-align:left"><em>Note:</em></td><td colspan="2" style="text-align:right"><sup>*</sup>p<0.1; <sup>**</sup>p<0.05; <sup>***</sup>p<0.01</td></tr>
</table>

What's worrisome is that we really can't know how the statistical significance will turn out in a split sample analysis. Below I re-run exactly the same analysis, only using a different random seed, and we now conclude (correctly, but with the wrong methodology) that there's no interaction effect.


<table style="text-align:center"><tr><td colspan="3" style="border-bottom: 1px solid black"></td></tr><tr><td style="text-align:left"></td><td colspan="2"><em>Dependent variable:</em></td></tr>
<tr><td></td><td colspan="2" style="border-bottom: 1px solid black"></td></tr>
<tr><td style="text-align:left"></td><td colspan="2">y</td></tr>
<tr><td style="text-align:left"></td><td>group A</td><td>group B</td></tr>
<tr><td style="text-align:left"></td><td>(1)</td><td>(2)</td></tr>
<tr><td colspan="3" style="border-bottom: 1px solid black"></td></tr><tr><td style="text-align:left">X_int</td><td>3.392<sup>***</sup></td><td>1.663<sup>***</sup></td></tr>
<tr><td style="text-align:left"></td><td>(0.839)</td><td>(0.458)</td></tr>
<tr><td style="text-align:left"></td><td></td><td></td></tr>
<tr><td style="text-align:left">X_cov</td><td>1.143</td><td>2.790<sup>***</sup></td></tr>
<tr><td style="text-align:left"></td><td>(0.824)</td><td>(0.480)</td></tr>
<tr><td style="text-align:left"></td><td></td><td></td></tr>
<tr><td style="text-align:left">Constant</td><td>0.813<sup>*</sup></td><td>4.856<sup>***</sup></td></tr>
<tr><td style="text-align:left"></td><td>(0.462)</td><td>(0.474)</td></tr>
<tr><td style="text-align:left"></td><td></td><td></td></tr>
<tr><td colspan="3" style="border-bottom: 1px solid black"></td></tr><tr><td style="text-align:left">Observations</td><td>100</td><td>100</td></tr>
<tr><td colspan="3" style="border-bottom: 1px solid black"></td></tr><tr><td style="text-align:left"><em>Note:</em></td><td colspan="2" style="text-align:right"><sup>*</sup>p<0.1; <sup>**</sup>p<0.05; <sup>***</sup>p<0.01</td></tr>
</table>

**Take-away:** Don't use split sample analysis to show heterogenous treatment effect for one variable of interest.

## What if you do want to examine heterogenous treatment effect for all variables?

In this case, I would recommend [a multi-level model](http://www.stat.columbia.edu/~gelman/arm/), which allows co-varying intercepts and coefficients across groups.
