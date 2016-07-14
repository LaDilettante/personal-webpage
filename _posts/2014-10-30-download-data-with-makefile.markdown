---
title:      "Download data with Makefile"
subtitle:   "to improve reproducible research."
date:       2014-10-30 12:00:00
---

Since I have my R scripts carefully labeled in sequence, anyone can download my script and reproduce my research from raw data to the final document. The only step that is not yet reproducible in my research pipeline is how to get the same raw input data. Recently I've come up with two solutions:

1. When possible, use R packages to download raw data directly from database API. For example, we can directly access the World Bank's World Development Indicators (`library(WDI)`), the Polity Score and the Database of Political Institutions (`library(psData)`). This is the best case scenario -- given your script, any reader can simply hit Run to download the data, do analysis, and output results in one go.

2. When there is no available API and we have to go to various authors' website to download their dataset, this can be automated by using `Makefile`. Read [this](http://kbroman.org/minimal_make/) brief tutorial of how to use `Makefile` for reproducible research. You need to understand `Makefile` dependency structure to follow my script below.

I'll wait.

.
.
.

### Code

Okay, here's how to use `Makefile` to download, rename, and put data in the appropriate directory. As an example, I'm downloading a dataset on authoritarian regimes by [Geddes, Wright, and Frantz](http://sites.psu.edu/dictators/).

{% highlight bash %}
all: GWF_Autocratic_Regimes_1_2

GWF-Autocratic-Regimes-1.2.zip:
	curl -o GWF-Autocratic-Regimes-1.2.zip "http://sites.psu.edu/dictators/wp-content/uploads/sites/12570/2014/07/GWF-Autocratic-Regimes-1.2.zip"

GWF_Autocratic_Regimes_1_2: GWF-Autocratic-Regimes-1.2.zip
	unzip GWF-Autocratic-Regimes-1.2.zip
	mv GWF\ Autocratic\ Regimes\ 1.2 GWF_Autocratic_Regimes_1_2
	find ./GWF_Autocratic_Regimes_1_2 -exec touch {} \;
{% endhighlight %}

Code explanation:

* `curl` is the command to download file. The `-o new_name` option allows you to rename the downloaded file. In this case I keep it the same.

* `unzip` unarchives the downloaded file (`GWF-Autocratic-Regimes-1.2.zip`). In this case, it produces a folder called `GWF Autocratic Regimes 1.2`

* Since it's good practice not to have spaces in file path, I rename the folder with `mv GWF\ Autocratic\ Regimes\ 1.2 GWF_Autocratic_Regimes_1_2`

* Finally, we need to recursively `touch` every files inside `GWF_Autocratic_Regimes_1_2` so that these files have a newer modification timestamp than that of `GWF-Autocratic-Regimes-1.2.zip`. Had we not done that, files inside `GWF_Autocratic_Regimes_1_2` was last modified at whenever the dataset was created. Since this timestamp is older than `GWF-Autocratic-Regimes-1.2.zip`, `make` will mistakenly think that it needs to update these files and thus keeps re-running the `unzip`.

We do that by `find ./GWF_Autocratic_Regimes_1_2 -exec touch {} \;`. See more explanation and options in [this Stackoverflow answer](http://superuser.com/questions/432382/how-do-i-recursively-touch-files-matching-a-pattern).

### How to run

You can download any particular data folder by running `make GWF_Autocratic_Regimes_1_2`, `make another_folder`, etc.

Alternatively, you can list all the names in `all: GWF_Autocratic_Regimes_1_2 other_folder1 other_folder2` and run `make all`.