import random
import argparse

from numpy import zeros, sign, argsort
from math import exp, log, pow
from collections import defaultdict
import matplotlib.pyplot as plt


kSEED = 1735
kBIAS = "BIAS_CONSTANT"

random.seed(kSEED)


def sigmoid(score, threshold=20.0):
    """
    Prevent overflow of exp by capping activation at 20.

    :param score: A real valued number to convert into a number between 0 and 1
    """

    if abs(score) > threshold:
        score = threshold * sign(score)

    return 1.0 / (1.0 + exp(-score))


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
    def __init__(self, num_features, lam, eta=lambda x: 0.1):
        """
        Create a logistic regression classifier

        :param num_features: The number of features (including bias)
        :param lam: Regularization parameter
        :param eta: A function that takes the iteration as an argument (the default is a constant value)
        """
        
        self.w = zeros(num_features)
        self.num_features = num_features
        self.lam = lam
        self.eta = eta(1)
        self.last_update = defaultdict(int)

        assert self.lam>= 0, "Regularization parameter must be non-negative"

    def progress(self, examples):
        """
        Given a set of examples, compute the probability and accuracy

        :param examples: The dataset to score
        :return: A tuple of (log probability, accuracy)
        """

        logprob = 0.0
        num_right = 0
        for ex in examples:
            p = sigmoid(self.w.dot(ex.x))
            if ex.y == 1:
                logprob += log(p)
            else:
                logprob += log(1.0 - p)

            # Get accuracy
            if abs(ex.y - p) < 0.5:
                num_right += 1

        return logprob, float(num_right) / float(len(examples))

    def sg_update(self, train_example, iteration, use_tfidf=False):
        """
        Compute a stochastic gradient update to improve the log likelihood.

        :param train_example: The example to take the gradient with respect to
        :param iteration: The current iteration (an integer)
        :param use_tfidf: A boolean to switch between the raw data and the tfidf representation
        :return: Return the new value of the regression coefficients
        """
        
        # TODO: Implement updates in this function
        self.w += self.eta*(train_example.y - sigmoid(self.w.dot(train_example.x)))*train_example.x
        
        #Perform lazy sparse regularization
        for k in range(1,self.num_features):
            #Check for nonzero feature
            if(train_example.x[k] != 0):
                #Perform regularization for the kth feature
                self.w[k] *= pow(1 - 2*self.eta*self.lam,iteration - self.last_update.get(k, -1))
                #Set kth feature's update iteration
                self.last_update[k] = iteration
        return self.w


    def get_best_features(self, x, vocab):
        """
        Print the x best features for both classes
        """
        order = argsort(self.w)

        print("Positive")
        for i in range(1,x+1):
            if(self.w[order[-i]] <= 0):
                break
            print("\tFeature: %s, Score: %f" % (vocab[order[-i]], self.w[order[-i]]))
        
        print("\nNegative")
        for i in range(x):
            if(self.w[order[i]] >= 0):
                break
            print("\tFeature: %s, Score: %f" % (vocab[order[i]], self.w[order[i]]))

    def get_worst_features(self, x, vocab):
        """
        Print the x worst features for predicting the class
        """

        order = argsort([abs(i) for i in self.w])

        print("Poorest predictors")
        for i in range(x):
            print("\tFeature: %s, Score: %f" % (vocab[order[i]], self.w[order[i]]))



def eta_schedule(iteration):
    # TODO (extra credit): Update this function to provide an
    # EFFECTIVE iteration dependent learning rate size.  
    return 1.0 

def read_dataset(positive, negative, vocab, test_proportion=0.1):
    """
    Reads in a text dataset with a given vocabulary

    :param positive: Positive examples
    :param negative: Negative examples
    :param vocab: A list of vocabulary words
    :param test_proprotion: How much of the data should be reserved for test
    """

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

    # Shuffle the data 
    random.shuffle(train)
    random.shuffle(test)

    return train, test, vocab



if __name__ == "__main__":
    argparser = argparse.ArgumentParser()
    argparser.add_argument("--lam", help="Weight of L2 regression",
                           type=float, default=0.0, required=False)
    argparser.add_argument("--eta", help="Initial SG learning rate",
                           type=float, default=0.1, required=False)
    argparser.add_argument("--positive", help="Positive class",
                           type=str, default="../data/autos_motorcycles/positive", required=False)
    argparser.add_argument("--negative", help="Negative class",
                           type=str, default="../data/autos_motorcycles/negative", required=False)
    argparser.add_argument("--vocab", help="Vocabulary that can be features",
                           type=str, default="../data/autos_motorcycles/vocab", required=False)
    argparser.add_argument("--passes", help="Number of passes through train",
                           type=int, default=1, required=False)
    argparser.add_argument("--output", help="Name of plot output file", type=str, default="output.png", required=False)

    args = argparser.parse_args()
    train, test, vocab = read_dataset(args.positive, args.negative, args.vocab)

    print("Read in %i train and %i test" % (len(train), len(test)))

    # Initialize model
    lr = LogReg(len(vocab), args.lam, lambda x: args.eta)

    # Iterations
    iteration = 0
    training_accuracy = []
    holdout_accuracy = []
    for pp in xrange(args.passes):
        random.shuffle(train)
        for ex in train:
            lr.sg_update(ex, iteration)
            if iteration % 5 == 1:
                train_lp, train_acc = lr.progress(train)
                ho_lp, ho_acc = lr.progress(test)
                print("Update %i\tTP %f\tHP %f\tTA %f\tHA %f" %
                      (iteration, train_lp, ho_lp, train_acc, ho_acc))
                training_accuracy.append(train_acc)
                holdout_accuracy.append(ho_acc)
            iteration += 1
    lr.get_best_features(5,vocab)
    lr.get_worst_features(5,vocab)
    
    # Create figure
    plt.figure()
    plt.title("Model Accuracy (%s)" % (args.output,))
    plt.xlabel("Iterations % 5")
    plt.ylabel("Accuracy")
    plt.plot(training_accuracy, label="Training Accuracy")
    plt.plot(holdout_accuracy, label="Holdout Accuracy")
    plt.legend()
    #plt.show()
    plt.savefig(args.output, format="png")
