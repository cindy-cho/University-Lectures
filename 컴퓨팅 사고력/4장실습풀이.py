'''4장 실습 풀이'''
str1 = "Computer 4";str2 = "Science#5"
print(str1[:8] * int(str1[9:]))
print(str2[:7] * int(str2[8:]))


s1="Sogang University"
s2=s1[:6]
s3=s1[7:17]
s4=s1[5::-1]
print(s2)
print(s3)
print(s4)

sample = "abcABCdEFaBCDeFAbC"
sample = sample.lower()
index_abc = sample.find("abc")
index_def = sample.find("def")
count_abc = sample.count("abc")
count_def = sample.count("def")

print(index_abc,",",count_abc)
print(index_def,",",count_def)
                        
original = "This class is Computational Thinking!"
reverse = original[::-1]
print("reversed sentence : {}".format(reverse))

num=3.1415926; x="123"; y="abc"
print("{2},{0},{1}".format(x[0], x[1],x[2]))
print("{:10.2f}".format(num))
print("{:10d}".format(int(x)))
print("{:10s}".format(y))
