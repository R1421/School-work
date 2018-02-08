import unittest

from vc_sin import train_sin_classifier


class TestLearnability(unittest.TestCase):

    def test_vc_one_point_pos(self):
        data_pos = [(1, False)]

        classifier_pos = train_sin_classifier(data_pos)

        for kk, yy in data_pos:
            self.assertEqual(True if yy == +1 else False,
                             classifier_pos.classify(kk))

    def test_vc_one_point_neg(self):
        data_neg = [(1, True)]

        classifier_neg = train_sin_classifier(data_neg)

        for kk, yy in data_neg:
            self.assertEqual(True if yy == +1 else False,
                             classifier_neg.classify(kk))

    def test_vc_three_points(self):
        data = [(1, False), (2, True), (3, False)]
        classifier = train_sin_classifier(data)

        for kk, yy in data:
            self.assertEqual(True if yy == +1 else False,
                             classifier.classify(kk))

    def test_vc_four_points(self):
        data = [(1, False), (2, True), (3, False), (5, False)]
        classifier = train_sin_classifier(data)

        for kk, yy in data:
            self.assertEqual(True if yy == +1 else False,
                             classifier.classify(kk))

if __name__ == '__main__':
    unittest.main()
