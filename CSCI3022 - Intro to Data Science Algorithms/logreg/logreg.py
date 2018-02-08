import random
from numpy import zeros, sign, argsort
from math import exp, log
from collections import defaultdict

import argparse

kSEED = 1701
kBIAS = "BIAS_CONSTANT"

random.seed(kSEED)


def sigmoid(score, threshold=20.0):
    """
    Note: Prevents overflow of exp by capping activation at 20.

    :param score: A real valued number to convert into a number between 0 and 1
    """

    if abs(score) > threshold:
        score = threshold * sign(score)

    activation = exp(score)
    return activation / (1.0 + activation)


class Example:
    """
    Class to represent a logistic regression example
    """
    def __init__(self, label, words, vocab, df):
        """
        Create a new example

        :param label: The label (0 / 1) of the example
        :param words: The words in a list of "word:count" format
        :param vocab: The vocabulary to use as features (list)
        """
        self.nonzero = {}
        self.y = label
        self.x = zeros(len(vocab))
        for word, count in [x.split(":") for x in words]:
            if word in vocab:
                assert word != kBIAS, "Bias can't actually appear in document"
                self.x[vocab.index(word)] += float(count)
                self.nonzero[vocab.index(word)] = word
        self.x[0] = 1


class LogReg:
    def __init__(self, num_features, learning_rate=0.05):
        """
        Create a logistic regression classifier

        :param num_features: The number of features (including bias)
        :param learning_rate: How big of a SG step we take
        """

        self.beta = zeros(num_features)
        self.learning_rate = learning_rate

    def progress(self, examples):
        """
        Given a set of examples, compute the probability and accuracy

        :param examples: The dataset to score
        :return: A tuple of (log probability, accuracy)
        """

        logprob = 0.0
        num_right = 0
        for ii in examples:
            p = sigmoid(self.beta.dot(ii.x))
            if ii.y == 1:
                logprob += log(p)
            else:
                logprob += log(1.0 - p)

            # Get accuracy
            if abs(ii.y - p) < 0.5:
                num_right += 1

        return logprob, float(num_right) / float(len(examples))

    def sg_update(self, train_example):
        """
        Compute a stochastic gradient update to improve the log likelihood.

        :param train_example: The example to take the gradient with respect to
        :return: The current vector of parameters
        """

        # Your code here
        #Update is beta_i plus step-size (learning_rate) times the slope of the likelyhood given beta with respect to beta_i
        #print("%s, %d" % (train_example.x,train_example.y))
        expBeta = exp(self.beta.dot(train_example.x))
        pi_i = expBeta/(1+expBeta)
        for ii in range(0,len(self.beta)):
            #Update beta_i by stepping
            self.beta[ii] += self.learning_rate*(train_example.y-pi_i)*train_example.x[ii]

        return self.beta

    def printweights(self):
        "Return beta"
        return self.beta


def read_dataset(positive, negative, vocab, test_proportion=.1):
    """
    Reads in a text dataset with a given vocabulary

    :param positive: Positive examples
    :param negative: Negative examples
    :param vocab: A list of vocabulary words
    :param test_proprotion: How much of the data should be reserved for test
    """

    # You should not need to modify this function
    
    df = [float(x.split("\t")[1]) for x in open(vocab, 'r') if '\t' in x]
    vocab = [x.split("\t")[0] for x in open(vocab, 'r') if '\t' in x]
    assert vocab[0] == kBIAS, \
        "First vocab word must be bias term (was %s)" % vocab[0]

    train = []
    test = []
    for label, input in [(1, positive), (0, negative)]:
        for line in open(input):
            ex = Example(label, line.split(), vocab, df)
            if random.random() <= test_proportion:
                test.append(ex)
            else:
                train.append(ex)

    # Shuffle the data so that we don't have order effects
    random.shuffle(train)
    random.shuffle(test)

    return train, test, vocab

if __name__ == "__main__":
    argparser = argparse.ArgumentParser()
    argparser.add_argument("--step", help="Initial SG step size",
                           type=float, default=0.1, required=False)
    argparser.add_argument("--positive", help="Positive class",
                           type=str, default="positive", required=False)
    argparser.add_argument("--negative", help="Negative class",
                           type=str, default="negative", required=False)
    argparser.add_argument("--vocab", help="Vocabulary that can be features",
                           type=str, default="vocab", required=False)
    argparser.add_argument("--passes", help="Number of passes through train",
                           type=int, default=1, required=False)

    args = argparser.parse_args()
    train, test, vocab = read_dataset(args.positive, args.negative, args.vocab)

    print("Read in %i train and %i test" % (len(train), len(test)))

    # Initialize model
    lr = LogReg(len(vocab), args.step)

    # Iterations
    update_number = 0
    for pp in range(args.passes):
        for ii in train:
            update_number += 1
            lr.sg_update(ii)

            if update_number % 5 == 1:
                train_lp, train_acc = lr.progress(train)
                ho_lp, ho_acc = lr.progress(test)
                print("Update %i\tTP %f\tHP %f\tTA %f\tHA %f" %
                      (update_number, train_lp, ho_lp, train_acc, ho_acc))
    print("Updated %d times" % update_number)
    beta = lr.printweights()
    pairs = []
    #for i in range(0,len(vocab)):
    #    print("%s: %f" % (vocab[i], beta[i]))
    #    pairs.append((vocab[i],beta[i]))

    indexes = argsort(beta)
    print("\nGreatest")
    for i in indexes[:6]:
        print(vocab[i])
    print("\nLeast")
    for i in indexes[-6:]:
        print(vocab[i])
    print("\nMost neutral")
    for i in indexes[len(indexes)//2-3:len(indexes)//2+3]:
        print(vocab[i])
