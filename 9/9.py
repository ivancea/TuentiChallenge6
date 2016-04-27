import sys

def calcZeros(n):
	count = 0
	while(True):
		while n%10==0:
			count += 1
			n /= 10
		if n%2 != 0 and n%5 != 0:
			break;
		if n%2 == 0:
			n *= 5
		else:
			n *= 2
	return count

def reduce(n):
	while n%5==0:
		n /= 5
	while n%2==0:
		n /= 2
	return int(n)
	
def calcOnes(n):
	t = 1
	while True:
		if(t%n == 0):
			break
		t = t*10 + 1
	return len(str(t))

	
	
c = int(input())
for cc in range(1, c+1):
	n = int(input())
	zeros = calcZeros(n)
	n = reduce(n)
	ones = calcOnes(n)
	sys.stderr.write("Case #" + str(cc) + ": " + str(ones) + " " + str(zeros) + "\n")
	print("Case #" + str(cc) + ": " + str(ones) + " " + str(zeros))
