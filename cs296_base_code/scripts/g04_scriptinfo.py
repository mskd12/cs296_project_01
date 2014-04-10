import sys

filename = input("Please enter the name/path of a script... \n")
#filename = input()
try:
	fo = open(filename,'r')
except OSError:
	print("No file of the given path/name exists. The script will exit now.")
	sys.exit()


line = fo.readline()
while line.isspace():
	line = fo.readline()
	continue

print("The title of the movie is", line.strip(), end = " ")

line = fo.readline()
while line.isspace():
        line = fo.readline()
        continue

while not line.isspace() and 'by' not in line:
	print(line.strip(), end = "")
	line = fo.readline()

while line.isspace():
        line = fo.readline()
        continue

if 'by' in line:
	print(".\n")
	line = fo.readline()
	while line.isspace():
		line = fo.readline()
		continue

	writers_str = ""
	while not line.isspace():
		writers_str = writers_str + " " + line.strip() + " "
		line = fo.readline()
		
	writers = writers_str.split(",")
	writers_last = writers.pop();
	writers.extend(writers_last.split("and"))	
	writers_last = writers.pop();
	writers.extend(writers_last.split("&"))

	if len(writers) > 1:
		print("The authors of the script are", end = " ")
		for w in writers:
			if w is writers[-1]:
				print("and", w.strip(), end = ".\n")
			else:
				print(w.strip(), end = ", ")
	else:
		print("The author of the script is", writers[0].strip(), end = ".\n")
fo.close()