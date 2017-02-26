---
title:      "Fix the libjvm.so file not found error"
excerpt:   "I encounter this problem whenever I try to use rJava on Ubuntu + Rstudio, and here is the solution."
date:       2015-02-01 12:00:00
---

I encounter this problem whenever I try to use `rJava` on Ubuntu + Rstudio, so I decided to write it down.

You'll see this error message if you try to load the `rJava` package or anything else that depends on it (`psData` in my case):

{% highlight R %}
> library(psData)
Error : .onLoad failed in loadNamespace() for 'rJava', details:
  call: dyn.load(file, DLLpath = DLLpath, ...)
  error: unable to load shared object '/home/anh/Rlibs/rJava/libs/rJava.so':
  libjvm.so: cannot open shared object file: No such file or directory
Error: package or namespace load failed for ‘psData’
{% endhighlight %}

The issue boils down to Rstudio being unable to find the shared file `libjvm.so`. We need to include the path towards `libjvm.so` (i.e. the Java library folder) in [LD_LIBRARY_PATH](https://www.google.com/search?client=ubuntu&channel=fs&q=what+is+ld_library_path+linux&ie=utf-8&oe=utf-8), the environment variable that points Ubuntu and its application towards shared library.

A wrinke: If we set `LD_LIBRARY_PATH` in `/etc/environment`, `library(rjava)` can be loaded via terminal `R`. However, Rstudio doesn't look into `/etc/environment` and thus is still not aware of the new `LD_LIBRARY_PATH`.

**The upshot**: Set `LD_LIBRARY_PATH` in `~/.profile` to make it available to all desktop applications, including Rstudio (as suggested by [Ubuntu wiki article on persistent environment variable](https://help.ubuntu.com/community/EnvironmentVariables#Persistent_environment_variables)).

**Instructions**:

- Inside `~/.profile`, add the path to `libjvm.so` to `LD_LIBRARY_PATH` (you may have a different path from mine):

{% highlight bash %}
export LD_LIBRARY_PATH=/usr/lib/jvm/java-7-oracle/lib/amd64:/usr/lib/jvm/java-7-oracle/jre/lib/amd64/server
{% endhighlight %}

- Log out and in or restart your computer so that Ubuntu reloads `~/.profile`. 
- Then make R update its java configuration:

{% highlight bash %}
sudo R CMD javareconf
{% endhighlight %}

That's it. `library(rJava)` should run after restarting Rstudio.