Support Vector Machines
=

Due: 24. March at 11:55pm 

Overview
--------

In this homework you'll explore the primal and dual representations of support
vector machines, as well as explore the performance of various kernels while 
classifying handwritten digits. 

You'll turn in your code on Moodle.  This assignment is worth 30
points.

What you have to do
----

Coding (15pts):

1.  Given a weight vector, implement the *find support* function that returns the indices of the support vectors.
1.  Given a weight vector, implement the *find slack* function that returns the indices of the vectors with nonzero slack.
1.  Given the alpha dual vector, implement the *weight vector* function that returns the corresponding weight vector.

Analysis (15pts):

1.  Use the Sklearn implementation of support vector machines to train a classifier to distinguish 3's from 8's (using the MNIST data from the KNN homework).
1.  Experiment with linear, polynomial, and RBF kernels.  In each case, perform a grid search to determine optimal-ish hyperparameters
for the given model (e.g. C for linear kernel, C and p for polynomial kernel, and C and gamma for RBF).  You will find very helpful 
examples on how to do this in the Lecture 14 in-class Notebook. 
1.  Comment on classification performance for each model for varying parameters by either testing on a hold-out set or performing 
cross-validation. 
1.  Give examples (in picture form) of support vectors from each class when using a linear kernel.

Notes
-

- Try not to reinvent the wheel for the coding portion of the assignment.  Leverage built-in Numpy methods whenever possible.  My 
solution for each function is one line of code.  It's OK if yours is longer, but if it's too much longer then you're working too hard. 
- I've provided you a sample driver function that reads in the data and plots training examples.  You will have to add the rest to do the Analysis portion.  Do **NOT** submit your driver file to Moodle. 
- Sklearn's implementation of support vector machines gives a convenient method for extracting support vectors from each class.  Feel free to use that for the analysis portion of the assignment.  


What to turn in
-

1.  Submit your _svm.py_ file
1.  Submit your _analysis.pdf_ file (no more than one page of writing; lots of opportunities to  
    show with pictures instead of telling with text)


Unit Tests
=

I've provided unit tests based on the example that we worked through in class.
Make sure it passes all of the unit tests.  However, these tests are not exhaustive; passing the tests will not
guarantee a good grade, you should verify yourself that your code is robust and
correct.


Hints
-

1.  Don't use all of the data, especially at first.  
