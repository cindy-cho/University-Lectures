nSize = int(input("구하려는 소수의 개수를 입력 : "))
nSizeCpy = nSize
N = 2
while(nSize>0):
    primeChk = True
    k = 2
    while k < N:
        if N % k == 0:
            primeChk = False
            break
        k+=1

    if primeChk == True:
        print(N)
        nSize-=1

    N+=1

print("%d 개의 소수를 찾았습니다"%(nSizeCpy))
