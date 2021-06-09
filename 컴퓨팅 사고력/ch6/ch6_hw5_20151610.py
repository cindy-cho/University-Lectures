'''실습 5'''
import math as m
a, b, c= input("Enter a, b, c : ").split()
a = float(a)
b = float(b)
c = float(c)
D = b*b - 4*a*c
if(D>0) :
    D = m.sqrt(D)
    root1 = (-b + D)/2*a
    root2 = (-b - D)/2*a
    print("root1 = %.4f and root2 = %.4f." %(root1,root2))
elif(D==0) :
    root1 = -b/2*a
    print("single root = %.4f." %(root1))
else :
    print("no root exists.")
