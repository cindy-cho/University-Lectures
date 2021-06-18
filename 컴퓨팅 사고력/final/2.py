#위에있는 트리 출력
for i in range(5):
    #빈칸 출력
    for j in range((5-i)+2):
        print(" ",end='')
    #별 출력
    for j in range(i*2+1):
        print("*",end='')
    #줄 바꿈
    print()

#아래있는 트리 출력
for i in range(5):
    #빈칸 출력
    for j in range(5-i):
        print(" ",end='')
    #별 출력
    for j in range((i+2)*2+1):
        print("*",end='')
    #줄 바꿈
    print()

