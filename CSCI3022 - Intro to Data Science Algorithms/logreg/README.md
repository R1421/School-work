Logistic Regression
=======

Overview
--------

In this homework you'll implement a stochastic gradient ascent for
logistic regression and you'll apply it to the task of determining
whether documents are talking about hockey or baseball.

![Hockey and Baseball: Are they really that different?](baseball_hockey.jpg "Two sports I know nothing about")

You should not use any libraries that implement any of the functionality of logistic regression
for this assignment; logistic regression is implemented in scikit
learn, but you should do everything yourself. 

You'll turn in your code on Moodle.  This assignment is worth 25
points.

What you have to do
----

Coding (15 points):

1. Understand how the code is creating feature vectors (this will help you code the solution and to do the later analysis).  You don't actually need to write any code for this, however.
2. (Optional) Store necessary data in the constructor so you can do classification later.  
3. You'll likely need to write some code to get the best/worst features (see below).
3. Modify the _sg update_ function to perform non-regularized updates.

Analysis (10 points):

1. What is the role of the learning rate?  [Give examples/graphs]
2. How many passes over the data do you need to complete?
3. What words are the best predictors of each class?  How (mathematically) did you find them?
4. What words are the poorest predictors of classes?  How (mathematically) did you find them?

What to turn in
-

1. Submit your _logreg.py_ file (include your name at the top of the source)
1. Submit your _analysis.pdf_ file
    - no more than one page
    - pictures are better than text
    - include your name at the top of the PDF

Unit Tests
=

I've provided unit tests based on the example that we worked through
in class.  Before running your code on read data, make sure it passes
all of the unit tests.

```
engr2-4-195-dhcp:logreg jbg$ python3 tests.py
[ 0.  0.  0.  0.  0.]
[ 1.  4.  3.  1.  0.]
[ 0.5  2.   1.5  0.5  0. ]
[ 1.  4.  3.  1.  0.]
.
----------------------------------------------------------------------
Ran 1 test in 0.002s

OK
```

Example
-

This is an example of what your runs should look like (TP is "Train
Probability"; HP is "Heldout Probability"; TA is "Train Accuracy"; HA
is "Heldout Accuracy"):

```
cs244-33-dhcp:logreg jbg$ python logreg.py
Read in 1064 train and 133 test
Update 1	TP -728.031877	HP -89.799782	TA 0.497180	HA 0.533835
Update 6	TP -900.538122	HP -115.634421	TA 0.517857	HA 0.488722
Update 11	TP -704.708605	HP -96.961868	TA 0.579887	HA 0.518797
Update 16	TP -679.129712	HP -92.263830	TA 0.588346	HA 0.541353
Update 21	TP -722.469178	HP -89.796534	TA 0.608083	HA 0.639098
Update 26	TP -656.324879	HP -75.516536	TA 0.660714	HA 0.714286
Update 31	TP -658.569795	HP -76.169386	TA 0.654135	HA 0.691729
Update 36	TP -633.161013	HP -72.344206	TA 0.684211	HA 0.706767
Update 41	TP -701.607619	HP -80.218928	TA 0.679511	HA 0.669173
Update 46	TP -588.567683	HP -66.271052	TA 0.722744	HA 0.766917
Update 51	TP -582.332356	HP -67.719479	TA 0.719925	HA 0.714286
...
Update 1046	TP -125.650765	HP -25.450108	TA 0.969925	HA 0.939850
Update 1051	TP -125.489756	HP -25.138841	TA 0.974624	HA 0.939850
Update 1056	TP -126.303435	HP -24.990931	TA 0.971805	HA 0.939850
Update 1061	TP -123.245353	HP -24.924609	TA 0.974624	HA 0.947368
```

Hints
-

1.  Make sure that you debug on small
    datasets first (I've provided _toy text_ in the data directory to get you started).
1.  Use numpy functions whenever you can to make the computation faster.


