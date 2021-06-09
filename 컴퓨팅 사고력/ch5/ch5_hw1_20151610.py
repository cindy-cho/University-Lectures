#ch5_hw1
import math as m
num1, num2, num3 = input("정수 숫자 3개를 입력 : ").split()
print("입력 받은 값 :",num1,num2,num3)                         
sum = int(num1) + int(num2) + int(num3)
print("총합 : {:3}".format(sum))
print("평균 : {:3.1f}".format(sum/3))
