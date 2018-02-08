import unittest

from logreg import LogReg, Example

kTOY_VOCAB = "BIAS_CONSTANT A B C D".split()
kPOS = Example(1, "A:4 B:3 C:1".split(), kTOY_VOCAB, None)
kNEG = Example(0, "B:2 C:3 D:1".split(), kTOY_VOCAB, None)

class TestLogReg(unittest.TestCase):
    def setUp(self):
        self.logreg_learnrate = LogReg(5, 0.0, lambda x: 0.5)
        self.logreg_unreg = LogReg(5, 0.0, lambda x: 1.0)
        self.logreg_reg = LogReg(5, 0.25, lambda x: 1.0)

    def test_learnrate(self):
        print("\nTesting: Learning Rate Usage")
        print(self.logreg_learnrate.w)
        print(kPOS.x)
        w = self.logreg_learnrate.sg_update(kPOS, 0)
        self.assertAlmostEqual(w[0], 0.25)
        self.assertAlmostEqual(w[1], 1.00)
        self.assertAlmostEqual(w[2], 0.75)
        self.assertAlmostEqual(w[3], 0.25)
        self.assertAlmostEqual(w[4], 0.0)

        print(self.logreg_learnrate.w)
        print(kNEG.x)
        w = self.logreg_learnrate.sg_update(kNEG, 1)
        self.assertAlmostEqual(w[0], -0.21207090998937828)
        self.assertAlmostEqual(w[1], 1.0)
        self.assertAlmostEqual(w[2], -0.17414181997875655)
        self.assertAlmostEqual(w[3], -1.1362127299681348)
        self.assertAlmostEqual(w[4], -0.46207090998937828)       

    def test_unreg(self):
        print("\nTesting: Unregularized Update")
        print(self.logreg_unreg.w)
        print(kPOS.x)
        w = self.logreg_unreg.sg_update(kPOS, 0)
        self.assertAlmostEqual(w[0], .5)
        self.assertAlmostEqual(w[1], 2.0)
        self.assertAlmostEqual(w[2], 1.5)
        self.assertAlmostEqual(w[3], 0.5)
        self.assertAlmostEqual(w[4], 0.0)

        print(self.logreg_unreg.w)
        print(kNEG.x)
        w = self.logreg_unreg.sg_update(kNEG, 1)
        self.assertAlmostEqual(w[0], -0.49330714907571527)
        self.assertAlmostEqual(w[1], 2.0)
        self.assertAlmostEqual(w[2], -0.48661429815143054)
        self.assertAlmostEqual(w[3], -2.479921447227146)
        self.assertAlmostEqual(w[4], -0.99330714907571527)

    def test_reg(self):
        print("\nTesting: Regularized Update")
        print(self.logreg_reg.w)
        print(kPOS.x)
        w = self.logreg_reg.sg_update(kPOS, 0)
        self.assertAlmostEqual(w[0], .5)
        self.assertAlmostEqual(w[1], 1.0)
        self.assertAlmostEqual(w[2], 0.75)
        self.assertAlmostEqual(w[3], 0.25)
        self.assertAlmostEqual(w[4], 0.0)

        print(self.logreg_reg.w)
        print(kNEG.x)
        w = self.logreg_reg.sg_update(kNEG, 1)
        self.assertAlmostEqual(w[0], -0.43991334982599239)
        self.assertAlmostEqual(w[1], 1.0)
        self.assertAlmostEqual(w[2], -0.56491334982599239)
        self.assertAlmostEqual(w[3], -1.2848700247389886)
        self.assertAlmostEqual(w[4], -0.2349783374564981)

        self.logreg_reg.get_best_features(2,kTOY_VOCAB)



if __name__ == '__main__':
    unittest.main()
