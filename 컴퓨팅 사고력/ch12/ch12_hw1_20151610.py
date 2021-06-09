def plusOperation(a,b):
    '''더하기'''
    return a+b
    
def minusOperation(a,b):
    '''빼기'''
    return a-b

def divideOperation(a,b):
    '''나누기'''
    if b == 0 :
        return False;
    else :
        return a/b

def multiplyOperation(a,b):
    '''곱하기'''
    return a*b

a, op, b = input("수식 입력(예: 20 * 40) : ").split()
a = float(a)
b = float(b)

if op == '*':
    c = multiplyOperation(a,b)
    print("%f * %f = %f" %(a,b,c))

elif op == '/':
    c = divideOperation(a,b)
    if c == False :
        print("%f 로 나누기를 수행할 수 없습니다" %(b))
    else : 
        print("%f / %f = %f" %(a,b,c))

elif op == '+':
    c = plusOperation(a,b)
    print("%f + %f = %f" %(a,b,c))

elif op == '-':
    c = minusOperation(a,b)
    print("%f - %f = %f" %(a,b,c))

else:
    print("%s 지원하지 않는 연산자입니다" %(op))
