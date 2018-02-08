# Final Exam

The final solves the Oregonator problem in chemical kinetics, as explained in the [Differential Equations notebook](https://nbviewer.jupyter.org/github/jedbrown/numerical-computation/blob/master/DifferentialEquations.ipynb).

Please add your code to this directory (don't forget to `git add` it) and write your answers to the following parts below.  (These questions are explained in detail in the notebook above).

### I worked with Rasmi Lamichhane, Anh-Khoa Than, and Richard Laub and got help from them for questions 2 and 4. I did not time for question 3 because my machine froze during the last 30 minutes and by the time I got it running again it was too late to re-execute my code to get the data needed to continue. It would have gone over the time. I then had some issues with git and it resulted in me deleting this file... twice.... This is the third time I've written this, and that is why it is so late.


## 1. How to measure accuracy?

I measured accuracy by finding the location of the first peak of y0 y1 and y2. I then took the norm of the difference. This works because if the slope at each iteration is either under-  or over-approximated, the peak would occur later or earlier respectively.

## 2. Implicit versus Explicit

The best method was backwards euler if the goal is accuracy. It is, however, the most costly of the three methods (euler, rk4, and beuler). Of these three, the least costly is the euler method.

## 3. Eigenvalues

**your answer here**

## 4. Generalization

If one were trying to solve a much larger system, the correct choice depends on whether accuracy is most important than speed. If accuracy is most important, backwards euler would be the best option, though it would take a VERY long time to finish. If speed is the most important, euler is the best option. A good middle would be rk4, which is fairly accurate, and much faster than backwards euler.
