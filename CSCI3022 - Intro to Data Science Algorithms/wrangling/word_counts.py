from collections import Counter
from zipfile import ZipFile

def text_from_zipfile(zip_file):
    """
    Given a zip file, yield an iterator over the text in each file in the
    zip file.
    """
    # Modify this function
    #return ["nope"]
    with ZipFile(zip_file) as zf:
        for x in zf.namelist():
            with zf.open(x) as currentFile:
                for line in currentFile:
#                    print(line)
                    yield str(line, "utf-8", errors="ignore")

def words(text):
    """
    Return all words in a string, where a word is four or more contiguous
    characters in the range a-z or A-Z.  The resulting words should be
    lower case.
    """
    # Modify this function
    '''
    for word in re.split("[^a-z]", text.lower()):
        if len(word) >= 4:
            yield word'''
    return re.findall(kWORDS, text.lower())
#    return text.lower().split()

def accumulate_counts(words, total=Counter()):
    """
    Take an iterator over words, add the sum to the total, and return the
    total.

    @words An iterable object that contains the words in a document
    @total The total counter we should add the counts to
    """
    assert isinstance(total, Counter)

    # Modify this function    
    for word in words:
        total[word] += 1
    return total

if __name__ == "__main__":
    # You should not need to modify this part of the code
    total = Counter()
    for tt in text_from_zipfile("../data/state_union.zip"):
        total = accumulate_counts(words(tt), total)

    for ii, cc in total.most_common(100):
        print("%s\t%i" % (ii, cc))
