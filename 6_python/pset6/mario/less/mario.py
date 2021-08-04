from cs50 import get_int


while True:
    h = get_int("Height: ")
    if h >= 1 and h <= 8:
        break

for i in range(h):
    for j in range(h):
        # print the hashes
        if (i + j) >= (h - 1):
            print("#", end="")
        # print the spaces
        else:
            print(" ", end="")
    print()