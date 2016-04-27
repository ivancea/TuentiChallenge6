import sys

def calcZeros(n):
	count = 0
	while(True):
		while n%10==0:
			count += 1
			n /= 10
		if n%2 == 1 and n%5 == 1:
			break;
		if n%2 == 0:
			n *= 5
		else:
			n *= 2
		sys.stderr.write(str(n) + "\n")
	return count

c = int(input())
for cc in range(1, c+1):
	n = int(input())
	zeros = calcZeros(n)
	ones = 1
	while True:
		s = '1'*ones + '0'*zeros
		if(int(s)%n == 0):
			sys.stderr.write("Case #" + str(cc) + ": " + str(ones) + " " + str(zeros) + "\n")
			print("Case #" + str(cc) + ": " + str(ones) + " " + str(zeros))
			ended = True
			break
		ones += 1
