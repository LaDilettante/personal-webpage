---
title: "How to run MCMC in parallel"
excerpt: "I have to run Markov chain Monte Carlo (MCMC) simulations that each takes hours and requires parameter configuration. Here's how I parallelize it."
comments: true
categories:
  - computing
tags:
  - mcmc
---

I have to run Markov chain Monte Carlo (MCMC) simulations that each takes hours and requires parameter configuration. On this particular day, it was a Metropolis Hastings algorithm for which I have to specify the step size of the proposal distribution.

After getting sick of manually changing the step size each time, I gave in and parallelize the MCMCs, running all of them in one go. Given the big time cost of each MCMC, I really don't want one failure to jeopardize the rest. So I wrote a parallelized script that accomplishes the following goals:

1. The result of each chain is saved as soon as it is done

2. The progress is tracked in a log file

I used the `foreach` package to parallelize plus some tricks to create an informative log file and file names. Below is the code for `my_parallel_mcmc.R`:

{% highlight R %}
# We first create a grid of "tuning parameters"
# (proposal step size in my case of Metropolis Hastings)

param1 <- c(0.01, 0.05, 1, 2, 5)
param2 <- c(0.01, 0.05, 1, 2, 5)
tuning_grid <- expand.grid(param1=param1, param2=param2)

# Choose how many cores you want to use
registerDoMC(cores = detectCores() / 2)

# Clear out log file
writeLines(c(""), "my_mcmc.log")

# Finally, run MCMC in parallel
foreach(param1 = tuning_grid$param1, param2 = tuning_grid$param2) %dopar% {
  sink("my_mcmc.log", append=TRUE) # Write to log file

  # Your individual MCMC wrapped inside a function
  f_mcmc(data = my_data, max_iter = 20000,
         param1=param1, param2=param2)
}
{% endhighlight %}

Inside your `f_mcmc()` function, it should 1) periodically print out a progress report, and 2) save the MCMC result at the end.

{% highlight R %}
f_tslogit <- function(data = data, max_iter = 10000,
                      param1, param2) {
... # Data processing

# Big MCMC loop starts here
for (i in 1:max_iter) {
    ... # MCMC stuff. In my case, drawing proposed value, computing acceptance ratio, etc.

    # 1) Periodically print progress report every 1000 iterations
    # The printed output will be logged to the log file specified above
    if (i %% 1000 == 0) cat("Current iter: ", i, "\n")

    # 2) Save result to a file at the end
    # Note how the file name needs to be unique for each MCMC chain
    # For an informative name, I include both the param values and the time stamp
    outfile = paste("my_MCMC",
                    gsub("[ \\.]", "-", paste(param1, param2)), "_",
                    strftime(Sys.time(), format = "%m-%d_%H-%M"),
                    ".RData",
                    sep = "")
    save(results, file=outfile)

    # Finally, log a concluding message
    cat(outfile, done, Sys.time())
}
{% endhighlight %}

I used git and github to clone my script onto a remote cluster. From its terminal, I run this script with `Rscript my_parallel_mcmc_script.R`. To check the progress, I use `tail -f my_mcmc.log`. To keep the job running even after you disconnect from the remote cluster, use [tmux](http://askubuntu.com/questions/8653/how-to-keep-processes-running-after-ending-ssh-session).