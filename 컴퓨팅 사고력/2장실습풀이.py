'''2장 실습풀이'''
#1번
a = 3.14
a = str(a)
print(a, type(a))

#str -> float -> int

a= int(float(a))
print(a,type(a))

a=float(a)
print(a,type(a))

#2번

num1 = 10
num2 = 20

print(num1, num2)
num1, num2 = num2, num1
print(num1,num2)

'''3장 실습풀이'''
#1

import math as m
pt1=21.9
pt2=37
pt3=13.6

avg = (pt1+pt2+pt3)/3
print("average : " , m.trunc(avg))

#2
money = 3928
print(money)
coin500 = money // 500
money %= 500
print("500won: ",coin500)
coin100= money //100
money %= 100
print("100won : " ,coin100)
print("left : ", money)
