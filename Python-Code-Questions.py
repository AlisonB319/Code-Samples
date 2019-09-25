from functools import reduce
from collections import Counter
import inspect
import math
# Alison Burgess
# CPTS 355 HW 3
# 3/12/18

# 1(a)
# This function takes a dictionary of dictionary and adds together the vales
# based on the common keys
def addDict(d):
    d2 = {}
    if d == {}:
        return 0
    for outKey, inKey in d.items():
        for inVal in inKey:
            if inVal in d2:
                d2[inVal] += inKey[inVal]
            else:
                d2[inVal] = inKey[inVal]
    return d2

def testaddDict():
    test1 = {'family1': {'dogs': 2, 'cats': 3, 'fish': 1},
            'family2': {'dogs': 3, 'cats': 2}}
    test2 = {'Mon': {'355': 0, '451': 0, '360': 0}, 'Tue': {'451': 1, '360': 10},
            'Thu': {'355': 0, '451': 0, '360': 0}, 'Fri': {'355': 2},
            'Sun': {'355': 2, '451': 4, '360': 2}}
    test3 = {'Mon': {'355': 0, '451': 0, '360': 0}, 'Tue': {'451': 0, '360': 0},
            'Wed': {}}
    if addDict(test1) != {'dogs': 5, 'cats': 5, 'fish': 1}:
        return False
    if addDict(test2) != {'355': 4, '451': 5, '360': 12}:
        return False
    if addDict(test3) != {'355': 0, '451': 0, '360': 0}:
        return False
    return True

# 1(b)
# This function takes a list of dictionaries and add together the values based
# on common keys
def addDictN(L):
    if L == []:
        return 0
    if L == [{}]:
        return 0
    d2 = list(map(addDict, L))
    z = reduce(lambda x, y: x + Counter(y), d2, Counter())
    z = dict(z)
    return z

def testaddDictN():
    test1 = [{'Mon': {'355': 4, '360': 5}, 'Tue': {'451': 2, '360': 3}, 'Thu': {'360': 0},
              'Fri': {'355': 2}, 'Sun': {'355': 1}},
            {'Tue': {'360': 2}, 'Wed': {'355': 2}, 'Fri': {'360': 3, '355': 1}},
            {'Mon': {'360': 6}, 'Wed': {'451': 3}, 'Thu': {'355': 0}, 'Fri': {'360': 6},
             'Sun': {'355': 1}}]
    test2 = [{'f1': {'dogs': 2, 'cats': 3, 'fish': 1},
              'f2': {'dogs': 3, 'cats': 2}},
            {'f1': {'dogs': 5, 'cats': 2, 'fish': 3}}]
    test3 = [{'f1': {'dogs': 1, 'cats': 0, 'fish': 1},
              'f2': {'dogs': 0, 'cats': 1}}]
    if addDictN(test1) != {'355': 11, '360': 25, '451': 5}:
        return False
    if addDictN(test2) != {'dogs': 10, 'cats': 7, 'fish': 4}:
        return False
    if addDictN(test3) != {'dogs': 1, 'cats': 1, 'fish': 1}:
        return False
    return True

# 2(a)
def secondNum(num):
    return num[1]

def firstNum(num):
    return num[0]

#This function sorts the lists so they are in the correct order
def sort(blank):
    finalL = []
    for i in range(len(blank) + 1):
        newL = []
        for k, v in blank:
            if v == i:
                newL += [(k, v)]
        if newL != []:
            # sorts the new sub lists so they can be appended correctly
            sortedL = sorted(newL, key=firstNum)
            for k, v in sortedL:
                finalL += [(k, v)]
    return finalL
# Takes an inputted string and counts how many time each character occurs
def charCount(s):
    c_dict = dict()
    for c in s:
        if c is ' ':
            pass
        elif c_dict.get(c) is not None:
            c_dict[c] += 1
        else:
            c_dict.update({c: 1})
    tup = c_dict.items()
    # the sorting begins
    blank = sorted(tup, key=secondNum)
    finalL = sort(blank)
    return finalL

