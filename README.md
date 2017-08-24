# Minimal Mistakes

**[Minimal Mistakes](http://mmistakes.github.io/minimal-mistakes)** is a two column responsive Jekyll theme perfect for powering your GitHub hosted blog built. Compatible with Jekyll 3.0 and up.

## Minimal Mistakes is all about:

* Responsive templates. Looking good on mobile, tablet, and desktop.
* Gracefully degrading in older browsers. Compatible with Internet Explorer 8+ and all modern browsers.
* Minimal embellishments -- content first.
* Optional large feature images for posts and pages.
* Simple and clear permalink structure.
* [Custom 404 page](http://mmistakes.github.io/minimal-mistakes/404.html) to get you started.
* Support for Disqus Comments

![screenshot of Minimal Mistakes theme](http://mmistakes.github.io/minimal-mistakes/images/mm-theme-post-600.jpg)

See a [live version of Minimal Mistakes](http://mmistakes.github.io/minimal-mistakes/) hosted on GitHub.

## Getting Started

Minimal Mistakes takes advantage of Sass and data files to make customizing easier. These features require [Jekyll 2.x](https://github.com/mmistakes/minimal-mistakes/releases/tag/2.1.3) and will not work with older versions of Jekyll.

To learn how to install and use this theme check out the [Setup Guide](http://mmistakes.github.io/minimal-mistakes/theme-setup/) for more information.

## Anh Le's modifications

### Setting up
- `bundle update`
- `bundle clean --force` if necessary

### Copy to server
- `gem install github-pages` if jekyll is not set up
- Go to `/media/aql3/personal-webpage`, `git pull`
- `jekyll build`
- `cd ..`
- `sudo rsync -av personal-webpage/_site/ public_html/` (a = all, v = verbose)

### Some commands to remember

To write Rmd blog post in Rstudio, make sure that [`build.R`](https://raw.githubusercontent.com/yihui/knitr-jekyll/gh-pages/build.R) is included in the root jekyll directory (this is undocumented):
- `which jekyll`
- `servr::jekyll(command='/home/anh/.rvm/gems/ruby-2.3.0/wrappers/jekyll build')`

### base_path

Remove {{ site.url }} from {{ site.url }}{{ site.baseurl }} so that local development works
