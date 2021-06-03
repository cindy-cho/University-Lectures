'''6단원 과제 2'''
x,op,y = input("수식 입력(예:20*40) : ").split()
x=float(x);y=float(y)

if(op=='+'):
    print("%.6f %c %.6f = %.6f" %(x,op,y,x+y))
elif(op=='-'):
    print("%.6f %c %.6f = %.6f" %(x,op,y,x-y))
elif(op=='*'):
    print("%.6f %c %.6f = %.6f" %(x,op,y,x*y))
elif(op=='/'):
    if(y==0.0) :
        print("%.6f 로 나누기를 수행할 수 없습니다."%(y))
    else :
        print("%.6f %c %.6f = %.6f" %(x,op,y,x/y))
else:
    print("%c 지원하지 않는 연산자입니다."%(op))
