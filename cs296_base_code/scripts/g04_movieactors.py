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


#f = open('amour.txt','r')

characters=dict()
rem_chars={'(', ')', ':', '!'}
rem_strs=['the end', 'hello', 'them', 'continuous', 'yesterday', 'today', 'tomorrow', 'cut to', 'dissolve to', 'morning', 'night', 'problem', 'omitted']
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
	if ((key in rem_strs) and (characters[key] <= 2)) or re.match(r'^[0-9]', key):
		del characters[key]

for key in characters:
	characters[key] = 0

for line in var_file:
	for key in characters:
		characters[key.casefold()]+=line.casefold().count(key.casefold())

# s1 is from dictionary
def equal(s1, s2):
	regex = re.compile('%s[!,.?\']'%s1)
	if (s2[-2:] == "'s") and (s2[:-2] == s1):
		return True
	else:
		return regex.match(s2)

#for line in var_file:
#	for word in line.split():
#		for key in characters:
#			if equal(key, word):
#				characters[key]+=1
#for key1 in list(characters):
#	for key2 in list(characters):
#		if (key1 != key2) and (key1.find(key2) != -1):
#			#print(key1, key2)
#			del characters[key1]
#			break

#var1 =[(x,characters[x]) for x in sorted(characters.keys())]
#print (var1)


var_file_words=list()
for line in var_file:
	var_file_words += line.split()

gender = dict()
gender_count = dict()
to_be_found = list()
villian_count = dict()
for key in characters:
	gender[key] = 'Undetermined'
	to_be_found.append(key)

for line in var_file:
	for key in to_be_found:
		index = line.casefold().find(key)
		if (index != -1) and (index >= 4) and (line[(index-4):index] == 'Mr. '):
			gender[key] = 'Male'
			to_be_found.remove(key)
		if (index != -1) and (index >= 5) and (line[(index-5):index] == 'Mrs. ' or line[(index-5):index] == 'Miss '):
			gender[key] = 'Female'
			to_be_found.remove(key)
		if (index != -1) and (index >= 4) and (line[(index-4):index] == 'Ms. '):
			gender[key] = 'Female'
			to_be_found.remove(key)

for key in to_be_found:
	if (('female' in key) or ('woman' in key) or ('mother' in key) or ('sister' in key) or ('girl' in key) or ('lady' in key) or ('wife' in key)) and (gender[key] == 'Undetermined'):
		gender[key] = 'Female'
		to_be_found.remove(key)
		continue	
	elif (('male' in key) or ('man' in key) or ('father' in key) or ('brother' in key) or ('boy' in key) or ('husband' in key)) and (gender[key] == 'Undetermined'):
		gender[key] = 'Male'
		to_be_found.remove(key)
	
for e in characters:
	gender_count[e] = 0
	villian_count[e] = 0

male_words = ['he', 'his', 'him', 'he\'s']
female_words = ['she', 'her', 'her\'s', 'she\'s']
villian_words = ['kill', 'torture', 'beat', 'hit', 'torment', 'sadist', 'gun', 'hack saw', 'knife', 'jealous', 'anger', 'envy', 'revenge'
, 'evil', 'distress', 'filthy', 'fight', 'rude', 'mean', 'scare', 'fear', 'vile', 'evil', 'evil', 'kill', 'evil', 'evil', 'evil']
latest_key = -1
no_lines = 20
pres_line = -1

def determine_villian(key,index,line_count):
	for i in range(line_count):
		for villian_word in villian_words:
			villian_count[key] += var_file[index-i].casefold().count(villian_word)

def determine(key,index,line_count):
	for i in range(line_count):
		for word in var_file[index-i].casefold().split():
			#print('det')
			for he_word in male_words:
				if equal(he_word,word):
					gender_count[key]+=1
			for she_word in female_words:
				if equal(she_word,word):
					gender_count[key]-=1
			
#latest = -1
def dialog(index):
	for i in range(index,0,-1):
		line = var_file[i]
		if (line.expandtabs()[0:20].isspace()) and (line.isupper()):
			return line[0:-1].strip().casefold()

for i in range(len(var_file)):
	if var_file[i].isspace():
		continue
	line = var_file[i].casefold()
	for key in to_be_found:
		if(line.find(key) != -1 and dialog(i) != key):
			#latest = line.find(key)
			determine(latest_key,i,pres_line)
			latest_key = key
			pres_line = 0
	
	if(pres_line == no_lines):
		determine(latest_key,i,no_lines)	
		pres_line = -1
		latest_key = -1
	elif(pres_line != -1) and (pres_line < no_lines):
		pres_line+=1

for key in characters:
	if (gender[key] == 'Undetermined') and (gender_count[key] > 0):
		gender[key] = 'Male'
	if (gender[key] == 'Undetermined') and (gender_count[key] < 0):
		gender[key] = 'Female'
print("The characters names, the number of their occurrences and their genders are as follows:")
for i in sorted(characters.keys()):
	print(i.capitalize(),'	', characters[i],'	', gender[i])

max_male = ''
max_female = ''
count_male = -1
count_female = -1
for i in characters:
	if (gender[i]=='Male') and (characters[i] > count_male):
		max_male = i
		count_male = characters[i]
	if (gender[i]=='Female') and (characters[i] > count_female):
		max_female = i
		count_female = characters[i]
	

print()
if (count_female < 10):
	max_female = 'Sorry, no heroine'
if (count_male < 10):
	max_male = 'No hero'
print('The hero is', max_male.capitalize(),'\nThe heroine is', max_female.capitalize() )
#print(dialog(2334))
characters_sorted = sorted(characters.items(), key=lambda x: x[1])
#print(characters_sorted)


print('The protagonists are', characters_sorted[-1][0].capitalize(), ',', characters_sorted[-2][0].capitalize(), ',', characters_sorted[-3][0].capitalize()) 

latest_key = -1
no_lines = 20
pres_line = -1

for i in range(len(var_file)):
	if var_file[i].isspace():
		continue
	line = var_file[i].casefold()
	for key in to_be_found:
		if(line.find(key) != -1):
			#latest = line.find(key)
			determine_villian(latest_key,i,pres_line)
			latest_key = key
			pres_line = 0
	
	if(pres_line == no_lines):
		determine_villian(latest_key,i,no_lines)	
		pres_line = -1
		latest_key = -1
	elif(pres_line != -1) and (pres_line < no_lines):
		pres_line+=1

villian_sorted = sorted(villian_count.items(), key=lambda x: x[1])
#print(villian_sorted[-3],villian_sorted[-2],villian_sorted[-1])
print("The antagonist is", villian_sorted[-1][0].capitalize(), end = ".\n")
f.close()

