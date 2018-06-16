---
title:     "A Short Introduction to Data Analytics"
excerpt:   "that gives you enough to do for your first 3 months towards a job in 1 year."
date:       2018-06-15 12:00:00
---

Data analytics is the use of data to help make business decisions. Framed this way, it's nothing new. When [humans invented writing in 3500 BC to track debts](https://sites.utexas.edu/dsb/tokens/the-evolution-of-writing/), they were already using data to conduct business. So when the boss yells at you for the sales figure from last month, be comforted by the knowledge that you are part of an ancient tradition.

What is new about present-day data analytics is that there is a lot more data and a lot more computing power to analyze it. We no longer just query the data with preconceived questions like "What was last month's sales?" We can now mine the data for answers we don't even expect. As the legend goes, when Walmart analyzed its massive sales data, it discovered that beers and diapers were frequently bought together on Friday by male customers. As it turns out, buying diapers on Friday reminds young fathers of their defunct social life and prompts them to buy beers to compensate. Once the relationship was discovered, it was easy to figure out the reason and reorganize the store so that the beers are next to the diapers. But the relationship was so surprising that, without big data, no one would look for it in the first place.<sup>[1](#footnote1)</sup>

[Despite being half-fiction](https://web.archive.org/web/20180423013132/http://www.dssresources.com/newsletters/66.php), the beer-and-diaper fable does convey how data can inform business decisions in new ways. In the 1990s, only Walmart and a handful of giants could mine their data. Today, even mid-size organizations sending out email marketing campaigns have enough data and tools to predict customer engagement. That means more jobs for you.

# Skills you need for data analytics

If data analytics is the use of data to help make business decisions, then the analyst must also have both data skills and business sense. Every job and project has a different focus, but they are always a mix of the following four skills:

1. Defining the problem (business sense/domain knowledge)
2. Getting the data (data skill/programming)
3. Building a model (data skill/statistics)
4. Packaging into a deliverable (business sense/communication, or data skill/programming)

To find the job that you like and are qualified for is to go beyond job titles and identify whether the job has the mix of skills that fit your profile. Indeed, the field is young enough that titles---data analyst, data scientist, business intelligence, data engineer, quantitative analyst---are still ill-defined. Here are simplified examples of different "data science" jobs with increasing levels of skill and compensation:

- LA fitness wants a quarterly report on sales performance of its gym across the US. (1) Jon comes up with different sales-related metrics: total sales, sales per employee, sales per square foot, etc. (2) He gets the data from another department in the company, likely in the form of an Excel spreadsheet. (3) He makes Excel plots showing the trend in sales and comparison across regions. (4) He makes a PowerPoint presentation for his boss.

- Capital One wants to reduce customers' default rate. (1) Julie asks her industry colleagues to figure out how to define a customer as defaulting on their credit card debt. (2) She then gets customer data from credit rating agencies, likely in the form of CSVs or a database. She cleans it up to match the customer segments that Capital One targets. (3) She builds a statistical model to predict whether a customer will default, taking care to ensure that her model follows regulations against discriminating based on race or gender. (4) She wrote up a description of the model and handed it over to the engineering team, who will turn the model into an automated system that flags incoming customers as high default risk.
   
- Facebook wants to know if its new design for the newsfeed increases user engagement. (1) Bob brainstorms what metrics measure user engagement. Is it the number of time an user click on a newsfeed item? The time spent on Facebook? The number of likes and shares? (2) Bob then talks to the data engineering team to get access to the data, likely stored in some internal data warehouse. If the metrics Bob wants is not yet tracked, he has to work with software engineers to implement those trackers himself. (3) Bob develops models to analyze the data, paying attention to whether different customer segments react differently. (4) Bob recommends whether to keep the design changes. He also develops a system that automatically analyzes customer engagement whenever there is a new design.

# How to get data skills

An painter needs to know both brush techniques and color theory---how to paint and what to paint. Likewise, you need both programming tools and statistics---how to build a model and what model to build.
   
## Programming

- SQL. The vast majority of businesses store their data in SQL database. Knowing SQL lets you query and manipulate them. This is the one skill that virtually all data analysts will use.
  
  Resources (pick 1):
  + [Stanford's online SQL course](https://lagunita.stanford.edu/courses/DB/2014/SelfPaced/about): FREE. Self-contained, no-prerequisite, modularized course that explains both the theory and the practicals of database. As a start, you can focus on just SQL, skipping XML, JSON, and other advanced topics. Highly recommended.
  + [SQLzoo](https://sqlzoo.net/): FREE. A series of SQL practice problems with increasing difficulty. Highly recommended.

- R / Python. Once you got the data, you need to clean, merge, and build models. Either R or Python works equally well. If you are an absolute beginner to programming, R is better because its learning materials are always and directly related to data analysis. If you have prior programming experience, Python may be more familiar and can speed up your learning progress.
  
  When I first learned R and Python, there wasn't as much resources as there is now. Below are resources that have good reviews, but I have not personally used them.
  
  Resources for R. Pick 1 of:
  + [Hadley Wickham's R for data science](http://r4ds.had.co.nz/): FREE. Written by Hadley Wickham, one of the most influential R contributors, the book teaches you R's modern tools to tackle fairly realistic problems. Highly recommended--- it's the best Intro to R resources in my opinion. The only, albeit small, downside is that it focuses on teaching [the *tidyverse*](https://www.tidyverse.org/), a set of modern R tools. Many people still use *base R*, which you can learn in other resources.
  + [DataCamp's Intro to R](https://www.datacamp.com/courses/free-introduction-to-r). A good thing about DataCamp is that they have a list of follow-up courses covering data science in R. If you want to stick with one platform, this could be a good choice.
  + [John Hopkins' R Programming course](https://www.coursera.org/learn/r-programming). FREE. I used this course to teach R to Duke's Political Science PhD and can vouch that it covers enough (base) R for most people.

  Resources for Python. Pick 1 of:
  
  + [Allen Downey's Think Python](http://greenteapress.com/wp/think-python/). FREE. How I first learned Python and programming. It is *not* about data analysis, just Python in general.
  + [Zed Shaw's Learn Python the hard way](https://learnpythonthehardway.org/). Another oft-recommended introduction to Python. Personally I prefer Downey's in-depth explanation.

  Then:
  
  + [Wes McKinney's Python for data analysis](http://shop.oreilly.com/product/0636920023784.do). It introduces the Python ecosystem for data analysis, including Pandas, NumPy, and IPython. Highly recommended. Could be difficult if you are new to Python.

## Statistics

If you are in school, I highly recommend taking classes from your Statistics department. Compared to programming, math is much harder to self-teach. When you make a mistake writing code, either the computer will throw an error or you will be able to see the wrong output. When you make a mistake doing math, there is no blinking red light telling you something is wrong. Without a teacher checking your work, it is very easy to go into dead-ends or hold on to a wrong understanding for months.

If you are not in school, consider taking online classes.

- [Andrew Ng's Machine Learning](https://www.coursera.org/learn/machine-learning). FREE. The definite introduction to machine learning course. Not too math heavy, but still convey the materials correctly. The only downside is that the course uses Matlab, not R or Python.

- [OpenIntro Statistics](https://www.openintro.org/stat/textbook.php?stat_book=os). FREE. Highly recommended. An increasingly popular introduction to Statistics using R. I have not used the book, but can vouch for the teaching skills and enthusiasm of the Duke professors who developed the course.

Other textbooks to complement your Statistics education.
  
- [Introduction to Statistical Learning](http://www-bcf.usc.edu/~gareth/ISL/). FREE. Highly recommended. A very insightful introduction to machine learning using R. The book is not heavy on math yet does not sacrifice rigor. The authors also write [Elements of Statistical Learning (FREE)](https://web.stanford.edu/~hastie/ElemStatLearn/), a more math-heavy and comprehensive book that is *the textbook* on machine learning.
    
- [Raschka's Python Machine Learning](https://sebastianraschka.com/books.html). A practical, code-heavy book on machine learning using Python. I like the realistic tips in this book.

(Optional) Other notable textbooks to upgrade your Statistics:

- [Frank Harrell's Regression Modeling Strategies](http://biostat.mc.vanderbilt.edu/wiki/Main/RmS)

- [Max Kuhn's Applied Predictive Modeling](https://www.amazon.com/Applied-Predictive-Modeling-Max-Kuhn/dp/1461468485)

- [Gelman and Hill's Data Analysis Using Regression and Multilevel/Hierarchical Models](https://www.amazon.com/Analysis-Regression-Multilevel-Hierarchical-Models/dp/052168689X)

- [Bayesian Data Analysis (BDA)](https://www.amazon.com/Bayesian-Analysis-Chapman-Statistical-Science/dp/1439840954)
 
(Optional) If you want to master Statistics and have more than 1 year before finding a job, you can learn Linear Algebra and some Calculus for a stronger mathematical foundation. [Albert Strang's Linear Algebra (FREE)](https://ocw.mit.edu/courses/mathematics/18-06-linear-algebra-spring-2010/) is an oft-recommended resource. [A short note from Andrew Ng's machine learning class (FREE)](http://cs229.stanford.edu/section/cs229-linalg.pdf) is also a great refresher.

# How to get business sense 

Companies expect you to come in with technical skills, not necessarily with industry knowledge. That makes sense. They know their industry, so they are confident they can teach you that. They don't know data analytics, so they want you to have the skills ready.
    
That said, interviews often have questions to gauge general "business sense." To me, business sense is the simply ability to make an educated guess about how a company makes money. Or, once given information about how a company makes money, come up with ways that it can make more money.

If you asked me how high fashion brands make money (which I know nothing about), I would guess that their profit comes from charging premium prices rather than cutting cost. If that's true, then using data to optimize their production shouldn't be the focus. We can't really use data to predict next year's trend either---that seems up to the whims of a coterie of designers and celebrities. Since the brand is the driver of profit, perhaps in this case data is best used to measure the impact of our marketing channels. Is this celebrity's endorsement worth the dollars we pay? Is our marketing reaching the next generation of big spenders? It's okay for these ideas to wrong since they are guesses. The point is to be educated while guessing.

Developing business sense isn't unique to data analytics. In fact, I develop mine by copying how management consultants prepare for their case interviews: browse the Wall Street Journal, read case studies, and follow industry news. Data science blogs are an excellent source of case studies. I particularly like [Airbnb](https://medium.com/airbnb-engineering), [Google](http://www.unofficialgoogledatascience.com/), [Stitch Fix](https://multithreaded.stitchfix.com/blog/), and my company, [Civis Analytics](https://medium.com/civis-analytics). [Hacker News](https://news.ycombinator.com/), a Reddit-like news aggregator, is another excellent source of tech news.
    
# Learning how to learn

Like many fields in tech, data analytics is constantly evolving. The programming languages and statistical models you use today will be obsolete in five years. Learning is the only constant in this evolving field, so it's important to learn how to learn.

When you get stuck, learn how to use Google to find your answers. There is not a day that I don't Google "What is [a statistical term]," or "How to do X [in Python / R]." Very often you will see results from [StackOverflow](stackoverflow.com) and [Cross Validated](https://stats.stackexchange.com/), Q&A sites dedicated to programming and statistics. In your first 3 months learning data analytics, I guarantee that all of your beginner questions have already been asked and answered there. Get used to these Q&A sites.

What's a lot trickier is how to Google what you don't know in the first place. Some of my favorite Google queries to find out my knowledge gaps are:

- assumptions of model X
- advantages and disadvantages of model X / technology Y
- alternatives to model X / technology Y
- difference between model X and [let Google autocomplete]

Textbooks and courses cover a topic systematically, and is also a great way to fill knowledge gaps. I often Google for "best textbook / Coursera course on topic X" for suggestions.

Newsletters and discussion boards are another way to get exposure to topics you are not aware of. I subscribe to [Data Elixir](https://dataelixir.com/) and read [Hacker News](https://news.ycombinator.com/).

# Finding data analytics jobs

The job market for data analytics is a hot mess. It's hot because everyone wants a part of the new field. It's a mess because the field is so new hiring is not yet standardized.

Since hiring isn't standardized, job titles aren't that meaningful. In theory, data scientists are more prestigious, demanding, and well-paid than analysts. In practice, I have seen data scientists that write rote reports all days. On the other hand, Google's quantitative analysts are a bunch of PhDs working on tough technical problems.

My recommendation is to use titles as a rough indicator. Focus instead on the job description, figuring out whether its mix of business and data skills match your profile.

Another consequence of the field being so young is that hiring managers don't know how to hire yet. So they are a conservative, skittish bunch that would rather reject a good candidate than hiring a bad one. They tend to rely on auxiliary signals, such as a technical graduate degrees. To lessen their fear, you should build and post a data project on your blog. This serves as evidence of your data skills---an extra signal that they can evaluate.

Tailor your project to fit the mix of business and data skills that your dream company wants. For purely technical projects, [Kaggle](https://www.kaggle.com/** gives you cleaned dataset with a defined metrics so that you can focus on the modeling part.

# Glossary

**C / C++**: low-level programming language that is sometimes used to speed up Python and R. Can be safely ignored as beginners.

**Hadoop**: a suite of software for running data tasks across clusters, developed when some companies have too much data to analyze on a single computer. Can be safely ignored as beginners.

**Javascript**: programming language for the web, often used to design online interactive visualization. Can be safely ignored as beginners.

**Python**: one of the two most popular programming languages in data science (the other is R). Doing data analysis in Python means using a suite of scientific libraries, including pandas, numpy, scipy, and scikit-learn. As a general-purpose programming language, Python can better fit into a software pipeline than R. An excellent choice for those with prior exposure to programming.

**R**: one of the two most popular programming languages in data science (the other is Python). It's designed first and foremost for data analysis. All statisticians use R, so the latest models will often be available as an R package. New tools are constantly added to R, notably [*the tidyverse*](https://www.tidyverse.org/), to make data analysis more convenient. An excellent choice for beginners.

**SQL**: what you use to query and manipulate relational database. It's very common
and a must-know.
 - NoSQL: alternative database technologies that have more speed and flexibility at the cost of less reliability. It's only used at giants (e.g. Google, Facebook** and can be safely ignored as a beginner.

**VBA**: programming language for Excel and other Office products. Many businesses today still use Excel for their data storage and analysis despite serious drawbacks, namely difficulty in reproducing an analysis, inability to hold large datasets, and lack of state-of-the-arts statistical tools. If the jobs you target mainly use Excel, VBA is an important tool to learn.

**SAS**: a programming language designed for data analysis, frequently used before R came to the scene. Due to decades-long contract, SAS is still widely used in pharmaceuticals, government, and insurance. Unless your target jobs use SAS, learn R or Python instead.

**Stata**: a programming language designed for data analysis, frequently used by economists. It's also increasingly replaced by R and Python.

<a name="footnote1">1</a>: Not only can modern data analytics discover relationships we don't expect, it can also find relationships we can't comprehend. Black box models like Random Forest or Neural Network can take an input, run it through a function complicated beyond human interpretation, and produce highly accurate predictions. They perform well even when we don't know how they do it.
