from math import log, exp
from collections import defaultdict, Counter
from zipfile import ZipFile
from random import random
import re

kNEG_INF = -1e6

kSTART = "<s>"
kEND = "</s>"

kWORDS = re.compile("[a-z]{1,}")
kREP = set(["Bush", "GWBush", "Eisenhower", "Ford", "Nixon", "Reagan"])
kDEM = set(["Carter", "Clinton", "Truman", "Johnson", "Kennedy"])

class OutOfVocab(Exception):
    def __init__(self, value):
        self.value = value
        
    def __str__(self):
        return repr(self.value)

def sentences_from_zipfile(zip_file, filter_presidents):
    """
    Given a zip file, yield an iterator over the lines in each file in the
    zip file.
    """
    with ZipFile(zip_file) as z:
        for ii in z.namelist():
            try:
                pres = ii.replace(".txt", "").replace("state_union/", "").split("-")[1]
            except IndexError:
                continue

            if pres in filter_presidents:
                for jj in z.read(ii).decode(errors='replace').split("\n")[3:]:
                    yield jj.lower()

def tokenize(sentence):
    """
    Given a sentence, return a list of all the words in the sentence.
    """
    
    return kWORDS.findall(sentence.lower())

def bigrams(sentence):
    """
    Given a sentence, generate all bigrams in the sentence.
    """
    
    for ii, ww in enumerate(sentence[:-1]):
        yield ww, sentence[ii + 1]




class BigramLanguageModel:

    def __init__(self):
        self._vocab = set([kSTART, kEND])
        
        # Add your code here!
        # Bigram counts
        self.bgcounts = Counter()
        self.ugcounts = Counter()
        self.bgTotal = 0
        self.vocabTotal = 0
        self._vocab_final = False

    def train_seen(self, word):
        """
        Tells the language model that a word has been seen.  This
        will be used to build the final vocabulary.
        """
        assert not self._vocab_final, \
            "Trying to add new words to finalized vocab"

        # Add your code here!
        self._vocab.add(word)

    def generate(self, context):
        """
        Given the previous word of a context, generate a next word from its
        conditional language model probability.  
        """

        # Add your code here.  Make sure to the account for the case
        # of a context you haven't seen before and Don't forget the
        # smoothing "+1" term while sampling.

        # Your code here
        #print("In Generate")
        """
        word = ''
        lapMax = kNEG_INF
        for i in self._vocab:
            lap = self.laplace(context,i)
            if(lap > lapMax):
                word = i
                lapMax = lap
        return word
        """
        """
        tmpCounter = Counter()
        for bg,n in self.bgcounts.items():
            if(bg[0] == context):
                tmpCounter[bg] = n

        return tmpCounter.most_common(1)[0][0][1]
        """
        threshold = random()
        pbin = 0
        for word in self._vocab:
            p = exp(self.laplace(context,word))
            pbin += p
            if(pbin > threshold):return word
            
    def sample(self, sample_size):
        """
        Generate an English-like string from a language model of a specified
        length (plus start and end tags).
        """

        # You should not need to modify this function
        yield kSTART
        next = kSTART
        for ii in range(sample_size):
            next = self.generate(next)
            if next == kEND:
                break
            else:
                yield next
        yield kEND
            
    def finalize(self):
        """
        Fixes the vocabulary as static, prevents keeping additional vocab from
        being added
        """
        
        # you should not need to modify this function
        self.vocabTotal = len(self._vocab)
        self._vocab_final = True

    def tokenize_and_censor(self, sentence):
        """
        Given a sentence, yields a sentence suitable for training or testing.
        Prefix the sentence with <s>, generate the words in the
        sentence, and end the sentence with </s>.
        """

        # you should not need to modify this function
        
        yield kSTART
        for ii in tokenize(sentence):
            if ii not in self._vocab:
                raise OutOfVocab(ii)
            yield ii
        yield kEND

    def vocab(self):
        """
        Returns the language model's vocabulary
        """

        assert self._vocab_final, "Vocab not finalized"
        return list(sorted(self._vocab))
        
    def laplace(self, context, word):
        """
        Return the log probability (base e) of a word given its context
        """

        assert context in self._vocab, "%s not in vocab" % context
        assert word in self._vocab, "%s not in vocab" % word

        # Add your code here
        #return log((self.bgcounts[context,word]+1)/(self.vocabTotal + sum(j for i,j in self.bgcounts.items() if i[0] == context)))
        return log((self.bgcounts[context,word]+1)/(self.vocabTotal + self.ugcounts[context]))

    def add_train(self, sentence):
        """
        Add the counts associated with a sentence.
        """

        # You'll need to complete this function, but here's a line of code that
        # will hopefully get you started.
        sentList = list(self.tokenize_and_censor(sentence))
        for context, word in bigrams(sentList):
            #None
            # ---------------------------------------
            assert word in self._vocab, "%s not in vocab" % word
            self.bgcounts.update({(context,word)})
            self.bgTotal += 1
        for word in sentList:
            self.ugcounts.update([word])


    def log_likelihood(self, sentence):
        """
        Compute the log likelihood of a sentence, divided by the number of
        tokens in the sentence.
        """
        sent = list(self.tokenize_and_censor(sentence))
        prob = 0
        for context,word in bigrams(sent):
            p = self.laplace(context,word)
            prob += p
        return prob/len(sent)


if __name__ == "__main__":
    dem_lm = BigramLanguageModel()
    rep_lm = BigramLanguageModel()

    for target, pres, name in [(dem_lm, kDEM, "D"), (rep_lm, kREP, "R")]:
        for sent in sentences_from_zipfile("../data/state_union.zip", pres):
            for ww in tokenize(sent):
                target.train_seen(ww)
                
        print("Done looking at %s words, finalizing vocabulary" % name)
        target.finalize()
        
        for sent in sentences_from_zipfile("../data/state_union.zip", pres):
            target.add_train(sent)
    
        print("Trained language model for %s" % name)

    obamaVocab = set()
    obamaBigrams = set()
    with open("../data/2016-obama.txt", encoding='utf8') as infile:
        print("REP\t\tDEM\t\tSentence\n" + "=" * 80)
        for ii in infile:
            
            if len(ii) < 15: # Ignore short sentences
                continue
            try:
                dem_score = dem_lm.log_likelihood(ii)
                rep_score = rep_lm.log_likelihood(ii)

                print("%f\t%f\t%s" % (dem_score, rep_score, ii.strip()))
            except OutOfVocab:
                None
            
            """
            for word in tokenize(ii):
                if word not in rep_lm._vocab and word not in dem_lm._vocab:
                    obamaVocab.add(word)
            """
            """
            for bg in bigrams(tokenize(ii)):
                if bg not in rep_lm.bgcounts and bg not in dem_lm.bgcounts:
                    obamaBigrams.add(bg)
    print(obamaVocab)
    print(obamaBigrams)
    """
    print("Democrat sentence:")
    print(' '.join(list(dem_lm.sample(50))))
    print("Republican Sentence:")
    print(' '.join(list(rep_lm.sample(50))))
