'''ch4_6'''
import math as m
num = 10
print(num,type(num),"\n")

print("5의 루트 값은: {:8.5f}\n".format(m.sqrt(5.0)))

str1 = "hello"
print(str1[0::2])
print(str1[::-1])
print(str1[1::-1])
print(str1[2::],"\n")

Korean = 80.3 ; English = 95.7 ; Math = 73.2 ;
print("과목      점수")
print("------------")
print("국어:{:8.2f}".format(Korean))
print("영어:{:8.2f}".format(English))
print("수학:{:8.2f}".format(Math))

AVG = Korean+English+Math

print("총점:{:8.2f}".format(AVG))
print("평균:{:10.4f}\n".format(AVG/3))

str1 = "These_functions_cannot_be_used_with_complex_numbers."
print("원래 문장: %s" %str1)
str1 = str1.replace("_"," ")
print("수정한 문장: {}" .format(str1))
print("a는 {}번 나왔다.".format(str1.count('a')))
print("e는 {}번 나왔다.".format(str1.count('e')))
print("u는 {}번 나왔다.".format(str1.count('u')))
print("space는 {}번 나왔다.".format(str1.count(' ')))
print("모두 대문자로 바꾸면: {}".format(str1.upper()))
