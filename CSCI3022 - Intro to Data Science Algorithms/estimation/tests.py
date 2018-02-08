import unittest
import pickle
from csv import DictReader
from collections import Counter
from math import log

from districts import ml_mean, ml_variance, log_probability, republican_share
from lm import BigramLanguageModel, kSTART, kEND

kALASKA = """LINE,STATE ABBREVIATION,STATE,D,FEC ID#,(I),CANDIDATE NAME (First),CANDIDATE NAME (Last),CANDIDATE NAME,TOTAL VOTES,PARTY,PRIMARY VOTES,PRIMARY %,RUNOFF VOTES,RUNOFF %,GENERAL VOTES ,GENERAL %,GE RUNOFF ELECTION VOTES (LA),GE RUNOFF ELECTION % (LA),"COMBINED GE PARTY TOTALS (CT, NY, SC)","COMBINED % (CT, NY, SC)",GE WINNER INDICATOR,FOOTNOTES
52,AK,Alaska,0,H6AK00045,(I),Don,Young,"Young, Don",,R,"79,393","74,29%",,,"142,572","50,97%",,,,,W,
53,AK,Alaska,0,H0AK00097,,John R.,Cox,"Cox, John R.",,R,"14,497","13,57%",,,,,,,,,,
54,AK,Alaska,0,H4AK00149,,David  ,Seaward,"Seaward, David  ",,R,"7,604","7,12%",,,,,,,,,,
55,AK,Alaska,0,H4AK00131,,"David,Dohner,"Dohner, David",,R,"5,373","5,03%",,,,,,,,,,
56,AK,Alaska,0,n/a,,,,,Party Votes:,R,"106,867",,,,,,,,,,,
57,AK,Alaska,0,H4AK00123,,Forrest ,Dunbar,"Dunbar, Forrest ",,D,"38,735","80,92%",,,"114,602","40,97%",,,,,,
58,AK,Alaska,0,H4AK00057,,Frank J.,Vondersaar,"Vondersaar, Frank J.",,D,"9,132","19,08%",,,,,,,,,,
59,AK,Alaska,0,n/a,,,,,Party Votes:,D,"47,867",,,,,,,,,,,
60,AK,Alaska,0,H2AK00143,,Jim C.,McDermott,"McDermott, Jim C.",,LIB,"13,437","100,00%",,,"21,29","7,61%",,,,,,
61,AK,Alaska,0,n/a,,,,,Party Votes:,LIB,"13,437",,,,,,,,,,,
62,AK,Alaska,0,n/a,,,,Scattered,,W,,,,,"1,277","0,46%",,,,,,
63,AK,Alaska,0,n/a,,,,,District Votes:,,"168,171",,,,"279,741",,,,,,,
64,AK,Alaska,H,n/a,,,,,Total State Votes:,,"168,171",,,,"279,741",,,,,,,
65,AK,Alaska,,n/a,,,,,,,,,,,,,,,,,,
66,AK,Alaska,,n/a,,,,,,,,,,,,,,,,,,
""".split("\n")

class TestDistrictNormals(unittest.TestCase):

    def test_mean(self):
        vals = [0, 100]
        self.assertAlmostEqual(ml_mean(vals), 50, places=3)

    def test_variance(self):
        vals = [0, 100]
        self.assertAlmostEqual(ml_variance(vals, 50), 2500, places=3)

    def test_logprob(self):
        self.assertAlmostEqual(log_probability(-1.0, 0.0, 1.0),
                               log(0.24197072451914337),
                               places=3)
        self.assertAlmostEqual(log_probability(-1.0, 0.0, 0.9),
                                            -1.421813830931315,
                                            places=3)
        
    def test_share(self):
        lines = list(DictReader(kALASKA))
        self.assertEqual(list(republican_share(lines, ["Alaska"]).keys()), 
                         [("Alaska", 0)])
        self.assertAlmostEqual(republican_share(lines, ["Alaska"])[("Alaska", 0)],
                               50.97, places=1)
        self.assertEqual(republican_share(lines, ["Bliss"]), {})                         


class TestLanguageModel(unittest.TestCase):
    def test_vocab(self):
        lm = BigramLanguageModel()
        lm.train_seen("the")
        lm.finalize()
        self.assertEqual(lm.vocab(), [kEND, kSTART, "the"])
    
    def test_logprob_single_word(self):
        lm = BigramLanguageModel()
        lm.train_seen("the")
        lm.finalize()
        lm.add_train("the")
        lm.add_train("")
        
        self.assertAlmostEqual(lm.laplace("the", kEND), log(.5), places=3)
        self.assertAlmostEqual(lm.laplace(kSTART, "the"), log(.4), places=3)
    
    def test_logprob_two_words(self):
        lm = BigramLanguageModel()
        lm.train_seen("the")
        lm.train_seen("nation")
        lm.finalize()
        lm.add_train("the nation")
        lm.add_train("nation")
        lm.add_train("the")

        self.assertAlmostEqual(lm.laplace("the", "nation"), log(2/6.), places=3)
        self.assertAlmostEqual(lm.laplace(kSTART, kEND), log(1/7.), places=3)
    
    def test_generate(self):
        lm = BigramLanguageModel()
        lm.train_seen("likely")
        lm.train_seen("unlikely")
        lm.finalize()
        
        for ii in range(10000):
            lm.add_train("likely")
        
        count = Counter()
        for ii in range(100):
            sent = list(lm.sample(1))
            count[sent[1]] += 1
        self.assertTrue(count["likely"] > 98)



if __name__ == '__main__':
    unittest.main()
