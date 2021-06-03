#ch9_hw3_20151610

A = [4, 8, 2, 3, 4, 2]
B = [7, 2, 5, 2, 3, 6, 5]

AA = set(A)
BB = set(B)

CC = AA&BB

C = list(CC)
C = sorted(C)

print(C)
