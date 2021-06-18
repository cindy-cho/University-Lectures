''' 전체 '''

fp_r = open("in.txt",'r')
fp_w = open("out.txt", 'w')

fp_r.read()  # 파일전체
fp_r.readline() # 한줄씩
fp_r.readlines() # 파일을 줄 단위로 읽어 리스트로 반환

for aLine in fp_r:
    statements

# 파일 전체를 한줄씩 읽는 법

fp_w.write(string) # 줄바꿈 없음
print(objects,file=fp_w) # 줄바꿈 있음. end 값 변경 가능

fp_r.close()
fp_w.close()

#random 모듈
import random

random.randint(1,6)

myList = ['red','green','blue']
color = random.choice(myList)

#사용자 정의 모듈로 구성
FILE : userModule.py
def add_multiply(x,y):
    sum = x+y
    mul = x*y
    return sum, mul

FILE : main.py
from userModule import *
#그대로 쓰면 된다
add_multiply


#터틀 
from turtle import *
fd(100)
rt(90)
pencolor("red")
circle(100)
left(360/6)
done()
penup()
goto(200,0)
pendown()
width(20)
color("red")
fillcolor("green")


#tuple
t = ()
t = tuple()

T = (1,)

#List
#Slicing
L[ b : e : s ]
L.extend(M)
L.sort()
L.sort(reverse=True)

M = list(enumerate(L))


#String
s.isalpha()
s.islower()
s.isalnum()
s.isspace()
s.isdecimal
s.count(a)
s.find(a)
s.upper()
s.lower()
s.replace("hi","hello")
s.title()
s.lsstrip()
s.rstrip()  #공백제거