def testcharCount():
    if charCount("zzzz qqqq ggg aaa bb cc") != [('b', 2), ('c', 2), ('a', 3), ('g', 3), ('q', 4), ('z', 4)]:
        return False
    if charCount("hopefully passing 355") != [('3', 1), ('a', 1), ('e', 1), ('f', 1), ('g', 1), ('h', 1), ('i', 1), ('n', 1), ('o', 1), ('u', 1), ('y', 1), ('5', 2), ('l', 2), ('p', 2), ('s', 2)]:
        return False
    if charCount("") != []:
        return False
    return True

# 2b
# takes an inputted string and counts how many times each character occurs using
# .count to count how many times each character occurs
def charCount2(s):
    tup = [(c, s.count(c)) for c in s if c is not ' ']
    blank = sorted(list(set(tup)), key=secondNum)
    #sorting begins
    finalL = sort(blank)
    return finalL

def testcharCount2():
    if charCount2("zzzz qqqq ggg aaa bb cc") != [('b', 2), ('c', 2), ('a', 3), ('g', 3), ('q', 4), ('z', 4)]:
        return False
    if charCount2("hopefully passing 355") != [('3', 1), ('a', 1), ('e', 1), ('f', 1), ('g', 1), ('h', 1), ('i', 1), ('n', 1), ('o', 1), ('u', 1), ('y', 1), ('5', 2), ('l', 2), ('p', 2), ('s', 2)]:
        return False
    if charCount2("") != []:
        return False
    return True

# 3a
# Takes a list of dictionaries and a look up value and determines if the key is in
# any of the dictionaries
def lookupVal(L, k):
    num = 0
    item = 0
    found = False
    if L == [{}]:
        return None
    for i in range(len(L)):
        if k in L[i]:
            item = k
            num = i
            found = True
    if found:
        return L[num][item]
    else:
        return None

def testlookupVal():
    test1 = [{"a": 9, "b": True, "q": "lost"}, {"x": 1}, {"y": False}]
    test2 = [{}]
    test3 = [{"a": False, "b": True, "c": "lost"}, {"d": 1}, {"e": False}]
    if lookupVal(test1, "q") != 'lost':
        return False
    if lookupVal(test2, 2) != None:
        return False
    if lookupVal(test3, "a") != False:
        return False
    return True

# 3b
# Takes a list of tuples and a key and determines if the key is in any of the tuples
def lookupVal2(tL, k):
    if len(tL) <= 0:
        return None
    size = len(tL)
    n = tL[size - 1][0]
    d = tL[size - 1][1]
    index = n + 1 - size
    for key, val in d.items():
        if key == k:
            return val
    return lookupVal2(tL[:index], k)

def testlookupVal2():
    test1 = [(0, {"x": 3, "y": False, "z": "zero"}),
          (0, {"x": 1}),
          (1, {"y": False}),
          (1, {"w": 3, "z": "seven"}),
          (2, {})]
    if lookupVal2(test1, "y") != False:
        return False
    if lookupVal2(test1, "z") != "zero":
        return False
    if lookupVal2(test1, "w") != None:
        return False
    return True

# 4
# This function takes a dictionary with keys and anonymous function and processes
# accordingly
def funRun(d, name, args):
    if d.get(name) is not None:
        if len(inspect.getfullargspec(d[name]).args) is not len(args):
            print("The argument list given doesn't march the arguments of the list")
            return
        else:
            return d[name](*args)
    else:
        print("this function name cannot be found in the given dictionary")
        return

def testfunRun():
    test1 = {"subtract": lambda x, y: (x - y), "multiply": lambda a, b: (a * b),
             "mod3": lambda n: (n%3)}
    if funRun(test1, "subtract", [10,1]) != 9:
        return False
    if funRun(test1, "multiply", [3,9]) != 27:
        return False
    if funRun(test1, "mod3", [36]) != 0:
        return False
    return True

# 5
#calcualtes how many paths possible in a grid from the top left to the bottom right
def numPaths(m, n):
    if m == 0 or n == 0:
        return 0
    count = [[0 for x in range(m)] for y in range(n)]
    for i in range(m):
        count[i][0] = 1
    for j in range(n):
        count[0][j] = 1
    for i in range(1, m):
        for j in range(n):
            count[i][j] = count[i - 1][j] + count[i][j - 1]
    return count[m - 1][n - 1]

