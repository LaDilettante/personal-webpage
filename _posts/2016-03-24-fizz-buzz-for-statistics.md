---
title: "FizzBuzz for Statistics"
excerpt: "A compilation of basic(?) tests for statistical competence."
---

Inspired by [a Reddit thread](https://www.reddit.com/r/statistics/comments/4c2aoh/good_fizz_buzztype_questions_for_interviewing/) and [the original FizzBuzz for programmers](http://blog.codinghorror.com/why-cant-programmers-program/).

# General

1. Explain p-value and confidence interval.

# Experiment

1. Explain why, when applicable, the paired t-test is usually preferable over an unpaired t-test. [(credit)](https://www.reddit.com/r/statistics/comments/4c2aoh/good_fizz_buzztype_questions_for_interviewing/d1eh0z4)

# Regression

1. Interpreting interaction term: The model is $$y = \beta_0 + \beta_1 X_1 + \beta_2 X_2 + \beta_3 X_3 + \epsilon$$. What is the change in $$y$$ given 1 unit increase in $$X_1$$?

# Probability

1. I fire two missiles at a ship at the same time. Each independently has a 60% chance of hitting and sinking it. I turn to yell at somebody, and when I turn back around, the ship is sinking. what's the probability both missiles hit it? [(credit)](https://www.reddit.com/r/statistics/comments/4c2aoh/good_fizz_buzztype_questions_for_interviewing/d1ejhex)

2. Sum of two random variables

# General (solution)

1. p-value and confidence interval

- *p-value* is the probability of getting observed, or more extreme, data given that the null hypothesis is true. **Wrong: p-value is the probability that the null hypothesis is true.**

- If we repeat an experiment many many times, we would expect that X% of the times the true parameter will fall within the X% confidence interval of that parameter.

# Experiment (solution)

1. Paired t-test takes into account the paired structure, which reduces the variance of the difference.
Consider two paired observations, whose outcomes are denoted $$X$$ and $$Y$$. We are interested in the difference $$Z = X - Y$$.

$$
\begin{align}
Var(Z) &= Var(X - Y) = Var(X) + Var(Y) - 2Cov(X, Y) \\
\end{align}
$$

Notice that if $$Cov(X, Y) > 0$$, e.g. paired units tend to have similar outcomes, then $$Var(Z)$$ is smaller.

# Regression (solution)

1. Interpreting interaction term:

$$
\frac{\partial}{\partial X_1} y = \beta_1 + \beta_3 X_2
$$

Key point: the marginal effect of $$X_1$$ on $$y$$ *depends on the value of $$X_2$$*

# Probability (solution)

1. After firing the two missiles, 4 disjoint events can happen:

- P(both hit) = 0.6 * 0.6 = 0.36
- P(only 1st hits) = 0.6 * 0.4 = 0.24
- P(only 2nd hits) = 0.4 * 0.6 = 0.24
- P(none hits) = 0.4 * 0.4 = 0.16

P(both hit &#124; ship sinks) = P(both hit &#124; at least one hit) = $$\frac{0.36}{0.36 + 0.24 + 0.24} = 0.43$$
