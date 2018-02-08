
Regression
===============

Overview
---------------

One of the most visible uses of regression is to predict election
outcomes.  They take poll data from many different sources, combine
them together, and create a prediction of the final outcome of the
election.  While this assignment won't match the complexity of
[538](http://fivethirtyeight.com/) or
[Princeton Election Consortium](http://election.princeton.edu/), we'll
be doing the same thing and hopefully also getting a better
understanding of how to create useful features for regression
problems.

Predict the Republican Share (5 points)
----------------------------

A small part of your grade is based on how well you can predict the
2016 election.  You'll be scored based on the mean squared error between the
Republican share of the vote in each state.  

It is possible to get more than the maximum number of points by doing
particularly well in your predictions.  To get points on this part of
the assignment, you should do better than the baseline predictions
offered in the initial template (just using last poll and state ID).

Construct a Model (20 points)
-------------------------------

This is an open-ended assignment.  While there is a right answer,
nobody knows what it is yet (and getting the right answer is an
unimportant part of the assignment).  What is more important is how
you go about building a model to get a good prediction.

There are several components to how you choose a model: creating
features, changing your model training (e.g., online vs. batch), and
selecting model parameters (e.g., regularization).  You should feel
free to explore any of these.

You may use additional *data* to create useful features.  We've
provided a script to get data from the HuffPo polling api, but you
should not feel at all limited to using only these data.  You may not
use the output of other models as data.  If there's any doubt, ask on
Piazza.

Your code should run on the data that you upload in the form that you
uploaded it.  I.e., if you upload a zip file called foo.zip, your
program should create your predictions when placed in the same
directory as foo.zip.

Writeup (15 points)
-----------------------

For whatever you chose as your final model, explain how you chose
your:
* Training
* Features
* Data
* Model

Because so much of this assignment is based on these decisions, make
sure you spend more time than usual on the writeup to ensure it is
written clearly and does a good job of justifying why you chose the
parameters you did.

Do not use more than 1000 words (as reported by the wc command) in
your writeup (but don't feel obligated to reach this limit).

Submitting Your Code, Data, and Predictions
-----------------------

You'll need to submit your assignment (predict.py, data, pred.txt,
model.txt, writeup.txt) on Moodle as an upload.  Do not change the
format of the predictions, as this will be automatically scored.
