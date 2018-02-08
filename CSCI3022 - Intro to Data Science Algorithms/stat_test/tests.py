import unittest
import pickle
from csv import DictReader
from collections import Counter
from math import log

from numpy import array

from bigrams import BigramFinder, chisquare_pvalue
from ttest import degrees_of_freedom, unbiased_sample_variance
from ttest import t_statistic, t_test

class TestBigramFinder(unittest.TestCase):
    def setUp(self):
        self._bf_empty = BigramFinder(min_unigram=2, max_unigram=100, min_ngram=5,
                                      exclude=["c"])
        
        self._bf_loaded = BigramFinder(min_unigram=2, max_unigram=100, min_ngram=5,
                                        exclude=["e"])

        corpus = ["cbdecbaec"] + ["abe"] * 10 + ["bce"] * 5 + ["ff"] * 200
        for ii in corpus:
            self._bf_loaded.vocab_scan(ii)

        self._bf_loaded.finalize()

        for ii in corpus:
            self._bf_loaded.add_sentence(ii)

    def testVocab(self):        
        self._bf_empty.vocab_scan("aaaaaabcccccc")
        for ii in range(105):
            self._bf_empty.vocab_scan("d")
        self._bf_empty.finalize()
        self.assertEqual(self._bf_empty.vocab(), set("a"))

    def testObservations(self):
        obs, ex = self._bf_loaded.observed_and_expected(("b", "c"))

        for ii, jj in zip(obs.flatten(), [5.0, 2.0, 12.0, 219.0]):
            self.assertAlmostEqual(ii, jj, places=3)

        for ii, jj in zip(ex.flatten(),
                          array([0.5, 6.5, 16.5, 214.5])):
            self.assertAlmostEqual(ii, jj, places=1)

    def testBigramList(self):
        bigrams = set(self._bf_loaded.valid_bigrams())
        self.assertEqual(bigrams, set([('b', 'c'), ('a', 'b')]))
            
    def testChiSquarePValue(self):
        obs = array([[36, 14], [30, 25]])
        ex = array([[31.43, 18.57], [34.57, 20.43]])

        self.assertAlmostEqual(chisquare_pvalue(obs, ex), 0.0644, places=2)
            
    def testVar(self):
        x = [9, 2, 1]
        self.assertAlmostEqual(unbiased_sample_variance(x, 4), 19.0)

    def testDegreesOfFreedom(self):
        self.assertAlmostEqual(degrees_of_freedom(1, 2, 4, 8), 42/5.)

    def testStatistic(self):
        self.assertAlmostEqual(t_statistic(27.15, 11.95, 20, 20, 156.5, 213.7444),
                               3.532761644279526, places=2)

    def testTPValue(self):
        v1 = [5, 7, 5, 3, 5, 3, 3, 9, 50, 100]
        v2 = [8, 1, 4, 6, 6, 4, 1, 2, 5]

        self.assertAlmostEqual(t_test(v1, v2), 0.175, places=2)
                    
if __name__ == '__main__':
    unittest.main()
