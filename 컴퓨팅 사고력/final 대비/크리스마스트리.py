'''크리스마스트리'''

for i in range(5):
    for j in range(6-i):
        print(" ",end='')
    for j in range((i+1)*2-1):
        print("*",end='')
    print()

for i in range(5):
    for j in range(4-i):
        print(" ",end='')
    for j in range((i+2)*2+1):
        print("*",end='')
    print()
