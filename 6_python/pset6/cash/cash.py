from cs50 import get_float


while True:
    n = get_float("Change owed: ")
    if (isinstance(n, float) == True) and (n > 0):
        cents = int(n * 100)
        break

# create list of coins
money = [25, 10, 5, 1]

# number of coins starts with 0
coins = 0
for i in money:
    while cents >= i:
        cents -= i
        coins += 1

print(coins)