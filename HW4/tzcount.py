import sys
import re
input = []
dates = []


for line in sys.stdin:
	input.append(line.rstrip())
	
output=[ line for line in input if re.search(r'^Date', line)]

for word in output:
	date=word.split()
	date = date[-1]
	dates.append(date)


output2 = [[x,dates.count(x)] for x in set(dates)]
	
output2 = sorted(output2)

 
for line in output2:
	if line[0][0] == '-':
		print(*line, sep =" ")
	
for line in output2:
	if line[0][0] == '+':
		print(*line, sep =" ")