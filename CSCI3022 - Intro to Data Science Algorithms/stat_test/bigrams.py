import re
import operator
from collections import Counter
from zipfile import ZipFile

from numpy import array
from scipy import zeros
from scipy.stats import chisquare

kWORDS = re.compile("[a-z]{1,}")
kSTOPWORDS = set(['i', 'me', 'my', 'myself', 'we', 'our', 'ours', 'ourselves', 'yo',
                  'your', 'yours', 'yourself', 'yourselves', 'he', 'him', 'his',
                  'himself', 'she', 'her', 'hers', 'herself', 'it', 'its', 'itself',
                  'they', 'them', 'their', 'theirs', 'themselves', 'what', 'which',
                  'who', 'whom', 'this', 'that', 'these', 'those', 'am', 'is', 'are',
                  'was', 'were', 'be', 'been', 'being', 'have', 'has', 'had', 'having',
                  'do', 'does', 'did', 'doing', 'a', 'an', 'the', 'and', 'but', 'if',
                  'or', 'because', 'as', 'until', 'while', 'of', 'at', 'by', 'for',
                  'with', 'about', 'against', 'between', 'into', 'through', 'during',
                  'before', 'after', 'above', 'below', 'to', 'from', 'up', 'down', 'in',
                  'out', 'on', 'off', 'over', 'under', 'again', 'further', 'then',
                  'once', 'here', 'there', 'when', 'where', 'why', 'how', 'all', 'any',
                  'both', 'each', 'few', 'more', 'most', 'other', 'some', 'such', 'no',
                  'nor', 'not', 'only', 'own', 'same', 'so', 'than', 'too', 'very',
                  's', 't', 'can', 'will', 'just', 'don', 'should', 'now', 've', 'm'])

def bigrams(sentence):
    """
    Given a sentence, generate all bigrams in the sentence.
    """
    
    for ii, ww in enumerate(sentence[:-1]):
        yield ww, sentence[ii + 1]

def tokenize(sentence):
    """
    Given a sentence, return a list of all the words in the sentence.
    """
    
    return kWORDS.findall(sentence.lower())

def sentences_from_zipfile(zip_file):
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

            for jj in z.read(ii).decode(errors='replace').split("\n")[3:]:
                yield jj.lower()

def chisquare_pvalue(obs, ex):
    """
    Given a 2x2 contingency table both observed and expected, returns the
    corresponding chisquared p-value.

    @param obs An array (list of lists or numpy array) of observed values
    @param obs An array (list of lists or numpy array) of expected values
    """

    i,j = chisquare(obs.ravel(),ex.ravel(),2)
    return j

