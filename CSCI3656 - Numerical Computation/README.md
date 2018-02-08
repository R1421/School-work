# CSCI-3656

## Final Exam
### Due 2016-12-15 at 11:59pm

See [notebook](https://nbviewer.jupyter.org/github/jedbrown/numerical-computation/blob/master/DifferentialEquations.ipynb) and `final/README.md` in this repository.

## Coding Assignment (HW7)
### Due 2016-12-10 at 11:59pm (extended from 2016-12-09)

It is common to use a howitzer or recoilless rifle for avalanche control at ski resorts and above highways.
The top of a 40-degree avalanche-prone slope is 3 km horizontal and 1 km vertical above your rifle.
The muzzle velocity is 300 m/s and the 10cm diameter projectile has a mass of 8 kg with a drag coefficient of 0.2.
You would like to find the firing angle (above horizontal) at which to aim so that your charge lands within 30 m of the top of the slope.
The problem setup and equations are [explained in the notebook](https://nbviewer.jupyter.org/github/jedbrown/numerical-computation/blob/master/DifferentialEquations.ipynb#Ballistics-(for-HW7)).

Write a program `hw7/hw7` that solves the differential equation for the free projectile and determines where it hits the slope.  Use the program to determine the angle theta in order to hit the slope within 30 meters of the top (without going over).  (You can either hand-optimize the angle or use a rootfinder.)
When run, your program should print the firing angle (theta) and the time of impact.

## Coding Assignment (HW6)
### Due 2016-12-02 at 11:59pm (extended from 2016-11-29)

This homework asks you to implement two numerical integration methods, described below.
After implementing these methods, you should compare their performance on some test functions with different numbers of points.  Find at least one test function and number of points `n` for which the first method is superior and at least one for which the second is superior.  Display your output using the format
`{testname} {method} {n} {error}`, one per line.
For example, my output might contain
```
sin legendre 3 2.359998e-07
sin legendre 4 -2.679675e-10
```

#### Recursive extrapolation
We have seen how Richardson extrapolation can be used to increase the order of accuracy of Newton-Cotes methods (typically starting with the trapezoid rule).
Implement a method that applies Richardson extrapolation recursively.
You can choose how many times to recurse.

#### Gauss-Legendre integration
The [Integration notebook](http://nbviewer.jupyter.org/github/jedbrown/numerical-computation/blob/master/Integration.ipynb) contains a recursive formula for the derivative of Legendre polynomials.  Write a function `legendre_eval(x, n)` that computes the `n`th Legendre polynomial and its derivative at the points `x`.  Write a function `legendre_roots(n)` that uses Newton's method to compute the roots of the `n`th Legendre polynomial, using the initial guess `cos(linspace(.5/(n-1), 1-.5/(n-1), n) * pi)`.  Write a version of `fint_legendre` (analogous to the implementation in the notebook) that uses the roots that you have computed.

## Coding Assignment (HW4)
### Due 2016-11-04 at 11:59pm

This homework explores the concepts of conditioning and accuracy of different interpolation techniques.  The [Interpolation notebook](https://nbviewer.jupyter.org/github/jedbrown/numerical-computation/blob/master/Interpolation.ipynb) has some code that may be useful to get you started.  The step below asks you to print some lines with the given format strings.  These are C (or Python, etc.) style format strings, `%d` means decimal integer and `%e` means floating point in scientific notation.  Please make your code print these lines as described when I execute `hw4/run` (or `hw4/run.py`, `hw4/run.m`, etc.).

1. Write a function `piecewise_linear_interp_and_eval(x, xx)` that returns a matrix mapping the values of a function at the points `x` to the values of the interpolating function at `xx`.  This function is analogous to `chebyshev_interp_and_eval(x, xx)`.  Print the norm (largest singular value) of this matrix for each of `x = linspace(-1,1,20)` and `x = cosspace(-1,1,20)` with `xx = linspace(-1,1,100)`.  Use the format strings `"piecewise_linear linspace -> linspace: norm=%e"` and `"piecewise_linear cosspace -> linspace: norm=%e"` for these two lines.
2. Implement/copy/port `chebyshev_interp_and_eval` to your source file (same as above, but using a single Chebyshev polynomial instead of piecewise linear functions).  Print the norms as above (replacing `piecewise_linear` with `chebyshev`).
3. For the function `f(x) = exp(-16*x**2)`, determine the number `n` of `x=linspace(-1,1,n)` and `x=cosspace(-1,1,n)` points needed to make the maximum interpolation error at `xx` less than `eps=1e-4`.  I expect you will write a loop that terminates when this condition is met or if no solution is found at `n=100`.
(This maximum error is also known as the "infinity norm". It is an option for the `norm` function in most linear algebra libraries.)  Print the number of points and the error using the format string `"piecewise_linear f() cosspace -> linspace: n=%d max_error=%e"` (and similar for `linspace`).
4. Same as above for `g(x) = abs(x)` and `eps=1e-2` (replace `f()` with `g()` in the format string).

## Coding assignment (HW3)
### Due 2016-10-18 at 11:59pm

The Householder algorithm uses a reflection to map x to a scaled coordinate vector of the same length, ||x||e_0.  The matrix

```
    [[cos(t), sin(t)], [-sin(t), cos(t)]]
```

is called a **Givens rotation**, rotating the plane by an angle `t`.
Instead of reflecting the vector x to ||x||e_0, it is also possible to rotate it into that position.
Implement a QR algorithm using Givens rotations instead of Householder reflectors.
Recommended steps:

1. Write a function `givens_rot(theta, v, x)` that rotates the vector `x` by an angle `theta` in the subspace spanned by the orthogonal basis `[1, 0, 0, ...]` and `[0, v]` where `v` is a unit vector.
2. Make this function accept a matrix `x` as input, operating on each column independently.
3. Calculate the angle that a vector `x` must be rotated by in order to align with the zeroth axis using the `arctan2` function, e.g., `arctan2(norm(x[1:]), x[0])`.
4. Adapt/port the Householder QR example code to use rotation instead of reflection.  Store the angles `theta` and vectors `v = x[1:]/norm(x[1:])` while triangularizing each column.
5. Write a function `givens_Q_times(V, x)` that applies the action of the orthogonal matrix `Q` (represented as a list `V` of `(theta, v)` pairs) on an input vector (or matrix) `x`.
6. Use `givens_Q_times` with the identity to return the factors `Q` and `R`.

Finally, compute the error in `QR = A` and `Q.T Q = I` where `A` is the Vandermonde matrix associated with m=10 and m=20 equally spaced points on the interval `[-1,1]`.
The output from these two numerical tests should be printed when running `hw3/givens` (or `hw3/givens.py`, `hw3/givens.m`, etc.).

## Coding assignment 1
### Due 2016-09-16 (Friday) at 11:59pm (extended from 2016-09-09)

1. Write a program `hw1/newton` that implements Newton's method and runs it on some test equations of your choice.  Output the convergence history for each test equation (please use the format described below).
2. Find a *strictly* monotonically increasing function with a unique root for which Newton's method diverges for initial guess x=1.0.  Add this to your test set.
3. Newton's method is often paired with a "line search" that scales the step size by a factor such that the norm of the new residual is smaller than the previous.  I.e., find a scaling factor such that `|f(x_{n+1})| < |f(x_n)|` where `x_{n+1} = x_n - scale * f(x)/f'(x)`.  One of the simplest variants is to start with a scaling factor of 1 and cut it in half until the norm decreases.  Implement this variant in `hw1/newtonls` and run it on your test equations.
4. Newton's method is based on dropping the quadratic and higher terms in a Taylor expansion.  Write a program `hw1/cubic` that implements a method that keeps the quadratic term in the Taylor expansion (dropping cubic and higher terms).  You will need to make choices about multiple roots or non-existant roots; we discussed some options in class.  Find an equation for which Newton is better and an equation for which the cubic algorithm is better.  (Better means that an algorithm converges faster or converges when the other diverges.)  Add these to your test suite.

### Edits (posted 2016-09-08)

* Update part 2 to request *strict* monotonicity (i.e., the derivative is never zero).  You can use a function that is defined for all real numbers `x`, but that is not required.
* Explain scaling factor for the line search in more detail and clarify choices in the cubic algorithm.

### Notes
* When executed, each of the three programs (`hw1/newton`, `hw1/newtonls`, and `hw1/cubic`) should print a sequence of lines containing the following information for each equation in your test suite.

```
${EquationName} ${IterationNumber} ${CurrentX} ${Residual}
```

(The `${VariableName}` syntax above indicates variable expansion; the `$`, `{`, and `}` characters are not printed.)
The `EquationName` is any (string) key you choose, it just allows comparison between the different programs.
Let `IterationNumber` start at 0 with the initial guess.
`CurrentX` and `Residual` are floating point values -- format them in a way that you think is appropriate.

* You can put your test equations in a separate file that is included or imported by each of the three executables.

* Be sure to commit and push all necessary source code to make your programs run.

* I will run `make` before trying to run the executables.  If you are using a compiled language, please write a [GNU-style makefile](https://www.gnu.org/software/make/manual/make.html#Introduction) (`hw1/Makefile`) to build your executables.

* You may use libraries such as SymPy to compute derivatives for this assignment.
Please note, however, that f(x) could be an arbitrary function (it could have its own solves inside, table lookups, etc.)
Also, we'll see in class how the output of symbolic differentiation expression grows exponentially in the size of the input.
So symbolic differentiation is not a general purpose solution despite being very useful for testing.

## Updating your repository

After you fork this repository, your fork does not update automatically when I add instructions or input/output for future assignments.
I recommend running the following from within the clone on your computer (only needed once ever):

    git remote add upstream git@git.cs.colorado.edu:csci-3656/csci-3656

and then to update at any time

    git pull upstream master

which will pull changes from my repository and merge them into yours.
This command is idempotent -- it does nothing if you are up to date.

## Coding assignment 0

### Due 2016-08-31 (Wednesday) at 11:59pm

* Log into https://git.cs.colorado.edu
* Use `ssh-keygen` to create a keypair if you don't already have one.
* Upload your *public* key to your profile on https://git.cs.colorado.edu
* Click "Fork" to fork this repository to your personal account.  You will make your changes in that repository.
* Clone your new repository to your computer: `git clone git@git.cs.colorado.edu:YOURUSERNAME/csci-3656`
* Create a new directory in the repository: `mkdir hw0`
* In that directory, create an executable file (your choice of language) named `run` that prints your preferred name.  If you have used a script, you'll need to start with a [shebang](https://en.wikipedia.org/wiki/Shebang_(Unix)) (`#!/usr/bin/python3`).  If you used a compiled language, you'll need to compile the code so you might write a shell script containing `gcc -o a a.c && ./a`.
* Use `git add hw0/run` and `git commit` to commit your changes.  Make sure the author information has your name and email address correct.
* Push your changes to your fork: `git push`

I will clone your repository and try running `hw0/run` (in a controlled environment, no points for trying to hack me ;-)).
Make sure that this works regardless of which language you used for your program.
This may involve starting your script with a shebang and using [chmod](https://en.wikipedia.org/wiki/Chmod) to make it executable.
If you need multiple files (e.g., with a compiled language), make sure you remembered to commit all relevant files (including the source code).
To be explicit, I recommend testing with:

    git clone your/repository test-repo
    test-repo/hw0/run

If there is a technical reason why the above cannot work in your chosen programming environment, please consider using an environment in which it can, otherwise let me know and we'll find a workaround.
* For MATLAB on Windows, you may name your file `hw0/run.m` and I will run it from MATLAB.  Note that MATLAB (or Octave) developers on Linux or Mac can use `#!/usr/bin/env octave --no-gui` as shown in class.

Please do not commit compiled binaries -- they won't run on my machine and just take up space in the repository.
