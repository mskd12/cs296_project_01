import operator
import re
import datetime
import sys

filename = input("Please enter the name/path of a script... \n")
#filename = input()
try:
	fo = open(filename,'r')
except OSError:
	print("No file of the given path/name exists. The script will exit now.")
	sys.exit()



genre_list = ["comedy", "action", "drama", "romance", "scifi", "horror", "fantasy"]
genre_count = dict()
for genre in genre_list:
	genre_count[genre] = 0

comedy_words = ["laugh", "joke", "sarcastic", "sarcasm"]
action_words = ["punch", "gun", "blow", "nuclear", "shot", "explode", "explosion", "chase", "police", "disguise", "hit", "bang", "CIA", "FBI", "bomb", "hijack", "scream", "blow"]
drama_words = ["love", "tragic", "relationship", "tears", "death", "funeral", "marriage", "divorce", "grief", "sad", "depress", "overwhelm", "pain", "happ", "regret", "sorry", "err"]
romance_words = ["love", "break-up", "date", "relationship", "kiss", "flirt", "romance", "girl", "night", "heart", "cry", "tears", "gorgeous", "darling", "beautiful"]
scifi_words = ["time travel", "robot", "nuclear", "unmanned", "galaxy", "worlds", "alien", "apocalyp", "earthling", "spaceship", "planet", "graphy"]
horror_words = ["scream", "moonless", "night", "ominous", "horror", "murder", "suicide", "fear", "death", "grave", "blood", "gore", "ghost", "spirit", "shout", "lone", "pale", "terror", "werewol", "vampire", "hell", "satan", "hack", "pain"]
fantasy_words = ["magic", "wand", "witch", "fantasy", "ancient", "angel", "spirit", "ghost", "monster", "hobbit", "elf", "elves", "dwarf", "dwarves", "earthling", "werewol", "vampire", "satan"]

genre_words = dict(comedy = comedy_words, action = action_words, drama = drama_words, romance = romance_words, scifi = scifi_words, horror = horror_words, fantasy = fantasy_words)

for line in fo:
	if line.isspace():
		continue

	for genre in genre_list:
		#print(genre)
		lower_line = line.lower()
		for word in genre_words[genre]:
			if lower_line.find(word) != -1:
				genre_count[genre] = genre_count[genre] + 1
			if genre is "scifi":
				suspected_year = re.search(r'[0-9][0-9][0-9][0-9]', lower_line)
				now = datetime.datetime.now()
				if suspected_year and now.year < int(suspected_year.group()):
					genre_count[genre] = genre_count[genre] + 1

genre_counts_sorted = sorted(genre_count.items(), key=lambda x: x[1])
print("The movie is a", end = " ")
if genre_counts_sorted[-1][1] - genre_counts_sorted[-2][1] < 25:
	print(genre_counts_sorted[-2][0],genre_counts_sorted[-1][0])
else:
	print(genre_counts_sorted[-1][0])	

