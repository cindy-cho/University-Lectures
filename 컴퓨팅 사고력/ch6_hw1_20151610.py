'''6단원 과제 1'''
a,b,c=input("세 개의 정수를 입력하시오 : ").split()

a = int(a);b=int(b);c=int(c)
if(a>b and a>c):
    if(b<c):
        tmp = b
        b = c
        c=tmp

elif(b>a and b>c):
    tmp = a
    a = b
    b= tmp
    if(b<c):
        tmp = b
        b=c
        c=tmp

elif(c>a and c>b):
    tmp = a
    a = c
    c = tmp
    if(b<c):
        tmp = b
        b = c
        c = tmp

print("내림차순 정렬:",a,b,c)
