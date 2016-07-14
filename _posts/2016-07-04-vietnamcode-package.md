---
title: "Use vietnamcode package to convert Vietnam's provincial ID"
excerpt: "No more struggling with diacritics, different spellings, and various coding schemes."
---



If you have ever struggled with various coding schemes of Vietnam's provincial IDs like me, there's a solution! I wrote the `vietnamcode` package to convert across all coding schemes, including provincial names with or without diacritics.

The main function is `vietnamcode` -- here's how flexible it is:


{% highlight r %}
library(vietnamcode)
vietnamcode(c("HCMC", "TP HCM", "Tp. Ho chi Minh"), 
            origin = "province_name", destination = "province_name_diacritics")
{% endhighlight %}



{% highlight text %}
## [1] "TP Hồ Chí Minh" "TP Hồ Chí Minh" "TP Hồ Chí Minh"
{% endhighlight %}



{% highlight r %}
vietnamcode(c("Bac Kan", "Bắc Kan", "Bac Can", "bac can"),
            origin = "province_name", destination = "pci")
{% endhighlight %}



{% highlight text %}
## [1] "54" "54" "54" "54"
{% endhighlight %}

The coding schemes supported are:

- province_name
- province_name_diacritics
- enterprise_census (old and new)
- PCI

If you find any bug, please let me know at [my package on github](http://github.com/LaDilettante/vietnamcode). I hope you find it useful. Thanks to the people behind the package [`countrycode`](https://github.com/vincentarelbundock/countrycode) for inspiration.