class BigramFinder:
    """
    Finds bigrams in a stream of text.
    """

    def __init__(self, min_unigram = 10, max_unigram = 150, min_ngram = 5,
                 exclude=[]):
        """
        Instantiates the class.

        @param min_ngram Ignore bigrams that appear fewer than this many times 

        @param max_unigram Ignore words that appear more than this many times

        @param min_unigram Ignore words that appear fewer than this many times

        @param exclude Don't add words from this set to bigrams
    
        """
        self._exclude = set(exclude)

        self._max_unigram = max_unigram
        self._min_unigram = min_unigram
        self._min_ngram = min_ngram

        self._vocab = None

        # You may want to add additional data structures here.

        self._unigram = Counter()
        self._bigram = Counter()
        self._ugTotal = 0
        self._bgTotal = 0

    def observed_and_expected(self, bigram):
        """
        Compute the observed and expected counts for a bigram

        @bigram A tuple containing the words to score
        """

        obs = zeros((2, 2))
        obs[0][0] = self._bigram[bigram]
        obs[0][1] = self._unigram[bigram[1],'r'] - self._bigram[bigram]
        obs[1][0] = self._unigram[bigram[0],'l'] - self._bigram[bigram]
        obs[1][1] = self._bgTotal - self._unigram[bigram[0],'l'] - self._unigram[bigram[1],'r'] + self._bigram[bigram]

        ex = zeros((2, 2))
        '''
        ex[0][0] = (obs[0][0]+obs[0][1])*(obs[0][0]+obs[1][0])/self._bgTotal
        ex[0][1] = (obs[0][0]+obs[0][1])*(obs[1][1]+obs[1][0])/self._bgTotal
        ex[1][0] = (obs[0][0]+obs[1][0])*(obs[1][1]+obs[1][0])/self._bgTotal
        ex[1][1] = (obs[1][1]+obs[0][1])*(obs[1][1]+obs[1][0])/self._bgTotal
        '''
        ex[0][0] = self._unigram[bigram[0],'l']*self._unigram[bigram[1],'r']/self._bgTotal
        ex[0][1] = (self._bgTotal - self._unigram[bigram[0],'l'])*self._unigram[bigram[1],'r']/self._bgTotal
        ex[1][0] = self._unigram[bigram[0],'l']*(self._bgTotal - self._unigram[bigram[1],'r'])/self._bgTotal
        ex[1][1] = (self._bgTotal-self._unigram[bigram[0],'l'])*(self._bgTotal - self._unigram[bigram[1],'r'])/self._bgTotal

        return obs, ex
        
    def score(self, bigram):
        """
        Compute the chi-square probability of a bigram being dependent.
        If either word of a bigram is in the "exclude" list, return 1.0.

        @bigram A tuple containing the words to score
        """

        # you shouldn't need to edit this function
        if any(x in self._exclude for x in bigram):
            return 1.0

        obs, ex = self.observed_and_expected(bigram)
                
        return chisquare_pvalue(obs, ex)

    def vocab_scan(self, sentence):
        """
        Given a sentence, scan all of its words and add up their counts.
        This will be used to finalize the vocabulary later.
        """

        # Don't modify this function.        
        for ii in sentence:
            self._unigram[ii] += 1

    def vocab(self):
        """
        Return the finder's vocab
        """

        # Don't modify this function.        
        return self._vocab

    def finalize(self):
        """
        Creates the vocabulary of for later processing.  Filters low frequency
        and high frequency words.
        """

        # Don't modify this function.
        self._vocab = set(x for x in self._unigram if self._unigram
                          if self._unigram[x] >= self._min_unigram and
                          self._unigram[x] <= self._max_unigram and
                          x not in self._exclude)
    
    def add_sentence(self, sentence):
        """
        Add the counts for a sentence (assumed to be iterable) so that we can
        then score bigrams.
        """
        assert self._vocab is not None, "Adding counts before finalizing vocabulary"
        
        # Your code here
        for ll, rr in bigrams(sentence):
            # Your code here
            self._bigram.update({(ll,rr)})
            self._unigram.update([(ll,'l'),(rr,'r')])
            self._bgTotal += 1
        self.vocab_scan(sentence)
        self._ugTotal += len(sentence)


    def valid_bigrams(self):
        """
        Return an iterator over the bigrams that have been seen enough to get a
        score.
        """
        
        # Your code here
        valid = []
        for i,j in self._bigram.items():
            if(j >= self._min_ngram):
                if(self._unigram[i[0]] > self._min_unigram and self._unigram[i[0]] < self._max_unigram):
                    if(self._unigram[i[1]] > self._min_unigram and self._unigram[i[1]] < self._max_unigram):
                        if(i[0] not in self._exclude and i[1] not in self._exclude):
                            #valid.append((i,j))
                            valid.append(i)
        return valid
        
    def sorted_bigrams(self):
        """
        Return n-grams sorted by the probability of being an n-gram.  Should
        yield a tuple of words in bigram and the p-value of the bigram.
        """
        
        # You should not need to modify this function
        
        d = {}
        for ngram in self.valid_bigrams():
            d[ngram] = self.score(ngram)

        for ngram, score in sorted(d.items(), key=operator.itemgetter(1), reverse=True):
            yield ngram, score

if __name__ == "__main__":
    bf = BigramFinder(exclude=kSTOPWORDS)
    
    for sent in sentences_from_zipfile("../data/state_union.zip"):
        bf.vocab_scan(tokenize(sent))

    bf.finalize()
    
    for sent in sentences_from_zipfile("../data/state_union.zip"):
        bf.add_sentence(tokenize(sent))
                
    for ngram, score in list(bf.sorted_bigrams())[:100]:
        print("%f\t%s\t%s\t" % (score, ngram[0], ngram[1]))
