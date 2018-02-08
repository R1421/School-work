
Estimating Distribution Parameters
===============

Overview
---------------

This program will be autograded.  That means that it's important to
not change function names and to not add additional functionality that
may improve the program but produce different results.  Make sure that
your unit tests pass.  This what a successful set of unit tests will
look like:

    $ python3 tests.py
    .......
    ----------------------------------------------------------------------
    Ran 7 tests in 0.002s
    
    OK

t-tests (5 points)
----------------------------

For the first part of the assignment, you'll need to create functions
to compute many of the parameters that go into hypothesis testing with
a t-test.  Given two sets of numbers (without assumed equal
variances), you'll need to first compute their unbiased sample
variance, compute the number of degrees of freedom
using the Welch–Satterthwaite equation, and then compute the p-value
of the Student's t-test.

You will need to implement the following functions:
* degrees_of_freedom
* unbiased_sample_variance
* t_statistic
* t_test

Bigrams Presidents Use (20 points)
-------------------------------

Each year, the president of the United States is required to make a
speech to congress describing the "State of the Union".  We are going
to look for pairs of words that are highly associated with each other.

To find pairs of words that are strongly associated with each other,
we'll use the "chi-square" test.  It tests the null hypothesis that
words appearing next to each other are independently distributed.
Rejecting the null with a good p-value implies that the words are
strongly associated with each other (e.g., "lower taxes").

You'll need to keep track of how many times words words are used
(similar to what you did in the previous assignment) after forming a
vocabulary of all the possible words that can be used in a bigram.

Unlike the language modeling assignment, you'll need to keep track of
how many bigrams *end* with a particular word, and you'll ignore words
and bigrams that occur too infrequently (cases where the chi-square
test does not apply).  These parameters are provided and set by the
constructor of the BigramFinder class.  Make sure your code obeys
these parameters.

To do this, you'll need to implement the following functions:
* chisquare_pvalue
* BigramFinder.observed_and_expected
* BigramFinder.add_sentence
* BigramFinder.valid_bigrams

Writeup (5 points)
-----------------------

Finally, include a brief plain-text file (not PDF, not Word, just a
plain ASCII text file) that:
* Describes your approach
* Discusses the bigrams you observe: what shouldn't be there but is,
  what bigrams are you missing and why?

Submitting Your Code
-----------------------

You'll need to submit your assignment (ttest.py, bigrams.py, writeup.txt) on Moodle as an upload.
