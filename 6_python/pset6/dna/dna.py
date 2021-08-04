import csv
import sys

# arguments error check
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit(1)

# open & read the csv file
csv_filename = sys.argv[1]
sequence_filename = sys.argv[2]

# get str_list
with open(csv_filename, "r") as f:
    reader = csv.reader(f)
    header = next(reader)
    str_list = header[1:]

# get main data
data = []
with open(csv_filename, "r") as f:
    reader = csv.DictReader(f)
    for row in reader:
        data.append(row)


# open & read the sequence
with open(sequence_filename, "r") as f:
    sequence = f.read()


# compute STR counts
str_counts = dict.fromkeys(str_list, 0)

for s in str_list:
    max_count = 0
    for i in range(len(sequence)):
        count = 0
        # if str match found, start counting repeats
        if sequence[i:(i + len(s))] == s:
            r = 0
            while sequence[(i + r):(i + r + len(s))] == s:
                r += len(s)
                count += 1
            # if new max of repeats, update max
            if count > max_count:
                max_count = count
    str_counts[s] = max_count


# compare against data
for person in data:
    match = 0
    for s, c in str_counts.items():
        if c == int(person[s]):
            match += 1

    # if all STRs are matched
    if match == len(str_list):
        print(person['name'])
        sys.exit()
print("No match")