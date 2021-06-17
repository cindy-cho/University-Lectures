'''4개의 산술연산'''

def plusCmd(num1,num2):
    return num1+num2

def minusCmd(num1,num2):
    return num1-num2

def mulCmd(num1,num2):
    return num1*num2

def divCmd(num1,num2):
    if num2 == 0:
        return False
    return num1/num2


num1, op, num2 = input("수식 입력(예: 20 * 40) : ").split()
num1 = float(num1)
num2 = float(num2)

if op == '+':
    print("%f + %f = %f" %(num1,num2,plusCmd(num1,num2)))

elif op == '-':
    print("%f + %f = %f" %(num1,num2,minusCmd(num1,num2)))
    
elif op == '*':
    print("%f + %f = %f" %(num1,num2,mulCmd(num1,num2)))
    
elif op == '/':
    if divCmd(num1,num2) == False:
        print("%f 로 나누기를 수행할 수 없습니다."%num2)
    else:
        print("%f + %f = %f" %(num1,num2,plusCmd(num1,num2)))

else:
    print("%s 지원하지 않는 연산자입니다." %op)

