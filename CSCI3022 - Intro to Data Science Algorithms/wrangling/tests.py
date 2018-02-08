import unittest
import pickle
from csv import DictReader
from collections import Counter

from districts import district_margins, all_states, all_state_rows
from word_counts import text_from_zipfile, words, accumulate_counts

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

class TestDistrictMargins(unittest.TestCase):

    def test_margins(self):
        lines = list(DictReader(kALASKA))
        self.assertAlmostEqual(10.0, district_margins(lines)[0])

    def test_states(self):
        lines = list(DictReader(kALASKA))
        self.assertEqual(all_states(lines), set(["Alaska"]))
        self.assertEqual(all_states([]), set([]))

    def test_filter(self):
        lines = list(DictReader(kALASKA))
        self.assertEqual(list(all_state_rows(lines, "Bliss")), [])        
        self.assertEqual(list(all_state_rows(lines, "Alaska")), lines)

class TestWordCounts(unittest.TestCase):
    def test_zip(self):
        self.assertEqual(set(str(x) for x in
                             text_from_zipfile("../data/test.zip")),
                         set(["FOO\n", "BAR\n", "BAZ\n"]))

    def test_words(self):
        self.assertEqual(set(words("Yes, we can certainly find real words, Frank!")),
                         set(["certainly", "find", "real", "words", "frank"]))

    def test_accumulate_counts(self):
        self.assertEqual(Counter(["a", "b", "c", "c"]),
                         accumulate_counts(["a", "b", "c", "c"]))

class TestAuto(unittest.TestCase):
    def test_auto(self):
        with open("public.pkl", 'rb') as infile:
            key = pickle.load(infile)
            for fname in key:
                for ii, rr in key[fname]:
                    check_against = globals()[fname](ii)
                    print("Testing %s\n\tInput: %s\n\tExpected: %s\n\tGot: %s" %
                          (fname, str(ii)[:60], str(rr)[:60], str(check_against)[:60]))
                    if isinstance(rr, dict):
                        for jj in rr:
                            self.assertTrue(jj in check_against,
                                            msg="Missing key %s in test %s" %
                                            (jj, fname))
                            self.assertAlmostEqual(rr[jj], check_against[jj],
                                                   places=2)
                        self.assertEqual(rr.keys(), check_against.keys())
                    else:
                        self.assertEqual(rr, check_against)
                    
if __name__ == '__main__':
    unittest.main()
