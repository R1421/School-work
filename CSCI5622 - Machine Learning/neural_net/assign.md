Training Feed-Forward Neural Networks 
=

Due: 3, May by 11:55pm

![Samples of Handwritten Digits](mnist.png "MNIST Digits")

Overview
--------

In this homework you'll implement a feed-forward neural network 
for classifying handwritten digits.  Your tasks will be to 
implement back propagation to compute the parameter derivatives
for SGD, implement L2-regularization, and implement numerical 
gradient checking to ensure that your code is working correctly. 

You'll turn in your code on Moodle.  This assignment is worth 25
points. Remember, this assignment can replace your lowest previous 
homework score, but is not mandatory. 

What you have to do
----

Coding (20 points):

1.  Modify the _back_prop_ function to compute the parameter derivatives 
1.  Modify the _SGD_train_ function to perform regularized updates 
1.  Modify the _gradient_checking_ function to perform numerical gradient checking 

Analysis (5 points):

1. Use your classifier to predict handwritten digits in a lower-resolution version of the MNIST dataset
1. Explore the effect of network architecture on classification accuracy 
1. Explore the effect of network regulariztion on classification accuracy 


What to turn in
-

1.  Submit your _nn.py_ file
1.  Submit your _analysis.pdf_ file (no more than one page; pictures
    are better than text)

Unit Tests
=
I'll upload these over the weekend. 

=
Hints
-

1.  I've provided you with a toy data set containing 2D feature vectors 
    and two labels, similar to the data used in the Lecture 18 in-class
    notebook.  Make sure your code works on this data set before moving
    on to MNIST. 
1.  Leverage Numpy as much as possible.  Inefficient implementation will
	be painstakingly slow when you start working on the MNIST data. 
1.  Information on numerical gradient checking can be found in the 
	Lecture 18 in-class notebook. 
1.  I've altered the data structure used to store training and testing 
	data from the one used in the Lecture 18 in-class notebook, however
	any code you had working in the in-class notebook should still work
	without modification. 
    
    
