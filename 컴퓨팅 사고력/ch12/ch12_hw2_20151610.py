import random as rand
def isFront():
    return rand.randint(0,1)

def throwCoin(a):
    '''동전 던지기 앞면이 나올 횟수'''
    i = 1
    chance = 0
    while i <= a :
        if isFront() == 0 :
            chance += 1

        if i <= 10 or i % 10 == 0 :
            print("%3d 번째까지 던지기에서 앞면이 나온 확률 : %2d%%" %(i, chance/i*100))
        
        i += 1
    
    return chance


a = int(input("동전 던지기 시도 횟수를 입력(1 - 100) : "))
chance = throwCoin(a)
print("\n***********************************************")
print("총 %2d번 동전 던지기에서 앞면이 나올 확률 : %2d%%" %(a, chance/a*100))
