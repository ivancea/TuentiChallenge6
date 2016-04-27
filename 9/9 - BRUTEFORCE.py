import sys

c = int(input())
for cc in range(1, c+1):
	n = int(input())
	ended = False
	m = 1
	while True:
		for i in range(max(m-len(str(n))-1,1),m+1):
			s = '1'*i + '0'*(m-i)
			if(int(s)%n == 0):
				sys.stderr.write("Case #" + str(cc) + ": " + str(i) + " " + str(m-i) + "\n")
				print("Case #" + str(cc) + ": " + str(i) + " " + str(m-i))
				ended = True
				break
		if ended:
			break
		m += 1
	if ended==False:
		sys.stderr.write("Case #" + str(cc) + ": ERROR\n")
		print("Case #" + str(cc) + ": ERROR")
