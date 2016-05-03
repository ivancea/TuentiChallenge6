import sys
from fractions import Fraction


def calc(probs, initial, changes):
	v = [Fraction(0)]*len(probs)
	v[initial] = Fraction(1)
	for cc in range(0,changes):
		t = [Fraction(0)]*len(probs)
		for i in range(0,len(v)):
			if v[i].numerator > 0:
				for seat, prob in probs[i].items():
					t[seat] += v[i]*prob
		v = t
	return v


seats = int(input())
probNumber = int(input())

probs = [0]*seats
for i in range(0,seats):
	probs[i] = {}

for i in range(0,probNumber):
	t = input().split(' ')
	probs[int(t[0])][int(t[1])] = Fraction(t[2])

q = int(input())
for qq in range(1,q+1):
	readArray = input().split(' ')
	initial = int(readArray[0])
	changes = int(readArray[1])
	sys.stderr.write("Case #"+str(qq)+": "+readArray[0]+" - "+readArray[1]+"\n")
	t = calc(probs, initial, changes)
	maxIndex = -1
	max = Fraction("-1/100")
	for i in range(len(t)-1, -1, -1):
		if t[i] > max:
			max = t[i]
			maxIndex = i
	print("Case #" + str(qq) + ": Chair: " + str(maxIndex) + " Last digits: " + str(t[maxIndex].numerator%10) + "/" + str(t[maxIndex].denominator%10))
