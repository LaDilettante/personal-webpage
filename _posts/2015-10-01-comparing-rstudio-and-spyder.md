---
title:      "Comparing RStudio and Spyder"
subtitle:   "for the data analyst that switches between R and Python."
date:       2015-10-01 12:00:00
---

Recently I have been searching for a Python's IDE that is similar to R's RStudio. While ipython notebook is better than text editor for data analysis, it suffers from two problems still:

- **version control is difficult** as output in the notebook may change even though the code doesn't (e.g. when there's a randomized element in the analysis).
- **the input-output layout is meant to be narrative**, which is not ideal for analysis. For example, when there are many plots, I have to scroll up and down a lot to navigate. Because of its focus on narrative, ipython notebook resembles knitr more than RStudio.

After much searching, I found [Spyder](https://pythonhosted.org/spyder/), which is an almost-perfect equivalent of RStudio. It comes pre-packaged with Anaconda and works seamlessly with IPython and the suite of data science libraries (numpy, pandas, etc.)

Here I compare the most important features of RStudio and Spyder so that one can make a quick switch between the two. One could read Spyder's tutorial, but for an experienced data analyst much of it is fluff.

## RStudio and Spyder comparison

Function | Rstudio | Spyder
--- | --- | ---
Run | Ctrl - R | F5 to run the entire script <br> F9 to run selection or line
Re-Run | Ctrl + Shift + P | Ctrl + F6
Help | help() | help() -- Will also show the doc string of your own function
     | F1 with cursor over object | Ctrl-i with cursor over object
Clean workspace | `rm(list = ls())` | `%reset` <br> `%reset -f` to skip confirmation
Auto-completion  | TAB | TAB
Go to Source | F2 with cursor over object | Ctrl+Left Click on object
Debug | debug() <br> debugonce() | Ctrl + F5 starts pdb <br> `%debug` starts debug where exception occurs
Search across Files | Ctrl + Shift + F | Ctrl + Shift + F
Variable Viewer | `Environment` pane (top right) | `Variable Explorer` pane (top right)

## Tweaks to make Spyder more like Rstudio

- Plot in a separate windows (instead of default inline): `Tools, Preferences, Ipython Console, Graphics` and under Graphics Backend select “automatic” instead of “inline”

## Unique Spyder features and tips

- Console: Use ipython console instead of python console
- Style: Go to `Preferences > Editor > Code Introspection/Analysis` and select the tickbox next to Style analysis (PEP8)
- Cell (similar to ipython notebook): `Ctrl+Enter` executes the current cell. A cell is defined as the code between two lines which start with the agreed tag `#%%`. Shift+Enter executes the current cell and advances the cursor to the next cell