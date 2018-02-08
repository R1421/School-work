Logistic Regression
=

Due: 10. February by 11:55pm

Overview
--------

In this homework you'll implement stochastic gradient ascent for
logistic regression and you'll apply it to the task of determining
whether documents are talking about automobiles or motorcycles. 

![](autos_motorcycles.jpg)

This will be slightly more difficult than the last homework (the
difficulty will slowly ramp upward).  You should not use any libraries that implement any of the functionality of logistic regression
for this assignment; logistic regression is implemented in scikit
learn, but you should do everything by hand now.  You'll be able to
use library implementations of logistic regression in the future. 

You'll turn in your code and analysis on Moodle.  This assignment is worth 30
points.

What you have to do
----

Coding (20 points):

1. Understand how the code is creating feature vectors (this will help you code the solution and to do the later analysis).  You don't actually need to write any code for this, however.
2. Modify the _sg update_ function to perform non-regularized updates.
3. After that works, modify the _sg update_ function to perform regularized updates using **Lazy Sparse Regularization**. Note that you should not regularize the bias weight.  See the in-class notebook associated with Lecture 4 for a refresher on LSR. 
4. You'll likely need to write some code to get the best/worst features (for the analysis portion).

<!---(See discussion [here](https://nbviewer.jupyter.org/url/grandmaster.colorado.edu/~cketelsen/files/csci5622/notebooks/lesson04/lesson04NBKAnswers.ipynb?flush_cache=true)) -->

Analysis (10 points):

1. How did the learning rate affect the convergence of your SGA implementation?
2. What was your stopping criterion and how many passes over the data did you need to complete before stopping?
3. What words are the best predictors of each class?  How (mathematically) did you find them?
4. What words are the poorest predictors of classes?  How (mathematically) did you find them?

Extra credit:

1. (max 2pts) Use a schedule to update the learning rate.
    - Modify the eta_schedule function 
    - Pass it into the LogReg constructor 
    - Support it in your _sg update_
    - Show the effect in your analysis document
1.  (max 2pts) Use document frequency (provided in the vocabulary file) to modify the feature values to [tf-idf](https://en.wikipedia.org/wiki/Tf%E2%80%93idf).
    - Modify the Example to store the df vector
    - With the appropriate flag, use the df and x vectors to implement tf-idf in the update
    - Show the effect in your analysis document

**Caution**: When implementing extra credit, make sure your implementation of the
regular algorithms doesn't change and you still pass the unit tests. 

What to turn in
-

1. Submit your _logreg.py_ file (include your name at the top of the source)
1. Submit your _analysis.pdf_ file
    - no more than one page worth of text
    - **pictures** are better than text
    - include your name at the top of the PDF

**Notes**:    

1. Do not modify the path to the data.  You should checkout the data directory from GitHub and leave it on the same directory level as your logreg directory. 

1. You should submit only your _logreg.py_ and _analysis.pdf_ files.  Do not submit zipped files or tarballs. 

Unit Tests
=

I've provided three unit tests.  The first test is to make sure 
you've used the learning rate correctly.  The second and third 
tests correspond to the two examples we worked through in class.  
Before running your code on read data, make sure it passes
all of the unit tests.

```
MacBook-Air:logreg cketelsen$ python tests.py 

Testing: Learning Rate Usage
[ 0.  0.  0.  0.  0.]
[ 1.  4.  3.  1.  0.]
F
Testing: Regularized Update
[ 0.  0.  0.  0.  0.]
[ 1.  4.  3.  1.  0.]
F
Testing: Unregularized Update
[ 0.  0.  0.  0.  0.]
[ 1.  4.  3.  1.  0.]
F
======================================================================
FAIL: test_learnrate (__main__.TestLogReg)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "tests.py", line 60, in test_learnrate
    self.assertAlmostEqual(w[0], 0.25)
AssertionError: 0.0 != 0.25 within 7 places

======================================================================
FAIL: test_reg (__main__.TestLogReg)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "tests.py", line 40, in test_reg
    self.assertAlmostEqual(w[0], .5)
AssertionError: 0.0 != 0.5 within 7 places

======================================================================
FAIL: test_unreg (__main__.TestLogReg)
----------------------------------------------------------------------
Traceback (most recent call last):
  File "tests.py", line 20, in test_unreg
    self.assertAlmostEqual(w[0], .5)
AssertionError: 0.0 != 0.5 within 7 places

----------------------------------------------------------------------
Ran 3 tests in 0.008s

FAILED (failures=3)
```

Example
-

This is an example of what your runs should look like:
```
MacBook-Air:logreg cketelsen$ python logreg.py
Read in 1059 train and 133 test
Update 1    TP -706.329229  HP -88.277155   TA 0.622285 HA 0.661654
Update 6    TP -771.994351  HP -107.969188  TA 0.566572 HA 0.511278
Update 11   TP -667.457526  HP -94.983726   TA 0.667611 HA 0.639098
Update 16   TP -545.293307  HP -76.950769   TA 0.760151 HA 0.721805
Update 21   TP -507.734061  HP -69.014348   TA 0.779037 HA 0.736842
Update 26   TP -472.235524  HP -63.573640   TA 0.795090 HA 0.759398
Update 31   TP -454.018319  HP -61.223156   TA 0.797923 HA 0.781955
Update 36   TP -440.699093  HP -56.766455   TA 0.803588 HA 0.804511
Update 41   TP -414.680447  HP -51.481145   TA 0.820585 HA 0.804511
Update 46   TP -391.314296  HP -50.555593   TA 0.847970 HA 0.827068
Update 51   TP -420.500191  HP -52.815497   TA 0.814920 HA 0.812030
Update 56   TP -413.348358  HP -48.789629   TA 0.807365 HA 0.827068
Update 61   TP -396.637909  HP -48.378879   TA 0.829084 HA 0.812030
Update 66   TP -393.283404  HP -47.696720   TA 0.829084 HA 0.819549
Update 71   TP -364.434386  HP -46.583350   TA 0.855524 HA 0.857143
Update 76   TP -365.173834  HP -50.513987   TA 0.861190 HA 0.842105
Update 81   TP -386.001432  HP -53.455266   TA 0.852691 HA 0.842105
Update 86   TP -354.868438  HP -49.264942   TA 0.860246 HA 0.842105
Update 91   TP -334.285993  HP -43.688586   TA 0.869688 HA 0.872180
Update 96   TP -359.934115  HP -45.583414   TA 0.850803 HA 0.857143
Update 101  TP -311.547934  HP -39.881548   TA 0.880076 HA 0.879699
Update 106  TP -306.567763  HP -39.818419   TA 0.881020 HA 0.879699
Update 111  TP -303.855842  HP -39.348164   TA 0.879131 HA 0.872180
Update 116  TP -300.381798  HP -39.180906   TA 0.884797 HA 0.872180
Update 121  TP -296.925995  HP -38.452797   TA 0.884797 HA 0.879699
Update 126  TP -296.985480  HP -38.772920   TA 0.889518 HA 0.879699
Update 131  TP -292.943911  HP -38.353531   TA 0.892351 HA 0.872180
Update 136  TP -292.270331  HP -38.148995   TA 0.885741 HA 0.879699
Update 141  TP -327.062720  HP -41.421220   TA 0.860246 HA 0.857143
Update 146  TP -310.505409  HP -39.280384   TA 0.875354 HA 0.864662
Update 151  TP -298.808697  HP -38.310533   TA 0.880076 HA 0.879699
Update 156  TP -301.824659  HP -38.876502   TA 0.879131 HA 0.872180
Update 161  TP -282.462183  HP -37.655326   TA 0.891407 HA 0.872180
Update 166  TP -284.726477  HP -37.878362   TA 0.890463 HA 0.879699
Update 171  TP -320.681970  HP -43.421747   TA 0.860246 HA 0.834586
Update 176  TP -308.301758  HP -41.560912   TA 0.864967 HA 0.857143
Update 181  TP -281.208115  HP -38.146112   TA 0.892351 HA 0.864662
Update 186  TP -266.226288  HP -36.173600   TA 0.897073 HA 0.872180
Update 191  TP -259.397252  HP -35.572234   TA 0.903683 HA 0.872180
Update 196  TP -254.417147  HP -34.892754   TA 0.907460 HA 0.887218
Update 201  TP -260.647159  HP -36.566523   TA 0.899906 HA 0.872180
Update 206  TP -249.643924  HP -34.409214   TA 0.901794 HA 0.894737
Update 211  TP -244.461165  HP -34.298696   TA 0.909348 HA 0.902256
Update 216  TP -249.719090  HP -35.707952   TA 0.902738 HA 0.894737
Update 221  TP -269.036102  HP -38.587207   TA 0.892351 HA 0.872180
Update 226  TP -234.859625  HP -31.831090   TA 0.919736 HA 0.902256
Update 231  TP -246.957932  HP -34.711466   TA 0.918791 HA 0.879699
Update 236  TP -274.112837  HP -39.785646   TA 0.902738 HA 0.849624
Update 241  TP -257.687988  HP -36.625131   TA 0.910293 HA 0.864662
Update 246  TP -243.642082  HP -34.666225   TA 0.915014 HA 0.872180
Update 251  TP -240.678865  HP -34.298046   TA 0.919736 HA 0.872180
Update 256  TP -238.410113  HP -34.487599   TA 0.921624 HA 0.872180
Update 261  TP -245.787754  HP -35.748651   TA 0.916903 HA 0.872180
Update 266  TP -228.526611  HP -32.658606   TA 0.923513 HA 0.872180
Update 271  TP -217.734097  HP -30.228118   TA 0.929178 HA 0.909774
Update 276  TP -222.640257  HP -31.253759   TA 0.927290 HA 0.894737
Update 281  TP -215.526147  HP -30.980111   TA 0.922568 HA 0.894737
Update 286  TP -212.875735  HP -31.922938   TA 0.931067 HA 0.879699
Update 291  TP -222.854874  HP -32.996114   TA 0.927290 HA 0.879699
Update 296  TP -216.027198  HP -32.074771   TA 0.929178 HA 0.864662
Update 301  TP -205.451319  HP -30.701714   TA 0.933900 HA 0.887218
Update 306  TP -197.076933  HP -27.656756   TA 0.932956 HA 0.902256
Update 311  TP -196.916017  HP -27.740621   TA 0.931067 HA 0.894737
Update 316  TP -196.281433  HP -29.151988   TA 0.927290 HA 0.887218
Update 321  TP -191.740297  HP -26.362023   TA 0.937677 HA 0.887218
Update 326  TP -190.427047  HP -26.140272   TA 0.934844 HA 0.902256
Update 331  TP -189.238982  HP -25.780515   TA 0.933900 HA 0.894737
Update 336  TP -188.932351  HP -25.832418   TA 0.933900 HA 0.902256
Update 341  TP -189.447374  HP -26.218840   TA 0.932956 HA 0.909774
Update 346  TP -184.093181  HP -25.595713   TA 0.939566 HA 0.902256
Update 351  TP -182.273463  HP -25.338302   TA 0.942398 HA 0.902256
Update 356  TP -186.666248  HP -26.043015   TA 0.942398 HA 0.924812
Update 361  TP -185.613978  HP -26.414339   TA 0.943343 HA 0.917293
Update 366  TP -191.048096  HP -27.472219   TA 0.941454 HA 0.924812
Update 371  TP -184.624443  HP -26.844027   TA 0.941454 HA 0.924812
Update 376  TP -200.369773  HP -30.700597   TA 0.934844 HA 0.917293
Update 381  TP -188.717821  HP -28.962984   TA 0.941454 HA 0.917293
Update 386  TP -174.172052  HP -27.522189   TA 0.943343 HA 0.902256
Update 391  TP -180.526427  HP -28.048715   TA 0.942398 HA 0.917293
Update 396  TP -180.270376  HP -28.029806   TA 0.944287 HA 0.917293
Update 401  TP -176.965924  HP -27.645730   TA 0.946176 HA 0.924812
Update 406  TP -162.432064  HP -24.368904   TA 0.949008 HA 0.939850
Update 411  TP -174.300448  HP -24.079402   TA 0.945231 HA 0.924812
Update 416  TP -175.085674  HP -24.124952   TA 0.943343 HA 0.924812
Update 421  TP -190.616137  HP -28.334092   TA 0.924457 HA 0.917293
Update 426  TP -178.145648  HP -26.727177   TA 0.935788 HA 0.917293
Update 431  TP -177.091264  HP -26.379356   TA 0.943343 HA 0.924812
Update 436  TP -176.690962  HP -26.256872   TA 0.943343 HA 0.924812
Update 441  TP -176.910997  HP -26.224153   TA 0.943343 HA 0.932331
Update 446  TP -176.356111  HP -26.091869   TA 0.946176 HA 0.924812
Update 451  TP -173.676681  HP -25.809017   TA 0.945231 HA 0.924812
Update 456  TP -165.784838  HP -25.683783   TA 0.937677 HA 0.917293
Update 461  TP -162.969528  HP -25.278811   TA 0.938621 HA 0.924812
Update 466  TP -157.150748  HP -26.664366   TA 0.942398 HA 0.939850
Update 471  TP -155.330369  HP -26.436157   TA 0.946176 HA 0.939850
Update 476  TP -156.269200  HP -26.619727   TA 0.943343 HA 0.932331
Update 481  TP -153.032198  HP -26.622674   TA 0.946176 HA 0.932331
Update 486  TP -153.077860  HP -26.634875   TA 0.946176 HA 0.932331
Update 491  TP -163.266954  HP -29.026493   TA 0.938621 HA 0.924812
Update 496  TP -158.735202  HP -28.019265   TA 0.943343 HA 0.924812
Update 501  TP -158.983870  HP -27.991894   TA 0.943343 HA 0.924812
Update 506  TP -148.494066  HP -25.641493   TA 0.949953 HA 0.939850
Update 511  TP -146.867234  HP -25.819213   TA 0.951841 HA 0.939850
Update 516  TP -142.546120  HP -27.249221   TA 0.950897 HA 0.932331
Update 521  TP -137.159511  HP -26.681022   TA 0.950897 HA 0.939850
Update 526  TP -136.810356  HP -27.618944   TA 0.957507 HA 0.909774
Update 531  TP -136.136556  HP -27.659269   TA 0.958451 HA 0.917293
Update 536  TP -135.406272  HP -27.518928   TA 0.958451 HA 0.924812
Update 541  TP -130.961703  HP -25.756598   TA 0.956563 HA 0.947368
Update 546  TP -137.853970  HP -24.393860   TA 0.955619 HA 0.917293
Update 551  TP -143.470712  HP -25.241174   TA 0.948064 HA 0.924812
Update 556  TP -155.611704  HP -27.087631   TA 0.948064 HA 0.909774
Update 561  TP -138.749602  HP -23.155117   TA 0.952786 HA 0.947368
Update 566  TP -141.048967  HP -23.608341   TA 0.950897 HA 0.939850
Update 571  TP -137.377491  HP -22.877327   TA 0.955619 HA 0.947368
Update 576  TP -142.258045  HP -23.491014   TA 0.952786 HA 0.932331
Update 581  TP -132.882306  HP -22.074784   TA 0.956563 HA 0.932331
Update 586  TP -133.567896  HP -22.105316   TA 0.958451 HA 0.932331
Update 591  TP -132.363768  HP -21.983073   TA 0.959396 HA 0.932331
Update 596  TP -108.276198  HP -20.104452   TA 0.966006 HA 0.954887
Update 601  TP -104.287052  HP -20.415687   TA 0.968839 HA 0.939850
Update 606  TP -99.249752   HP -19.529931   TA 0.970727 HA 0.947368
Update 611  TP -100.621381  HP -19.945264   TA 0.969783 HA 0.932331
Update 616  TP -100.947898  HP -20.687523   TA 0.971671 HA 0.939850
Update 621  TP -101.141672  HP -20.674405   TA 0.974504 HA 0.939850
Update 626  TP -98.741185   HP -20.198537   TA 0.973560 HA 0.939850
Update 631  TP -96.729334   HP -20.006196   TA 0.973560 HA 0.947368
Update 636  TP -97.463795   HP -20.238314   TA 0.973560 HA 0.939850
Update 641  TP -108.923775  HP -22.161219   TA 0.965061 HA 0.932331
Update 646  TP -115.911317  HP -23.321361   TA 0.959396 HA 0.924812
Update 651  TP -96.556726   HP -20.501767   TA 0.973560 HA 0.947368
Update 656  TP -87.052109   HP -19.410833   TA 0.976393 HA 0.947368
Update 661  TP -86.705171   HP -19.442150   TA 0.976393 HA 0.947368
Update 666  TP -85.722968   HP -19.303448   TA 0.975449 HA 0.947368
Update 671  TP -84.791787   HP -19.380819   TA 0.975449 HA 0.947368
Update 676  TP -84.643333   HP -19.317284   TA 0.974504 HA 0.947368
Update 681  TP -84.595007   HP -19.607396   TA 0.975449 HA 0.947368
Update 686  TP -81.248356   HP -18.935263   TA 0.976393 HA 0.947368
Update 691  TP -81.001722   HP -18.873729   TA 0.977337 HA 0.947368
Update 696  TP -79.395358   HP -18.578031   TA 0.979226 HA 0.947368
Update 701  TP -79.490545   HP -18.592180   TA 0.977337 HA 0.939850
Update 706  TP -83.569824   HP -20.300397   TA 0.978281 HA 0.954887
Update 711  TP -85.240907   HP -20.584531   TA 0.979226 HA 0.954887
Update 716  TP -85.398940   HP -20.717173   TA 0.980170 HA 0.954887
Update 721  TP -82.558771   HP -20.431777   TA 0.980170 HA 0.962406
Update 726  TP -78.803483   HP -19.842814   TA 0.980170 HA 0.954887
Update 731  TP -75.628432   HP -19.288610   TA 0.981114 HA 0.954887
Update 736  TP -76.028573   HP -19.161656   TA 0.982059 HA 0.954887
Update 741  TP -75.668469   HP -19.106280   TA 0.983003 HA 0.962406
Update 746  TP -75.630350   HP -19.091562   TA 0.983003 HA 0.962406
Update 751  TP -71.729778   HP -18.842223   TA 0.983947 HA 0.954887
Update 756  TP -73.817389   HP -19.248645   TA 0.981114 HA 0.954887
Update 761  TP -72.153189   HP -19.091297   TA 0.982059 HA 0.939850
Update 766  TP -74.136272   HP -19.466283   TA 0.978281 HA 0.954887
Update 771  TP -73.549283   HP -19.405029   TA 0.978281 HA 0.954887
Update 776  TP -67.159969   HP -17.833027   TA 0.984891 HA 0.969925
Update 781  TP -67.082021   HP -18.459729   TA 0.987724 HA 0.947368
Update 786  TP -66.060272   HP -18.452345   TA 0.986780 HA 0.954887
Update 791  TP -63.961442   HP -18.412315   TA 0.988669 HA 0.954887
Update 796  TP -62.997624   HP -18.072387   TA 0.988669 HA 0.954887
Update 801  TP -62.918908   HP -18.135388   TA 0.989613 HA 0.962406
Update 806  TP -62.688904   HP -18.025445   TA 0.989613 HA 0.954887
Update 811  TP -62.472275   HP -18.291454   TA 0.989613 HA 0.954887
Update 816  TP -61.842198   HP -18.138221   TA 0.989613 HA 0.947368
Update 821  TP -62.133552   HP -18.210771   TA 0.989613 HA 0.947368
Update 826  TP -75.856289   HP -16.607149   TA 0.981114 HA 0.962406
Update 831  TP -73.358464   HP -16.178817   TA 0.982059 HA 0.962406
Update 836  TP -72.462434   HP -16.060280   TA 0.983003 HA 0.962406
Update 841  TP -67.546836   HP -15.433451   TA 0.984891 HA 0.954887
Update 846  TP -66.750811   HP -15.339099   TA 0.985836 HA 0.954887
Update 851  TP -65.967439   HP -15.196042   TA 0.985836 HA 0.954887
Update 856  TP -67.759002   HP -15.564747   TA 0.984891 HA 0.947368
Update 861  TP -66.298995   HP -15.216370   TA 0.984891 HA 0.954887
Update 866  TP -65.681711   HP -15.126616   TA 0.984891 HA 0.954887
Update 871  TP -65.433255   HP -15.060031   TA 0.985836 HA 0.954887
Update 876  TP -65.111571   HP -15.045882   TA 0.985836 HA 0.954887
Update 881  TP -65.100985   HP -15.043008   TA 0.985836 HA 0.954887
Update 886  TP -63.928069   HP -14.986261   TA 0.985836 HA 0.954887
Update 891  TP -63.587300   HP -14.906230   TA 0.985836 HA 0.947368
Update 896  TP -75.201154   HP -17.552294   TA 0.977337 HA 0.939850
Update 901  TP -76.600617   HP -17.852918   TA 0.977337 HA 0.939850
Update 906  TP -68.297833   HP -16.696486   TA 0.981114 HA 0.939850
Update 911  TP -68.264441   HP -16.809956   TA 0.981114 HA 0.939850
Update 916  TP -81.030383   HP -19.781408   TA 0.977337 HA 0.939850
Update 921  TP -83.587699   HP -20.303622   TA 0.976393 HA 0.939850
Update 926  TP -51.760302   HP -14.733039   TA 0.991501 HA 0.954887
Update 931  TP -51.721019   HP -14.722346   TA 0.991501 HA 0.954887
Update 936  TP -51.727488   HP -14.712416   TA 0.991501 HA 0.954887
Update 941  TP -53.529861   HP -15.422120   TA 0.988669 HA 0.954887
Update 946  TP -53.503014   HP -15.411191   TA 0.988669 HA 0.954887
Update 951  TP -53.513587   HP -15.416141   TA 0.988669 HA 0.954887
Update 956  TP -52.539275   HP -15.191815   TA 0.988669 HA 0.962406
Update 961  TP -50.383375   HP -14.970621   TA 0.992446 HA 0.947368
Update 966  TP -50.066451   HP -14.889169   TA 0.992446 HA 0.954887
Update 971  TP -49.688095   HP -14.835450   TA 0.992446 HA 0.954887
Update 976  TP -48.829483   HP -14.656224   TA 0.994334 HA 0.954887
Update 981  TP -48.855078   HP -14.677094   TA 0.993390 HA 0.954887
Update 986  TP -47.048355   HP -14.302414   TA 0.993390 HA 0.954887
Update 991  TP -46.419107   HP -14.297946   TA 0.994334 HA 0.962406
Update 996  TP -46.055572   HP -14.234956   TA 0.994334 HA 0.962406
Update 1001 TP -46.364974   HP -14.406804   TA 0.995279 HA 0.962406
Update 1006 TP -46.270797   HP -14.337114   TA 0.995279 HA 0.962406
Update 1011 TP -48.852637   HP -14.417459   TA 0.992446 HA 0.939850
Update 1016 TP -49.015615   HP -14.472951   TA 0.992446 HA 0.939850
Update 1021 TP -47.131771   HP -14.275712   TA 0.993390 HA 0.947368
Update 1026 TP -46.839757   HP -14.328696   TA 0.992446 HA 0.947368
Update 1031 TP -46.922607   HP -14.802430   TA 0.993390 HA 0.947368
Update 1036 TP -44.584294   HP -14.695685   TA 0.994334 HA 0.947368
Update 1041 TP -44.009755   HP -14.411614   TA 0.993390 HA 0.947368
Update 1046 TP -43.485524   HP -14.403322   TA 0.994334 HA 0.947368
Update 1051 TP -43.544958   HP -14.582921   TA 0.995279 HA 0.947368
Update 1056 TP -43.548111   HP -14.584363   TA 0.995279 HA 0.947368
```

Hints
-

1.  As with the previous assignment, make sure that you debug on small
    datasets first (I've provided _toy text_ in the data directory to get you started).
1.  Certainly make sure that you do the unregularized version first
    and get it to work well.
1.  Use numpy functions whenever you can to make the computation faster.


