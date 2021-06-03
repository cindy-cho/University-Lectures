'''hw4_3'''
sample = "abcABCdEFaBCDeFAbC"
sample = sample.lower()
a = sample.find('abc'); aa = sample.count('abc')
b = sample.find('def'); bb = sample.count('def')

print('"abc 문자열 : %d인덱스, %d번 존재"' %(a,aa))
print('"def 문자열 : %d인덱스, %d번 존재"' %(b,bb))
