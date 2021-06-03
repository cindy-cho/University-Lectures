'''실습 풀이'''

'''5-1'''
##a,b,c = input("정수 숫자 3개를 입력 : ").split()
##a = int(a)
##b = int(b)
##c = int(c)
##
##total = a + b + c
##average = total/3
##
##print("입력 받은 값 :",a,b,c)
##print("총합 : ",total)
##print("평균 : %.1f"%average)


'''5-2'''
##sentence = "Good words cost nothing"
##word = input("찾는 단어 입력 : ")
##index = sentence.count(word)
##print("%s 문장에서는 %s 단어가 %d 번 있습니다."%(sentence,word,index))


'''5-3'''
##from math import *
##x1, y1, x2, y2 = input("두 점의 좌표값을 x1, y1, x2, y2 순서대로 입력 : ").split()
##x1 = float(x1)
##y1 = float(y1)
##x2 = float(x2)
##y2 = float(y2)
##distance = sqrt((x2-x1)**2 +(y2-y1)**2)
##
##print("두 점 사이의 거리는 %.2f 입니다."%distance)
##print("두 점 사이의 거리는 5이하 입니까?",distance <=5)

'''6-1'''
##a, b, c = input("세 개의 정수를 입력하시오 : ").split()
##a = int(a); b= int(b); c=int(c)
##
##if(a<b):
##    a, b = b, a
##
##if(a<c):
##    a, c = c, a
##
##if(b<c):
##    b, c = c, b
##
##print("내림차순 정렬 :",a,b,c)

'''6-2'''
##num1, op, num2 = input("수식 입력(예: 20 * 40) : ").split()
##num1 = float(num1);num2=float(num2)
##
###6번째 출력은 float의 디폴트 출력자리 개수임
##if op == "+":
##    result = num1 + num2
##    print("%f %s %f = %f"%(num1,op,num2,result))
##
##elif op == "*":
##    result = num1 * num2
##    print("%f %s %f = %f"%(num1,op,num2,result))
##
##elif op == "-":
##    result = num1 - num2
##    print("%f %s %f = %f"%(num1,op,num2,result))
##
##elif op == "/":
##    if num2 == 0:
##        print("%f로 나누기를 수행할 수 없습니다."%num2)
##    else:
##        result = num1 / num2
##        print("%f %s %f = %f"%(num1,op,num2,result))
##
##else :
##    print(op,"지원하지 않는 연산자 입니다.")


'''6-3'''
##num1, num2 = input("두 자리 정수 두개를 입력 : ").split()
##num1=int(num1);num2=int(num2)
##
##num1_10 = num1 // 10
##num1_1 = num1 % 10
##
##num2_10 = num2 // 10
##num2_1 = num2 % 10
##
##if num2 == num1:
##    print("두 정수는 모두",num2,"로 같은 정수입니다.")
##elif(num2_1==num1_10 and num2_10==num1_1):
##    print(num1,",",num2,": 자리 값만 다른 정수입니다.")
##elif(num2_1==num1_1 or num2_10==num1_10
##     or num2_1==num1_10 or num2_10==num1_1):
##    print(num1,",",num2,": 하나의 숫자만 일치합니다.")
##else:
##    print(num1,",",num2,":일치하지 않는 정수입니다.")
##    

'''근의 공식'''
import math as m

bound = 1.0e-8

a,b,c = input("Enter a, b, c : ").split()
a=float(a) ; b=float(b) ; c=float(c)

D = b * b - 4 * a * c

if abs(D) <= bound:
    root1 = -b / (2*a)
    print("single root = %.4f."%root1)


elif if D > 0:
    D = m.sqrt(D)
    root1 = (-b + D) / (2 * a)
    root2 = (-b - D) / (2 * a)
    print("root1 = %.4f and root2 = %.4f."%(root1,root2))

else:
    print("no root exists.")
    
'''5번'''

##if D > 0:
##    D = m.sqrt(D)
##    root1 = (-b + D) / (2 * a)
##    root2 = (-b - D) / (2 * a)
##    print("root1 = %.4f and root2 = %.4f."%(root1,root2))
##
##elif D == 0:
##    root1 = -b / (2*a)
##    print("single root = %.4f."%root1)
##    
##else:
##    print("no root exists.")






