import operator
import re
import datetime
import sys

filename = input("Please enter the name/path of a script... \n")
#filename = input()
try:
	f = open(filename,'r')
except OSError:
	print("No file of the given path/name exists. The script will exit now.")
	sys.exit()

characters=dict()
rem_chars={'(', ')', ':'}
rem_strs=['the end', 'hello', 'them', 'continuous', 'yesterday', 'today', 'tomorrow', 'cut to', 'dissolve to', 'morning', 'night', 'omitted']
def is_match(s):
	for i in rem_strs:
		if (s.casefold().find(i) != -1):
			return False
	else:
		return True

#for dealing with Mr. Mrs. Dr. in name
def check(s):
	if (s[0:4] == 'Mr. ') or (s[0:4] == 'Dr. '):
		return s[4:]
	elif (s[0:5] == 'Mrs. '):
		return s[5:]
	else:
		return s

var_file=f.readlines()

for line in var_file:
	if (line.expandtabs()[0:20].isspace()) and (line.isupper()) and ((set(line) & rem_chars) == set()) and (line[-2] != '-'):
		var1=check(line[0:-1].strip())
		if var1.casefold() not in characters.keys():
			characters[var1.casefold()]=1
		else:
			characters[var1.casefold()]+=1

#removing special strings which are not characters
for key in list(characters):
	if (key in rem_strs) and (characters[key] <= 2) or re.match(r'^[0-9]', key):
		del characters[key]

for key in characters:
	characters[key] = 0

for line in var_file:
	for key in characters:
		characters[key.casefold()]+=line.casefold().count(key.casefold())

print("The characters of the movie and number of their occurrences are as follows:")
for i in sorted(characters.keys()):
	print(i.capitalize(),'	', characters[i])

#print(characters)
f.close()
