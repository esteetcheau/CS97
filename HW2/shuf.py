#!/usr/bin/python3                                                              
import argparse
import string
import random
import sys


def inputRange(input_range, numlines, repeat): #if -i used
	input_range = input_range.split('-') #splits range into two values
	min = int(input_range[0])
	max = int(input_range[1]) + 1

	listNums = []
	for i in range(min, max):
		listNums.append(str(i)) #adds all numbers in range to list
		
	if repeat == False: #if -r not used
		if numlines == 0: #if -n not used, default -n to length of list
			numlines = len(listNums)
		#print numlines items from list in random order				
		print(random.sample(listNums, numlines)) #if -n used but -r not used
			
	while repeat == True: #-r used
		if numlines != 0: #-n used
		#prints numlines times from list randomly with repeats
			print(random.choices(listNums, k = numlines)) 
			repeat = False #causes while loop to end
		else: #-n not used
			print(random.choice(listNums)) #infinte loop of random printing
				
def inputEcho(echo, numlines, repeat): #if -e used
		listWords = []
		for words in echo: #creates list with all values to be shuffled
			listWords.append(words)
				
		if repeat == False: #if -r not used
			if numlines == 0: #if -n not used, default -n to length of list
				numlines = len(listWords)
			#print numlines items from list in random order								
			print(random.sample(listWords, numlines))
		
		while repeat == True:#-r used
			if numlines != 0: #-n used
				#prints numlines times from list randomly with repeats
				print(random.choices(listWords, k = numlines))
				repeat = False #causes while loop to end
			else: #-n not used
				print(random.choice(listWords)) #infinte loop of random printing

def shufFile(infile, numlines, repeat): #if inputfile given
        listLines = []
        for line in infile: #creates list with all values to be shuffled
                lines= line.strip() #strips lines
                listLines.append(lines)
                
        if repeat == False: #if -r not used
        	if numlines == 0: #if -n not used, default -n to length of list
        		numlines = len(listLines)
        	#print numlines items from list in random order								
        	print(random.sample(listLines, numlines)) #-r not used, -n not used
        	
        while repeat == True: #-r used
        	if numlines != 0: #-n used
        	#prints numlines times from list randomly with repeats
        		print(random.choices(listLines, k = numlines))
        		repeat = False #causes while loop to end
        	else: #-n not used
        		print(random.choice(listLines)) #infinte loop of random printing

def main():

        repeat = False #default -r not used
        numlines = 0 #default -n not used
        parser = argparse.ArgumentParser()
        
        if '-n' in sys.argv or '--numlines' in sys.argv:
        	parser.add_argument("-n", "--numlines",
        		action="store", dest="numlines", default=0,
        		help="output NUMLINES lines (default 1)")
        	
        	
        	if '-n' in sys.argv:
        		numlines = int(sys.argv[sys.argv.index('-n')+1]) #store value
        		del sys.argv[sys.argv.index('-n')+1] #delete from index
        		del sys.argv[sys.argv.index('-n')]
        	else:  #account for -n and --numlines
        		numlines = int(sys.argv[sys.argv.index('--numlines')+1]) #store value
        		del sys.argv[sys.argv.index('--numlines')+1] #delete from index
        		del sys.argv[sys.argv.index('--numlines')]
        	
        if '-r' in sys.argv or '--repeat' in sys.argv:
        	repeat = True
        	if '-r' in sys.argv:
        		del sys.argv[sys.argv.index('-r')] #delete from index
        	else: #account for -r and --repeat
        		del sys.argv[sys.argv.index('--repeat')]

       #3 unique cases that cannot be combined with one another (-i, -e, infile)
 
        if '-i' in sys.argv or '--input-range' in sys.argv:
        	parser.add_argument("-i", "--input-range",
        		action="store", dest="input_range",
        		help="each number in range is an input line")

        	args = parser.parse_args()
       		input_range = args.input_range
       		
       		#call inputRange function
       		inputRange(input_range, numlines, repeat)
       		
       	elif '-e' in sys.argv or '--echo' in sys.argv:
       		parser.add_argument("-e", "--echo",
                            	dest="echo", nargs='+',
                          	help="each argument is an input line")

        	args = parser.parse_args()
        	echo = args.echo
        	
        	#call inputEcho function
        	inputEcho(echo, numlines, repeat)
        	
        else:
        	parser.add_argument('infile', type=argparse.FileType('r'))

        	args = parser.parse_args()
        	infile = args.infile
        	
        	#call shufFile function
        	shufFile(infile, numlines, repeat)


if __name__ == '__main__':
        main()
	
	
	
	
	
	
