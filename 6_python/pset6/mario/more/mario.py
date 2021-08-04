n = input("Height: ")
while ((n > 1) and (n < 8)):
    try:
        n = int(input("Height: "))
    except:
        continue

i = 0
while i < n:

    # left
    j = 0
    while j < n:
        if (i + j < n - 1):
            print(' ')
        else:
            print('#')
        j += 1

    # margin
    j = n
    while j == n:
        print(' ')
        j += 1

    # right
    j = n
    while j < n + 1 + i:
        print('#')
        j += 1


    i += 1





