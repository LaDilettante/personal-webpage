---
title:      "Usability testing for statistical software"
---

This summer, I worked at [Civis Analytics](https://www.civisanalytics.com/), a start-up building cloud platform for data scientists. As bona fide techies, our customers want to communicate with Civis' platform via code instead of web GUI, so we wrote an R client that lets them do so.

During the design process, I interviewed our in-house data scientists for their feedback. To prepare, I scoured the Internet for articles on UX interviews, most of which unfortunately geared towards consumer-grade web design. While the principles hold true, many tactics do not take into account the sense and sensibility of our deeply technical users. Below is how I molded those principles into tactics for interviewing technical users for statistical software.

### 1. Watch your users use your software

In principle, watching your users using your software is the gold standard of usability testing. This approach lets engineers break free from their [curse of knowledge](https://en.wikipedia.org/wiki/Curse_of_knowledge), experiencing vicariously how frustrating it can be for a user to use an unfamiliar system.

In practice, because our data scientists only had 30 minutes to spare, I couldn't expect them to actually sit down and use our software. So I gave the users a list of our IO function signatures and asked them to guess what the functions did based on that alone. Indeed, all of us have scanned function names in long manuals looking for the thing we need. If a function signature does not communicate what the function does, the design has already failed.

During this exercise, I noted down two signs of confusion: either 1) the user guessed wrong, or 2) the user was slow to guess, both of which call for a re-thinking of our design.

For example, I noticed that many users hesitated upon seeing the function `read_civis`:

```R
read_civis(sql("SELECT * FROM my_table"))
```

They had expected the `read_civis` function to take the SQL statement via an argument i.e. `sql = "SELECT * FROM my_table"`, instead of as an object of class `sql` i.e. `sql("SELECT * FROM my_table")`.[^1] Noticing this, we changed `read_civis` to first parse the user-input string for SQL keywords, and if it detects any, to tell users `Do you mean to use sql(...)`? It's a small but considerate addition that would save the users an unwelcome trip to the documentation. These little things count in software design.

[^1]: We design `read_civis` so that it dispatches the appropriate method based on the type of its first argument (In R lingo, `read_civis` is [a generic function that does method dispatching](http://adv-r.had.co.nz/S3.html)). This design allows us to centralize all the different ways to read from Civis platform under one function `read_civis`. For example, `read_civis("my_table")` reads all data from the specified table, while `read_civis(sql("SELECT * FROM my_table"))` executes the SQL statement. Method dispatching is convenient but unfamiliar to users, so we could have designed `read_civis` to have multiple arguments, one for each way of reading from Civis platform. For example, `read_civis(table="my_table")` or `read_civis(sql="SELECT * FROM my_table")`. However, this approach litters the argument list and causes confusion when the user specifies multiple arguments at the same time.


### 2. Communicate to your users that it is okay to be confused 

Everyone hates admitting to being confused, especially technical users who take pride in being quick learners. And yet these moments of confusion are when we learn the most about where our software is lacking! To make the users comfortable, at every step of the interview I put the onus of being wrong on me, not the user.

At the beginning, set the tone with 

> Thank you for your time -- your feedback is really important to us. There are many design issues that our team is still debating internally. (*Note: This communicates that the design is very much in flux and their feedback will have a real impact.*) Please do tell me your first impression on any part of the design. If there is anything that is not immediately clear, that is on us to make it better. (*Note: This puts the onus of getting things right on the design team, not the users*).

During the interview, don't follow up with what users say with "How so?" Instead, use a more welcoming tone: "That's really interesting. Tell me more about your thought process."

Along the way, nod and confirm ("Yeap, uhm-hmm") liberally, especially when the user's answer does not match our expectation.

### 3. Be comfortable with silence

When the user goes "Mmm..." prod them with "Yeah...?" and wait for interesting stuff to pour out. Resist the temptation to fill in the silence and contaminate the data with your own thinking about the design. Once we have made the users comfortable, these moments of silence are should be valuable reflection and not hesitation about getting things wrong.

### 4. Structure your report back to the team around decision points

Because interviews with technical users can get deep in the weeds, I wanted to synthesize the information into actionable items for your team to decide. I found it most helpful to summarize users' preference in a table with the columns being the users, and the rows being specific, ideally binary, design choices. Typically, [we won't need to interview more than 5 users](https://www.nngroup.com/articles/why-you-only-need-to-test-with-5-users/), so this table should be compact enough to give an actionable overview.

Then, I often have a free form paragraph summarizing users' rationale behind their preference, or features that they suggest. When our users are technical experts, we do want to take advantage of their advice.

### Conclusion

And that was my experience doing user interview for statistical software! I was intimately involved with the design and thought I had considered everything, but talking to users still surprised and delighted me with new ways to make our design better. 

After all, what's fundamental to all these usability testing tactics is the utmost respect for users. Our software is for people to use, so we ought to love the humans more than the code (even though we tend to spend more time with the latter).

The [R client we developed is now open-sourced](https://github.com/civisanalytics/civis-r), and you can see the [IO scheme I've mentioned in examples here](https://github.com/civisanalytics/civis-r/blob/master/R/io.R).
