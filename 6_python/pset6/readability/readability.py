from cs50 import get_string

# prompt user for input
text = get_string("Text: ")

# init variables
letters = 0
spaces = 0
puncts = 0

# iter through text
for i in text:
    if i.isalpha() == True:
        letters += 1
    elif i.isspace() == True:
        spaces += 1
    elif i in [".", "!", "?"]:
        puncts += 1
    else:
        continue

# other variables
words = spaces + 1
sentences = puncts

# calculate index
L = (letters * 100) / words
S = (sentences * 100) / words
index = 0.0588 * L - 0.296 * S - 15.8

# output according to index
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")