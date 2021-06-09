'''6단원 과제 3'''
a,b = input("두 자리 정수 두개를 입력 : ").split()
if(a[0]==b[0] and a[1]==b[1]):
    print("두 정수는 모두 %s 로 같은 정수입니다."%(a))
elif(a[0]==b[1] and a[1]==b[0]):
    print("%s , %s : 자리 값만 다른 정수입니다."%(a,b))
elif(a[0]==b[0] or a[1]==b[1] or a[0]==b[1] or a[1]==b[0]):
    print("%s , %s : 하나의 숫자만 일치합니다."%(a,b))
else:
    print("%s , %s : 일치하지 않는 정수입니다."%(a,b))
