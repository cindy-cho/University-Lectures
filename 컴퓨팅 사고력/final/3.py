targetN = int(input("입력한 수까지 1과 소수를 제외한 수의 약수의 합을 구합니다.\n양의 정수를 입력하세요: "))
for i in range(2,targetN+1):
    #isPrime에 True값을 넣는다.
    isPrime = True
    #약수의 합을 nSum에 저장한다. 0으로 초기화.
    nSum = 0
    for j in range(2,i):
        #만약 나머지가 0이면 소수가 아니므로.
        if i%j==0:
            #합을 더하고, 소수가 아니기때문에 False로 세팅한다.
            nSum += j
            isPrime = False

    #False일 경우, 1과 자기자신을 더한 값을 sum으로 만들고 출력한다.
    if isPrime == False:
        nSum +=1
        nSum +=i
        print("%d의 약수의 합은 %d입니다."%(i,nSum))
        
