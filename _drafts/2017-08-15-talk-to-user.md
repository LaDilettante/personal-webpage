---
title:      "User interview for statistical software"
---

This summer, I worked at [Civis Analytics](https://www.civisanalytics.com/), a start-up building cloud platform for data science workflow. One of my team projects was to develop an R client that allows our customers to interact with Civis' platform via R code instead of web GUI.

During the design process, I interviewed our in-house data scientists for their feedback[^1]. To prepare, I scoured the Internet for articles on UX interviews. Unfortunately, these articles mostly geared towards consumer-grade web design. While the principles hold true, many tactics do not take into account the sense and sensibility of our technical users. Below is how I molded those principles into practical advice on user interview for statistical software.

## 1. Watch your users use your software

At the root of this principle is the fact that most people suffer from [the illusion of competence](https://www.coursera.org/learn/learning-how-to-learn/lecture/BuFzf/illusions-of-competence). After looking at some demo, we tend to overestimate our mastery of the software unless being put to the task of using it ourselves.

In practice, because our data scientists only had 30 minutes to spare, I couldn't expect them to actually sit down and use our software. Still, to guard against the illusion of competence, I gave the users a list of our IO function signatures and asked them to guess what the functions do based on that alone. Indeed, all of us have scanned function names in long manuals looking for the thing we need. If a function signature does not communicate what the function does, the design has already failed.

During this exercise, I noted down two signs of confusion: either 1) the user guessed wrong, or 2) the user was slow to guess, both of which call for a re-thinking of our design.

## 2. Communicate to your users that it is okay to be confused 

Everyone hates admitting to being confused, especially technical users who take pride in being quick learners. And yet these moments of confusion are when we learn the most about where our software is lacking! To make the users comfortable, at every step of the interview I put the onus of being wrong on me, not the user.

At the beginning, set the tone with "Thank you for your time -- your feedback is really important to us. There are many design issues that our team is still debating internally. (*Note: This communicates that the design is very much in flux and their feedback will have a real impact.*) Please do tell me your first impression on any part of the design. If there is anything that is not immediately clear, that is on us to make it better. (*Note: This puts the onus of getting things right on the design team, not the users*)."

During the interview, don't follow up with what users say with "Really?" or even "Why do you think so?" Instead, use a more welcoming tone: "That's really interesting. Tell me more about your thought process."

Along the way, nod and confirm ("Yeap, uhm-hmm") liberally, especially when the user's answer does not match our expectation.

## 3. Be comfortable with silence

When the user goes "Mmm..." prod them with "Yeah...?" and wait for interesting stuff to pour out. Resist the temptation to  fill in the silence with your own thinking about the design. Once we have made the users comfortable, these moments of silence are truly reflection and not hesitation about getting things wrong.

## 4. For statistical software, the obvious solution may not be the best

For simple processes such as checking out an online shopping cart, the only goal of design is that the user knows how to use the software immediately.

In contrast, good statistical software not only lets the user do what they want now, but also empowers them to do things they have not envisioned before. For this reason, near the end of the interview, I walked the users through design rationales that have non-obvious benefits. 

For example, while uploading R data frame to Amazon S3, we can either upload it as a CSV or as a binary R object. When asked, users invariably say they want CSV, which is the familiar way of doing things. I then engaged the user in thinking about the trade-off: yes, a CSV is more familiar, but it does not preserve the metadata, e.g. a data frame column types. Upon reflection, all users agree that uploading a binary R object would be the better choice, albeit not being the more obvious.

## 5. Structure your report back to the team around decision points

Because interviews with technical users can go deep in the weeds, you want to synthesize the information into actionable items for your team to decide. The most helpful structure is to summarize the data in a table with the rows being specific, ideally binary, design choices (e.g. upload CSV or data frames), and the columns being the users' preference. Typically, [you won't need to interview more than 5 users](https://www.nngroup.com/articles/why-you-only-need-to-test-with-5-users/), so this table should be compact enough to give an actionable overview.

Then, I'll have a free form paragraph summarizing users' rationale behind their preference, or features that they suggest. When our users are technical experts, we do want to take advantage of their design suggestions.

And that was my experience doing interview for statistical software. The [R client we developed has been open-sourced](R client we developed has been open-sourced), and you can see the [IO scheme I've been talking about here]()!

[^1]: Civis Analytics has both a department writing softwares for data scientists, and a department of applied data scientists doing consulting works for businesses and organizations.