def testnumPaths():
    if numPaths(4,4) != 20:
        return False
    if numPaths(1,1) != 1:
        return False
    if numPaths(0,0) != 0:
        return False
    return True

# 6(a)
# An iterator that produces endless square values
class iterSquares():
    def __init__(self):
        self.num = 1
    def __next__(self):
        num = self.num * self.num
        self.num += 1
        return num

# 6(b)
# This function uses the square iterator and stores the values into a list until
# the sum of the list is x - 1 away from equaling more than the given value
def numbersToSum(iNumbers, summ):
    if iNumbers.num == 1:
        prev, current = iNumbers.__next__(), iNumbers.__next__()
    else:
        #need to reset iNumbers so that the iteration does not skip numbers
        prev, current = (iNumbers.num - 3) * (iNumbers.num -3), (iNumbers.num - 2) * (iNumbers.num - 2)
        iNumbers.num = iNumbers.num - 1
    myL = []
    while sum(myL) < summ:
        myL.append(prev)
        prev, current = current, iNumbers.__next__()
    del myL[-1]
    return myL

def testnumbersToSum():
    sq= iterSquares()
    if numbersToSum(sq, 100) != [1, 4, 9, 16, 25, 36]:
        return False
    if numbersToSum(sq, 200) != [49,64,81]:
        return False
    sq = iterSquares()
    if numbersToSum(sq ,200) != [1, 4, 9, 16, 25, 36, 49]:
        return False
    return True

# 7a
class Stream(object):
    def __init__(self, first, compute_rest, empty=False):
        self.first = first
        self._compute_rest = compute_rest
        self.empty = empty
        self._rest = None
        self._computed = False
    @property
    def rest(self):
        assert not self.empty, 'Empty streams have no rest.'
        if not self._computed:
            self._rest = self._compute_rest()
        self._computed = True
        return self._rest

empty_stream = Stream(None, None, True)
# This function uses the stream to produce endless square values
def streamSquares(k):
    def compute_rest():
        return streamSquares(((k+1)*(k+1)))
    k = math.sqrt(k)
    k = int(k)
    return Stream((k*k), compute_rest)

# 7b
# The function takes a stream and returns only the even results
def evenStream(stream):
    def compute_rest1():
        return evenStream(stream.rest)
    def compute_rest2():
        return evenStream(stream.rest.rest)
    if stream.first % 2 == 0:
        return Stream(stream.first, compute_rest1)
    else:
        return Stream(stream.rest.first, compute_rest2)

def runTest(s, x):
    test1 = evenStream(streamSquares(s))
    myLi = []
    while test1.first < x:
        myLi.append(test1.first)
        test1 = test1.rest
    return myLi

def testevenStream():
    test1 = runTest(36, 200)
    test2 = runTest(9, 257)
    test3 = runTest(0,0)

    if test1 != [36, 64, 100, 144, 196]:
        return False
    if test2 != [16, 36, 64, 100, 144, 196, 256]:
        return False
    if test3 != []:
        return False
    return True

if __name__ == '__main__':
    passedMsg = "%s passed"
    failedMsg = "%s failed"
    if testaddDict():
        print( passedMsg % 'addDict')
    else:
        print( failedMsg % 'addDict')
    if testaddDictN():
        print( passedMsg % 'addDictN')
    else:
        print( failedMsg % 'addDictN')
    if testcharCount():
        print( passedMsg % 'charCount')
    else:
        print( failedMsg % 'charCount')
    if testcharCount2():
        print( passedMsg % 'charCount2')
    else:
        print( failedMsg % 'charCount2')
    if testlookupVal():
        print( passedMsg % 'lookupVal')
    else:
        print( failedMsg % 'lookupVal')
    if testlookupVal2():
        print( passedMsg % 'lookupVal2')
    else:
        print( failedMsg % 'lookupVal2')
    if testfunRun():
        print( passedMsg % 'funRun')
    else:
        print( failedMsg % 'funRun')
    if testnumPaths():
        print( passedMsg % 'numPaths')
    else:
        print( failedMsg % 'numPaths')
    if testnumbersToSum():
        print( passedMsg % 'numbersToSum')
    else:
        print( failedMsg % 'numbersToSum')
    if testevenStream():
        print( passedMsg % 'evenStream')
    else:
        print( failedMsg % 'evenStream')












