from math import sqrt

from scipy.stats import t
from numpy import mean

def degrees_of_freedom(s1, s2, n1, n2):
    """
    Compute the number of degrees of freedom using the Satterhwaite Formula
    
    @param s1 The unbiased sample variance of the first sample
    @param s2 The unbiased sample variance of the second sample
    @param n1 Thu number of observations in the first sample
    @param n2 The number of observations in the second sample
    """
    f1 = s1/n1
    f2 = s2/n2
    numerator = (f1 + f2)**2
    denominator = f1**2/(n1-1) + f2**2/(n2-1)

    return numerator/denominator

def unbiased_sample_variance(observations, mean):
    """
    Compute the unbiased sample variance

    @param observations Iterable set of observations
    @param mean The estimated mean
    """

    return sum((x-mean)**2 for x in observations)/(len(observations)-1)

def t_statistic(mean1, mean2, n1, n2, svar1, svar2):
    """
    Compute the t-statistic for the given estimates
    """

    # Complete this funtion
    return (mean1-mean2)/(svar1/n1 + svar2/n2)**0.5

def t_test(sample1, sample2):
    """
    Return the two-tailed p-value of a t test with unequal variance for two samples.

    @param sample1 An iterable of the first sample
    @param sample2 An iterable of the second sample
    """
    n1 = len(sample1)
    n2 = len(sample2)
    m1 = sum(sample1)/n1
    m2 = sum(sample2)/n2
    s1 = unbiased_sample_variance(sample1, m1)
    s2 = unbiased_sample_variance(sample2, m2)
    df = degrees_of_freedom(s1,s2,n1,n2)
    tstat = t_statistic(m1,m2,n1,n2,s1,s2)

    if(tstat < 0): return 2*t.cdf(stat,df)
    return  2*(1-t.cdf(tstat,df))

if __name__ == "__main__":
    v1 = [5, 7, 5, 3, 5, 3, 3, 9]
    v2 = [8, 1, 4, 6, 6, 4, 1, 2]

    print("p-value is %f" % t_test(v1, v2))
    
