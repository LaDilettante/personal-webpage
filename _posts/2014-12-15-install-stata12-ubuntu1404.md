---
title:      "Install Stata 12 on Ubuntu 14.04"
subtitle:   "Dealing with missing libraries libgnomeprint2.2-0 & libgtksourceview-1.0.so.0."
date:       2014-12-15 12:00:00
---
Ubuntu 14.04 no longer makes available several libraries that are necessary to run Stata 12 (specifically, `libgnomeprint2.2-0` and `libgtksourceview2.0-0`). In this post I show how to install those missing libraries (and also how to figure out the way to do it for similar occasions).

## The problem

If you follow [Stata 12 on Ubuntu installation guide](http://eduardgrebe.net/2012/10/installing-stata-12-on-ubuntu-12-04/), at one point you have to install these libraries for GUI Stata to work (command line Stata works without them):

{% highlight bash %}
apt-get install libgtksourceview2.0-0 libgnomeprint2.2-0
ln -s /usr/lib/libgtksourceview-2.0.so.0 /usr/lib/libgtksourceview-1.0.so.0
{% endhighlight %}

The problem is that Ubuntu 14.04 no longer makes available these packages.

## The solution

- Go to http://packages.ubuntu.com/ and search for the libraries we want (`libgtksourceview2.0-0` & `libgnomeprint2.2-0`). Make sure to search for them in **ANY** distribution, not just in **trusty**
- We find out that they are available for Ubuntu 12.04 precise ([here's the page for `libgnomeprint2.2-0`](http://packages.ubuntu.com/precise/libgnomeprint2.2-0))
- We then go to its [download page](http://packages.ubuntu.com/precise/amd64/libgnomeprint2.2-0/download)
- We can download the file directly, but as the instruction on the page says, it is better to install via Ubuntu package manager. We just need to add these old repositories to Ubuntu 14.04 apt sources by:
	- `sudo gedit /etc/apt/sources.list` and add this line `deb http://cz.archive.ubuntu.com/ubuntu precise main universe`. You can use any mirror site (as listed on the [download page](http://packages.ubuntu.com/precise/amd64/libgnomeprint2.2-0/download)) instead of `cz.archive.ubuntu.com` 
	- `sudo apt-get update` so that our package manager is aware of the new source
	- Finally, `sudo apt-get install libgnomeprint2.2-0 libgtksourceview2.0-0`

