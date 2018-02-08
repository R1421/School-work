Feature Engineering
=

Due: 24. February at 11:55pm 

The goal of this assignment is to do text classification on social media,
sorting them into different classes.  We'll be using the logistic regression
classifier provided by *sklearn*.

Unlike previous assignments, the code provided with this assignment has all of
the functionality required.  Your job is to make the functionality better by
improving the features the code uses for text classification.

**NOTE**: Because the goal of this assignment is feature engineering, not
classification algorithms, you _may not_ change the underlying algorithm or it's parameters

It is structured in a way that approximates how classification works in the real
world: Features are typically underspecified (or not specified at all). You, the
data digger, have to articulate the features you need. You then compete against
others to provide useful predictions.

It may seem straightforward, but do not start this at the last minute.  There
are often many things that go wrong in testing out features, and you'll want to
make sure your features work well once you've found them.

Analysis
--------------

The job of the written portion of the homework is to convince the grader that:
* Your new features work
* You understand what the new features are doing
* You had a clear methodology for incorporating the new features

Make sure that you have examples and quantitative evidence that your
features are working well.  Be sure to explain how you used the data
(e.g., did you have a validation set? did you do cross-validation?) and how you inspected the
results.

A sure way of getting a low grade is simply listing what you tried and
reporting the Kaggle score for each.  You are expected to pay more
attention to what is going on with the data and take a data-driven
approach to feature engineering.

About the Data
--------------

You can get the data from the Kaggle site (it's also included in the Git repo).

When people are discussing popular media, there’s a concept of spoilers.  That
is, critical information about the plot of a TV show, book, or movie that
“ruins” the experience for people who haven’t read / seen it yet.

Fortunately, the site TV Tropes has provided us with annotations of whether
particular text is a spoiler or not (go to the page for your favorite TV show /
movie and see what’s hidden).

Submission
-----------

In addition to turning in your code on Moodle, you'll also need to submit your
predictions on Kaggle, an online tournament site for machine learning
competitions.  You must sign up with your Colorado e-mail (it's a restricted
entry competition).

https://inclass.kaggle.com/c/feature-engineering-csci-4830-5622-spring-2017

In addition:
* please turn in a file called _analysis.pdf_ explaining your process of
  creating additional features.  Make sure you state your username there.  This should only be one page of text, but it is okay if it's longer due to graphics. 
* upload your _classify.py_ code that produced your predictions

The sample code produces a two column CSV file that is correctly formatted for Kaggle (predictions.csv).  It should have the id as the first column and the prediction as the second column.

How this Assignment is Graded (30+ points)
------------------------------

15 points of your score will be generated from your performance on the
the classification competition on Kaggle.  The performance will be
evaluated on accuracy on a held-out test set.

You should be able to significantly
improve on the baseline system (i.e. the predictions made by the starter 
code we've provided) as reported by the Kaggle system.  The top 3 students from the undergraduate and and graduate sections 
on the private leaderboard at the end of the contest will receive 3 extra
credit points towards the performance portion of your grade.  In addition, any student that beats Aditya's score will receive 2 extra credit points. 

Your writeup explanation is worth 15 points.


Questions / Hints
----------------

* Don't use all the data until you're ready.  You may want to add a --limit 
  option (as was provided in the KNN homework) to use a subset of the data to see how you're doing on smaller
  datasets.
* Examine the features that are being used.
* Do error analyses.
* If you have questions that aren’t answered in this list, feel free to ask them
  on Piazza.


    Can I look at TV Tropes?

In order to gain insight about the data yes, however, your feature extraction cannot use any additional data (beyond what I've given you) from the TV Tropes webpage.

    Can I use IMDB, Wikipedia, or a dictionary?

Yes, but you are not required to. So long as your features are fully automated, they can use any dataset other than TV Tropes. Be careful, however, that your dataset does not somehow include TV Tropes (e.g. using all webpages indexed by Google will likely include TV Tropes).

    Can I combine features?

Yes, and you probably should. This will likely be quite effective.

    Can I use Mechanical Turk?

That is not fully automatic, so no. You should be able to run your feature extraction without any human intervention.  If you want to collect data from Mechanical Turk to train a classifier that you can then use to generate your features, that is fine.  (But that’s way too much work for this assignment.)

	Can I use a Neural Network to automatically generate derived features? 

No.  This assignment is about your ability to extract meaningful features from the data using your own experience.  

    What sort of improvement is “good” or “enough”?

If you have 5-10% improvement over the baseline (on the Public Leaderboard) with your features, that’s more than sufficient.  If you fail to get that improvement but have tried reasonable features, that satisfies the requirements of assignment.  However, the extra credit for “winning” the class competition depends on the performance of other students.

    Where do I start?  

It might be a good idea to look at the in-class notebook associated with Lecture 7 where we did similar experiments.  This, along with all of the other in-class notebooks, is available in the [csci5622notebooks](https://github.com/chrisketelsen/csci5622notebooks) repo on GitHub. 

